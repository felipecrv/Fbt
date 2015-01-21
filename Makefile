# have a look at CONFIGURATION and the different Makedefs to configure the BT
include ./Makedefs

FBT_OPCODE_TABLES = src/$(TARGET_ARCH)/fbt_opcode_tables.h

.PHONY: all clean build test documentation

all: build

$(TARGET_ARCH)_table_generator/fbt_opcode_tables.h:
	make -C $(TARGET_ARCH)_table_generator fbt_opcode_tables.h

$(FBT_OPCODE_TABLES): $(TARGET_ARCH)_table_generator/fbt_opcode_tables.h
	cp $< $@

build: $(FBT_OPCODE_TABLES)
	make -C src all

test:
	make -C src all
	make -C test all

documentation:
	doxygen doxygen.config

clean:
	make -C src clean
	make -C test clean
	rm -rf documentation
	rm -f lib/$(LIBNAME).so
