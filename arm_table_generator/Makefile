CXXFLAGS = -Wall -Wno-unused-function
CXXFLAGS += -I../src # for arm/fbt_arm_opcode.h
CXXFLAGS += $(EXTRA_CXXFLAGS)

TABLE_GENERATOR ?= default_table_gen


all: $(TABLE_GENERATOR)

clean:
	rm -f $(TABLE_GENERATOR) default_table_gen *.o fbt_opcode_tables.h

$(TABLE_GENERATOR): $(TABLE_GENERATOR).o fbt_table_gen.o *.h ../src/arm/fbt_arm_opcode.h
	$(CXX) $(CXXFLAGS) -o $@ $(TABLE_GENERATOR).o fbt_table_gen.o

fbt_opcode_tables.h: $(TABLE_GENERATOR)
	./$<

.PHONY: all clean
