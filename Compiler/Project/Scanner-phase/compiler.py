import sys
import os
from collections import defaultdict
from scanner import Scanner

#in this functin we write the outputs into files
def write_output_files(tokens, errors, symbol_table):
    try:
        write_tokens(tokens)
        write_errors(errors)
        write_symbol_table(symbol_table)
    except IOError as e:
        print(f"Error writing output files: {e}", file=sys.stderr)
        sys.exit(1)


#in this function we store the tokens we calculated into the tokens.txt file
def write_tokens(tokens):
    #creating the text file
    with open('tokens.txt', 'w') as f:
        if not tokens:
            f.write("No tokens found.\n")
            return
            
        #group tokens by line number
        lines = defaultdict(list)
        for line_num, token in tokens:
            lines[line_num].append(token)
        
        #write tokens line by line
        for line_num in sorted(lines):
            token_strings = [f"({t[0]}, {t[1]})" for t in lines[line_num]]
            f.write(f"{line_num}.\t{' '.join(token_strings)}\n")

#in this function we store the errors we calculated into the lexical_errors.txt file
def write_errors(errors):
    #creating the text file
    with open('lexical_errors.txt', 'w') as f:
        if not errors:
            f.write("No lexical errors found.\n")
            return
            
        #group errors by line number
        error_lines = defaultdict(list)
        for line_num, error_msg in errors:
            error_lines[line_num].append(error_msg)
        
        #write errors line by line
        for line_num in sorted(error_lines):
            f.write(f"{line_num}.\t{' '.join(error_lines[line_num])}\n")

#in this function we store the symbols we calculated into the symbol_table.txt file
def write_symbol_table(symbol_table):
    #creating the text file
    with open('symbol_table.txt', 'w') as f:
        if not symbol_table:
            f.write("Symbol table is empty.\n")
            return
            
        #write symbols in order with numbering
        for idx, lexeme in enumerate(symbol_table.keys(), 1):
            f.write(f"{idx}.\t{lexeme}\n")


#this is the main body
if __name__ == "__main__":
    #we read the code here
    input_file = 'input.txt'
    if not os.path.exists(input_file):
        print(f"Error: Input file '{input_file}' not found.", file=sys.stderr)
        sys.exit(1)
    #then we gather the errors and tokens and symbol table
    try:
        #we call the scanner cunstructor so it calculate the things we want
        scanner = Scanner(input_file)
        tokens, errors, symbol_table = scanner.scan()   #calling the scan function will do it
        write_output_files(tokens, errors, symbol_table)
        print("Scanning completed successfully. Output files generated.")
    except Exception as e:
        print(f"Error during scanning: {e}", file=sys.stderr)
        sys.exit(1)
