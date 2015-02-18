#include <string>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <list>

#include "fbt_table_gen.h"
#include "arm_opcode.h"
#include "arm_opcode.map.h"

using namespace std;

/*
 * The list of AnalysisFunction which will be called in sequence to define the
 * action to take for each instruction during translation.
 */
static list<AnalysisFunction> functions;

static string uppercase(const string &str) {
  string result(str);
  for (unsigned int i = 0; i < str.length(); i++) {
    result[i] = toupper(str[i]);
  }
  return result;
}

static string lowercase(const string &str) {
  string result(str);
  for (unsigned int i = 0; i < str.length(); i++) {
    result[i] = tolower(str[i]);
  }
  return result;
}

template<int w>
static void print_hex(ostream& out, unsigned int x) {
  out << "0x" << hex << setw(w) << setfill('0') << x;
}

static string generate_table_name(const string& prefix, unsigned int opcode) {
  stringstream temp;
  string name = (prefix != "") ? prefix + "_opcode_table_" : "opcode_table_";
  temp << hex << ((opcode >> 24) & 0xF);
  temp << hex << ((opcode >> 20) & 0xF);

  return name;
}

static void generate_opcode_table(ofstream& out,
                                  const string& prefix,
                                  const string& comment,
                                  unsigned int start) {
  string table_name = generate_table_name(prefix, start);
  unsigned int opcode_major_bits = (start >> 20) & 0xFF;

  out << " /* " << comment << " */" << endl;

  for (unsigned int i = 0; i < 16; i++) {
    /* get the disasm table entry for this instruction */
    instr_description *instr = &table_opcode_onebyte[opcode_major_bits];
    if (instr->table != NULL) {
      instr = &instr->table[i];
    }

    unsigned int opcode = (start & 0x0FF00000) | (i << 4);

    istringstream mnemonic_sstream(instr->mnemonic);
    string mnemonic;
    mnemonic_sstream >> mnemonic;
    mnemonic = lowercase(mnemonic);
    if (mnemonic == "") {
      mnemonic = "UNDEFINED";
    }
    string action = instr->default_action;
    if (action == "") {
      action = "action_copy";
    }

    out << " /* ";
    print_hex<8>(out, opcode);
    out << " */ {";
    print_hex<8>(out, instr->opcode_flags);
    out << ", ";
    print_hex<8>(out, instr->operand_flags);
    out << ", {.handler = " << action << "}, ";
    out << "\"" << mnemonic << "\"" << "}";
    if (i < 15 || opcode_major_bits < 0xFF) {
      out << ",";
    }

    out << " // " << instr->comment << endl;
  }
  out << endl;
}

/* External functions */

void add_analysis_function(AnalysisFunction f) {
  functions.push_back(f);
}

void generate_tables(ofstream& out, string prefix) {
  string PREFIX(uppercase(prefix));

  if (PREFIX == "") {
    PREFIX = "FBT";
  }

  out << "/***  !! THIS IS A GENERATED FILE !!  ***/" << endl;
  out << "/***  DO NOT MODIFY THIS FILE - ALL CHANGES WILL BE OVERWRITTEN WHEN A NEW VERSION IS GENERATED  ***/" << endl;
  out << endl << endl;
  out << "#ifndef " << PREFIX << "_OPCODE_TABLES_H" << endl;
  out << "#define " << PREFIX << "_OPCODE_TABLES_H" << endl;
  out << endl;
  out << "#include \"../fbt_translate.h\"" << endl;
  out << endl;
  out << endl;

  out << "struct arm_opcode opcode_table[] = {" << endl;
  for (unsigned int i = 0; i <= 0xFF; i++) {
    stringstream temp;
    temp << hex << (i >> 4);
    temp << hex << (i & 0xF);
    string comment = "0x_" + temp.str() + "_____";
    generate_opcode_table(out, prefix, comment, i << 20);
  }
  out << "};" << endl << endl;

  out << "struct arm_opcode *default_opcode_table = opcode_table;" << std::endl;
  out << std::endl;

  /* close the ifdef from the beginning */
  out << "#endif  /* " << PREFIX << "_OPCODE_TABLES_H */" << endl << endl;
}
