# MyShell – Custom Unix Shell in C

## Authors
- Timothy Kurian  
- Shubham Yadav  

## Overview
MyShell is a lightweight Unix shell built in C that mimics basic behavior of standard shells like `bash`. It supports executing system commands, handling processes, and includes a few built-in commands.

This project was created to understand **process management, system calls, and shell internals**.

---

## Features
- Execute external commands (`ls`, `cat`, `pwd`, etc.)

### Built-in commands:
- `cd` – change directory  
- `help` – list commands  
- `exit` – terminate shell  

### Process handling using:
- `fork()`
- `execvp()`
- `waitpid()`

- Custom input parsing using `getline()` / manual buffer  
- Tokenization using `strtok()`  

---

## How It Works (High Level)
1. Shell displays prompt: `mysh>`  
2. User inputs a command  
3. Input is:
   - Read  
   - Tokenized into arguments  
4. Shell:
   - Checks if command is built-in  
   - Otherwise creates a new process to execute it  

---

## Compilation
```bash
gcc myshell.c -o myshell
```
## Run
```bash
./myshell
```


## Learning Outcomes
1. Understanding of Unix system calls
2. Process creation and control
3. Basic shell architecture
4. Memory management in C

## Future Improvements
1. Pipes (|)
2. Input/output redirection (>, <)
3. Background processes (&)
4. Command history
