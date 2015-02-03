include ../Makedefs

# activate optimizations
CFLAGS += -fno-stack-protector -fno-omit-frame-pointer

# relro with global offset table protection
LDFLAGS += -Wl,-z,relro,-z,now,-z,initfirst $(I386)

# flags for position independent code in object files
LIBFLAGS=-fpic -c

# Make sure we fail if anything fails in a loop
SHELL := /bin/bash -e

# object files for IA32
IA32_FILES += libfastbt.c fbt_mem_mgmt.c fbt_translate.c fbt_code_cache.c fbt_actions.c \
	generic/fbt_llio.c generic/fbt_libc.c fbt_debug.c fbt_trampoline.c fbt_syscall.c \
	fbt_mutex.c generic/fbt_algorithms.c fbt_mem_pool.c

# object files for ARM
ARM_FILES += libfastbt.c generic/fbt_algorithms.c #generic/fbt_libc.c generic/fbt_llio.c

# object files for the ARM disassembler
ARM_DISASSEMBLER_FILES=generic/fbt_llio.c generic/fbt_libc.c \
											 arm/fbt_disassemble.c arm/arm_disassembler.c

# we include some kernel stuff as we directly call system calls.
ifeq ($(TARGET_ARCH),ia32)
  CFLAGS += -I/lib/modules/$(shell uname -r)/build/arch/x86/include
else # ARM
  CFLAGS += -I/lib/modules/$(shell uname -r)/build/arch/arm/include
endif

GEN_DIR=generated

.PHONY: all clean

all: $(LIBNAME).so $(LIBNAME).a

$(IA32_LIBNAME).so: *.h ia32/*.h generic/*.h $(IA32_FILES)
	mkdir -p $(GEN_DIR)
	mkdir -p $(GEN_DIR)/generic
	
	for file in $(IA32_FILES); do \
		$(CC) ${CFLAGS} -E $$file > $(GEN_DIR)/$$file; \
	done

	for file in $(IA32_FILES); do \
		$(DSL_PATH) $(GEN_DIR)/$$file $(GEN_DIR)/$$file ; \
	done
	
	cp *.h $(GEN_DIR)
	cp generic/*.h $(GEN_DIR)/generic

	$(CC) $(CFLAGS) $(LIBFLAGS) generated/*.c generated/generic/*.c
	$(CC) -shared -Wl,-soname,$(IA32_LIBNAME).so.$(LIBVERS) \
		-o $(IA32_LIBNAME).so *.o $(LDFLAGS)

$(ARM_LIBNAME).so: *.h arm/*.h generic/*.h $(ARM_FILES)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(ARM_FILES)
	$(CC) -shared -Wl,-soname,$(ARM_LIBNAME).so.$(LIBVERS) \
		-o $(ARM_LIBNAME).so *.o $(LDFLAGS)

$(LIBNAME).a:
	ar cru $(LIBNAME).a libfastbt.o

arm/fbt_opcode_tables.h: arm/fbt_arm_opcode.h
	make -C ../arm_table_generator fbt_opcode_tables.h
	cp ../arm_table_generator/fbt_opcode_tables.h arm/

arm_disassembler: $(ARM_DISASSEMBLER_FILES) *.h arm/*.h generic/*.h arm/fbt_opcode_tables.h
	$(CC) $(CFLAGS) $(EXTRA_ARM_DISASSEMBLER_CFLAGS) -c $(ARM_DISASSEMBLER_FILES)
	$(CC) $(CFLAGS) $(EXTRA_ARM_DISASSEMBLER_CFLAGS) *.o -o $@

clean:
	rm -rf $(GEN_DIR)
	rm -f *.o *.lo *.la *~ *.as *.out
	rm -f $(IA32_LIBNAME).a $(ARM_LIBNAME).a
	rm -f $(IA32_LIBNAME).so $(ARM_LIBNAME).a
	rm -f arm_disassembler
