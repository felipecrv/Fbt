#ifndef TABLE_GENERATOR_H
#define TABLE_GENERATOR_H

#include <fstream>
#include <string>

#include "arm_opcode.h"

/* Public interface for table generator definition */

/**
 * Analysis function type:
 *
 * @param opcode is a byte buffer holding the opcode for which the action should
 *               be defined
 * @param disasm_info is a struct with the informations of the disasm library
 * @param action is the current action which is inserted into the jump table.
 *                modify to change the action which is inserted
 * @return false if no more analysis functions should be called for this opcode
 */
typedef bool(*AnalysisFunction)(const unsigned char* opcode,
                                const instr_description& disasm_info,
                                std::string& action);

/**
 * Adds an analysis function. The functions are called in the order they were
 * added.
 *
 * @param f is a function pointer to an analysis function
 */
void add_analysis_function(AnalysisFunction f);

/**
 * Generates the opcode jump table.
 *
 * @param out is the stream where the generated file is outputted to
 * @param prefix is a string which is prepended to any variable in the generated
 *               output to prevent name colisions
 */
void generate_tables(std::ofstream& out, std::string prefix);

/* Helper functions */

#endif  /* TABLE_GENERATOR_H */
