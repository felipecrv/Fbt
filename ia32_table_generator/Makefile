CXXFLAGS = -Wall -Wno-unused-function
CXXFLAGS += -I./src -I./include -g

TARGETS = example libstm_table_gen


all: $(TARGETS)

clean:
	rm -f $(TARGETS) *.o ./src/*.o fbt_opcode_tables.h

example: ./src/table_gen.o ./src/instr_analyse_helpers.o example.o
	$(CXX) $(CXXFLAGS) -o $@ $^

libstm_table_gen: ./src/table_gen.o ./src/instr_analyse_helpers.o libstm_table_gen.o
	$(CXX) $(CXXFLAGS) -o $@ $^

fbt_opcode_tables.h: example
	./$<

.PHONY: all clean
