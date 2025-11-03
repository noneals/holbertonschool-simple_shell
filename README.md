# Simple Shell

A simple UNIX command interpreter written in C.

## Description

This is a simple shell program that can execute commands in both interactive and non-interactive modes. It replicates basic functionality of the sh shell.

## Features

- Display a prompt and wait for user input
- Execute simple commands
- Handle command lines with arguments
- Implement the PATH to find executables
- Handle the "exit" built-in command
- Handle the "env" built-in command
- Handle end of file condition (Ctrl+D)

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
$ /bin/ls
hsh main.c shell.c
$ exit
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c
$ cat test_file | ./hsh
```

## Files

- `main.h` - Header file with function prototypes and includes
- `main.c` - Main entry point of the shell
- `shell.c` - Core shell functions (prompt, read, parse)
- `execute.c` - Command execution and PATH handling
- `README.md` - This file

## Authors

- Abdulaziz Hamed (aziz5g-tech)
- Norah Mohammed (noneals)

## Requirements

- Ubuntu 20.04 LTS
- gcc compiler with flags: -Wall -Werror -Wextra -pedantic -std=gnu89
- Betty style compliant

## Betty Style

All code follows the Betty coding style guidelines.
