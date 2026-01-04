#!/usr/bin/env python3
import sys

def asm_to_cpp(asm_file, cpp_file):
    with open(asm_file, 'r') as f:
        asm_content = f.read()
    
    # Use C++11 raw string literal - no escaping needed
    cpp_content = '__asm__(R"__asm__(\n' + asm_content + ')__asm__");\n'
    
    with open(cpp_file, 'w') as f:
        f.write(cpp_content)

if __name__ == '__main__':
    if len(sys.argv) != 3:
        print(f'Usage: {sys.argv[0]} <input.asm> <output.cpp>')
        sys.exit(1)
    
    asm_to_cpp(sys.argv[1], sys.argv[2])
