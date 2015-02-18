CC ?= gcc
ARCH ?= ia32
CFLAGS ?= -Wall

ifeq ($(ARCH),ia32)
	CFLAGS += -m32
endif

test: clean test-$(ARCH)

test-$(ARCH): multiple_macros
	./$<

multiple_macros: multiple_macros.c
	$(CC) $(CFLAGS) $< -o $@

multiple_macros.c: multiple_macros.dsl.c
	$(CC) $(CFLAGS) -E $< > pp_$<
	../src/parse.py -c $(ARCH) pp_$< $@

pytest:
	python multiple_macros.py

clean:
	rm -f pp_multiple_macros.dsl.c multiple_macros.c multiple_macros

.PHONY: test test-$(ARCH) pytest clean
