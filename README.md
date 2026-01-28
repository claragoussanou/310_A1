# 310_A1
To compile shell: make mysh
To recompile shell after editing： make clean ; make mysh

To run from command line: ./mysh                            # INTERACTIVE MODE
To run using an input file: ./mysh < input_file.txt         # BATCH MODE

Commands already supported on the shell: !! case sensitive
help | quit | set VAR STRING | print VAR | source SCRIPT.TXT

OUR TASKS:
1. add echo command
2. fix batch mode so that $ is not displayed on every line and it terminates after unning all instructions in the file
3. add my_ls command
4. add my_mkdir command
5. add my_touch command
6. add my_cd command