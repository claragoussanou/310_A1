This solution uses the starter code

-------------------------------------------------------------------------------------------------------------------------
this part is for us and should be deleted before we submit !!!
# 310_A1
To compile shell: make mysh
To recompile shell after editing： make clean ; make mysh

To run from command line: ./mysh                               # INTERACTIVE MODE
To run using an input file: ./mysh < input_file.txt            # BATCH MODE

Commands already supported on the shell: !! case sensitive
help | quit | set VAR STRING | print VAR | source SCRIPT.TXT

OUR TASKS:
1. [ DONE ] add echo command
2. [ DONE ] fix batch mode
    - [ DONE ] $ is not displayed on every line
    - [ DONE ] terminates after running all instructions in the file
3. [ DONE ] add my_ls command
4. [ DONE ] add my_mkdir command
5. [ DONE ] add my_touch command
6. add my_cd command
7. implement one-liners
8. add run command