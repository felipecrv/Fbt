#!/usr/bin/env python

X86 = 0
ARM = 1

class Arch(object):
    def __init__(self, arch_code):
        self.arch_code = arch_code

    def is_x86(self): return self.arch_code == X86

    def is_arm(self): return self.arch_code == ARM

    def get_assembler_command(self, input_filename, output_obj_path):
        if self.is_x86():
            return 'as --32 -march=i386 "%s" -o "%s"' % (input_filename, output_obj_path)
        if self.is_arm():
            return '/opt/cross/bin/arm-unknown-linux-gnueabi-as -march=armv6 "%s" -o "%s"' % (
                    input_filename, output_obj_path)

    def get_objdump_program_name(self):
        if self.is_x86():
            return 'objdump'
        if self.is_arm():
            return '/opt/cross/bin/arm-unknown-linux-gnueabi-objdump'
