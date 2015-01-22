#include <iostream>
#include <fstream>
#include <cassert>

#include "fbt_table_gen.h"

using namespace std;

/**
 * Generate the opcode tables used by Fbt.
 *
 * This table will generate a translator that does nothing really special. Most
 * of the instructions will be simply copied to the translated code and executed.
 *
 * To get the desired instrumentation effect, use `add_analysis_function` to
 * define the appropriate actions for specific instructions.
 * `ia32_table_generator/libstm_table_gen.cpp` is an example of this.
 */
int main (int argc, char *argv[]) {
  cout << "Generating ARM fbt_opcode_tables.h...";

  ofstream output_file("fbt_opcode_tables.h");
  assert(output_file.is_open());

  generate_tables(output_file, "");

  cout << endl;

  return 0;
}
