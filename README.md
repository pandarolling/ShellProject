MyShell – Custom Unix Shell in C
Authors
Timothy Kurian
Shubham Yadav
Overview

MyShell is a lightweight Unix shell built in C that mimics basic behavior of standard shells like bash. It supports executing system commands, handling processes, and includes a few built-in commands.

This project was created to understand process management, system calls, and shell internals.

Features
Execute external commands (ls, cat, pwd, etc.)
Built-in commands:
cd – change directory
help – list commands
exit – terminate shell
Process handling using:
fork()
execvp()
waitpid()
Custom input parsing using getline() / manual buffer
Tokenization using strtok()
How It Works (High Level)
Shell displays prompt: mysh>
User inputs a command
Input is:
Read
Tokenized into arguments
Shell:
Checks if command is built-in
Otherwise creates a new process to execute it
Compilation
gcc myshell.c -o myshell
Run
./myshell
Example
mysh> ls
mysh> pwd
mysh> cd ..
mysh> cat file.txt
mysh> exit
Learning Outcomes
Understanding of Unix system calls
Process creation and control
Basic shell architecture
Memory management in C
Future Improvements
Pipes (|)
Input/output redirection (>, <)
Background processes (&)
Command history
