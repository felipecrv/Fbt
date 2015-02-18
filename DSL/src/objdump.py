#!/usr/bin/env python

import re
import subprocess

from util import find_list, address_to_bytes

class ObjdumpResult(object):
    def __init__(self, bytes, labels):
        self.bytes = bytes
        self.labels = labels
        self.code = {}
        self.variable_occurrences = None

def system(s):
    p = subprocess.Popen(s, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)

    result = p.wait()
    stdout, stderr = p.communicate()

    return (stdout, stderr, p.returncode)

def objdump(path, variables, arch):
    result = ObjdumpResult([], {})
    objdump_program = arch.get_objdump_program_name()

    # Handle labels
    stdout, stderr, resultcode = system('%s -t "%s"' % (objdump_program, path))
    if resultcode != 0:
        raise Exception("Error when running %s: '%s'" % (objdump_program, stderr))

    for line in stdout.splitlines():
        cols = line.split('\t')
        if len(cols) != 2:
            continue

        l = cols[0].split()
        r = cols[1].split()

        section = l[-1]
        label_name = r[-1]
        offset = l[0]

        if section != '.text':
            continue

        result.labels[label_name] = int(offset, 16)

    # Handle machine code
    stdout, stderr, resultcode = system('%s -d "%s"' % (objdump_program, path))
    if resultcode != 0:
        raise Exception("Error when running %s: '%s'" %  (objdump_program, stderr))

    section_marker = 'Disassembly of section (.*?):'

    section = None
    offset = None

    variable_occurrences = {}

    for line in stdout.split('\n'):
        line = line.strip()
        if len(line) == 0:
            continue

        m = re.match(section_marker, line)
        if m:
            section = m.groups()[0]
        elif section == '.text':
            m = re.match('([0-9a-f]+) <(.*?)>:', line)
            if m:
                #offset, label = m.groups()
                #offset = int(offset, 16)
                #assert label not in result.labels
                #result.labels[label] = offset
                continue

            columns = line.split('\t')
            if not (2 <= len(columns) <= 3 if arch.is_x86() else 4) :
                raise Exception('Invalid line: %s' % columns)

            offset, instructions = columns[:2]
            if len(columns) == 3:
                result.code[int(offset.strip(':'), 16)] = columns[2]

            # The ARM disassembler doesn't put spaces between byte like the x86
            # disassembler. We should check the size of the code.
            machine_code = instructions.strip().split(' ')
            machine_code_bytes = []
            for mcode in machine_code:
                if len(mcode) > 2:
                    for byte in map(''.join, zip(*[iter(mcode)] * 2)):
                        print "byte entering: ", byte
                        machine_code_bytes.append(byte)
                else:
                    machine_code_bytes.append(mcode)

            result.bytes += machine_code_bytes
        else:
            pass

    result.variable_occurrences = variable_occurrences

    # TODO: do this only with the variables actually occurring in each instruction, to reduce chance for error
    # Find occurrences of variables in machine code
    for variable, magic in variables.iteritems():
        for pos in find_list(result.bytes, address_to_bytes(magic)):
            variable_occurrences[variable] = variable_occurrences.get(variable, []) + [pos]

    return result
