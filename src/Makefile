include ../Makedefs

# activate optimizations
CFLAGS += -fno-stack-protector -fno-omit-frame-pointer

# relro with global offset table protection
LDFLAGS += -Wl,-z,relro,-z,now,-z,initfirst $(I386)

# Make sure we fail if anything fails in a loop
SHELL := /bin/bash -e

# object files for IA32
IA32_FILES += libfastbt.c fbt_mem_mgmt.c fbt_translate.c fbt_code_cache.c ia32/fbt_actions.c \
	generic/fbt_llio.c generic/fbt_libc.c fbt_debug.c ia32/fbt_trampoline.c fbt_syscall.c \
	generic/fbt_mutex.c generic/fbt_algorithms.c fbt_mem_pool.c ia32/fbt_disassemble.c \
	ia32/fbt_ia32_debug.c

# object files for ARM
ARM_FILES += libfastbt.c generic/fbt_algorithms.c generic/fbt_libc.c generic/fbt_llio.c \
						 generic/fbt_mutex.c arm/fbt_disassemble.c fbt_syscall.c \
						 fbt_mem_mgmt.c fbt_mem_pool.c fbt_debug.c fbt_code_cache.c fbt_translate.c \
						 arm/fbt_actions.c arm/fbt_trampoline.c arm/fbt_pc_cache.c

# object files for the ARM disassembler
ARM_DISASSEMBLER_FILES=generic/fbt_llio.c generic/fbt_libc.c \
											 arm/fbt_disassemble.c arm/arm_disassembler.c \
											 arm/fbt_actions.c fbt_debug.c

.PHONY: all clean

all: $(LIBNAME).so $(LIBNAME).a

$(IA32_LIBNAME).so: *.h ia32/*.h generic/*.h $(IA32_FILES)
	mkdir -p generated
	mkdir -p generated/generic
	mkdir -p generated/ia32

	for file in $(IA32_FILES); do \
		$(CC) ${CFLAGS} -E $$file > generated/$$file; \
	done

	for file in $(IA32_FILES); do \
		$(DSL_PATH) -c ia32 generated/$$file generated/$$file ; \
	done

	cp *.h generated
	cp generic/*.h generated/generic
	cp ia32/*.h generated/ia32

	$(CC) $(CFLAGS) -fpic -c generated/generic/*.c generated/ia32/*.c generated/*.c
	$(CC) -shared -Wl,-soname,$(IA32_LIBNAME).so.$(LIBVERS) \
		-o $(IA32_LIBNAME).so *.o $(LDFLAGS)

$(ARM_LIBNAME).so: *.h arm/*.h generic/*.h $(ARM_FILES)
	mkdir -p generated
	mkdir -p generated/generic
	mkdir -p generated/arm

	for file in $(ARM_FILES); do \
		$(CC) ${CFLAGS} -E $$file > generated/$$file; \
	done

	for file in $(ARM_FILES); do \
		$(DSL_PATH) -c arm generated/$$file generated/$$file ; \
	done

	cp *.h generated
	cp generic/*.h generated/generic
	cp arm/*.h generated/arm

	$(CC) $(CFLAGS) -fpic -c generated/generic/*.c generated/arm/*.c generated/*.c
	$(CC) $(LDFLAGS) -shared -Wl,-soname,$(ARM_LIBNAME).so.$(LIBVERS) \
		-o $(ARM_LIBNAME).so *.o

$(LIBNAME).a: $(LIBNAME).so
	ar cru $(LIBNAME).a *.o

ia32/fbt_opcode_tables.h: ia32/fbt_x86_opcode.h
	make -C ../ia32_table_generator fbt_opcode_tables.h
	mv ../ia32_table_generator/fbt_opcode_tables.h ia32/

arm/fbt_opcode_tables.h: arm/fbt_arm_opcode.h
	make -C ../arm_table_generator fbt_opcode_tables.h
	mv ../arm_table_generator/fbt_opcode_tables.h arm/

arm_disassembler: $(ARM_DISASSEMBLER_FILES) *.h arm/*.h generic/*.h arm/fbt_opcode_tables.h
	$(CC) $(CFLAGS) $(EXTRA_ARM_DISASSEMBLER_CFLAGS) -c $(ARM_DISASSEMBLER_FILES)
	$(CC) $(CFLAGS) -lpthread $(EXTRA_ARM_DISASSEMBLER_CFLAGS) *.o -o $@

clean:
	rm -rf generated
	rm -f *.o *.lo *.la *~ *.as *.out
	rm -f *.a *.so
	rm -f arm_disassembler
