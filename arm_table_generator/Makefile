CXXFLAGS = -Wall -Wno-unused-function -DARM_TABLE_GENERATOR
CXXFLAGS += -I../src # for arm/fbt_arm_opcode.h
CXXFLAGS += $(EXTRA_CXXFLAGS)

TABLE_GENERATOR ?= default_table_gen

HEADERS=arm_opcode.h arm_opcode.map.h ../src/arm/fbt_arm_opcode.h


all: $(TABLE_GENERATOR)

clean:
	rm -f $(TABLE_GENERATOR) default_table_gen *.o fbt_opcode_tables.h

%.o: %.cpp $(HEADERS)
	$(CXX) $(CXXFLAGS) -c $< -o $@

$(TABLE_GENERATOR): $(TABLE_GENERATOR).o fbt_table_gen.o $(HEADERS)
	$(CXX) $(CXXFLAGS) -o $@ $(TABLE_GENERATOR).o fbt_table_gen.o

fbt_opcode_tables.h: $(TABLE_GENERATOR)
	./$<

.PHONY: all clean
