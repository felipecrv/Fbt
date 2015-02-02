include ../Makedefs

# activate optimizations
CFLAGS += -fno-stack-protector -fno-omit-frame-pointer

# relro with global offset table protection
LDFLAGS += -Wl,-z,relro,-z,now,-z,initfirst $(I386)

# use gcc
CC=gcc
# flags for position independent code in object files
LIBFLAGS=-fpic -c

# Make sure we fail if anything fails in a loop
SHELL := /bin/bash -e

# object files
FILES+=libfastbt.c fbt_mem_mgmt.c fbt_translate.c fbt_code_cache.c fbt_actions.c \
	generic/fbt_llio.c generic/fbt_libc.c fbt_debug.c fbt_trampoline.c fbt_syscall.c \
	fbt_mutex.c generic/fbt_algorithms.c fbt_mem_pool.c

# object files for the ARM disassembler
ARM_DISASSEMBLER_FILES=generic/fbt_llio.c generic/fbt_libc.c \
											 arm/fbt_disassemble.c arm/disassembler.c

# we include some kernel stuff as we directly call system calls.
CFLAGS += -I/lib/modules/$(shell uname -r)/build/arch/x86/include

GEN_DIR=generated

.PHONY: all clean

all: $(LIBNAME).so $(LIBNAME).a

$(LIBNAME).so: *.h ia32/*.h generic/*.h $(FILES)
	mkdir -p $(GEN_DIR)
	mkdir -p $(GEN_DIR)/generic
	
	for file in $(FILES); do \
		gcc ${CFLAGS} -E $$file > $(GEN_DIR)/$$file; \
	done

	for file in $(FILES); do \
		$(DSL_PATH) $(GEN_DIR)/$$file $(GEN_DIR)/$$file ; \
	done
	
	cp *.h $(GEN_DIR)
	cp generic/*.h $(GEN_DIR)/generic

	$(CC) $(CFLAGS) $(LIBFLAGS) generated/*.c generated/generic/*.c
	$(CC) -shared -Wl,-soname,$(LIBNAME).so.$(LIBVERS) \
		-o $(LIBNAME).so *.o $(LDFLAGS)

$(LIBNAME).a:
	ar cru $(LIBNAME).a libfastbt.o

arm/fbt_opcode_tables.h: arm/fbt_arm_opcode.h
	make -C ../arm_table_generator fbt_opcode_tables.h
	cp ../arm_table_generator/fbt_opcode_tables.h arm/

arm/disassembler: $(ARM_DISASSEMBLER_FILES) *.h arm/*.h generic/*.h arm/fbt_opcode_tables.h
	$(CC) $(CFLAGS) -c $(ARM_DISASSEMBLER_FILES)
	$(CC) $(CFLAGS) *.o -o $@

clean:
	rm -rf $(GEN_DIR)
	rm -f *.o arm/*.o *.lo *.la *~ *.as *.out
	rm -f $(LIBNAME).a
	rm -f $(LIBNAME).so
	rm -f arm/disassembler
