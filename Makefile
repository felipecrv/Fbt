# have a look at CONFIGURATION and the different Makedefs to configure the BT
include ./Makedefs

.PHONY: all clean build test documentation

all: build

build:
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
