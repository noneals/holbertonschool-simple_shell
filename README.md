# Simple Shell

A simple UNIX command interpreter written in C that replicates the basic functionality of `/bin/sh`.

## Description

This project is a simple shell implementation that can execute commands in both interactive and non-interactive modes. It handles command execution, PATH searching, built-in commands, and proper exit status management without using forbidden functions like `getenv`.

## Features

✅ Display a prompt and wait for user input  
✅ Execute commands with absolute paths (`/bin/ls`)  
✅ Execute commands using PATH environment variable (`ls`)  
✅ Handle command lines with arguments (`ls -l /tmp`)  
✅ Implement custom PATH searching without `getenv`  
✅ Handle the `exit` built-in command with proper exit status  
✅ Handle the `env` built-in command  
✅ Handle end of file condition (Ctrl+D)  
✅ Proper exit status handling (0, 127, etc.)  
✅ No memory leaks (Valgrind clean)  
✅ No fork called if command doesn't exist

## Compilation

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```

## Usage

### Interactive Mode

```bash
$ ./hsh
$ /bin/ls
builtin.c  find_path.c  main.c  main.h  README.md  run_command.c  shell.c
$ ls
builtin.c  find_path.c  main.c  main.h  README.md  run_command.c  shell.c
$ ls -l /tmp
total 20
drwx------ 3 root root 4096 Nov  5 12:09 systemd-private
$ pwd
/home/user/simple_shell
$ exit
$
```

### Non-Interactive Mode

```bash
$ echo "/bin/ls" | ./hsh
builtin.c  find_path.c  main.c  main.h  README.md  run_command.c  shell.c
$ echo "ls -la" | ./hsh
total 100
drwxrwxr-x 3 user user  4096 Nov  5 10:00 .
drwxrwxr-x 8 user user  4096 Nov  5 09:00 ..
-rw-rw-r-- 1 user user  1234 Nov  5 10:00 main.c
$ cat commands.txt | ./hsh
```

## Project Structure

### Files

| File            | Description                                       | Functions                                                     |
| --------------- | ------------------------------------------------- | ------------------------------------------------------------- |
| `main.h`        | Header file with function prototypes and includes | N/A                                                           |
| `main.c`        | Main entry point and shell loop                   | `main` (1)                                                    |
| `shell.c`       | Core shell functions (prompt, read, parse, free)  | `display_prompt`, `read_line`, `parse_line`, `free_array` (4) |
| `find_path.c`   | PATH searching without using `getenv`             | `get_path_env`, `find_path` (2)                               |
| `run_command.c` | Command execution and process management          | `fork_and_execute`, `execute_command` (2)                     |
| `builtin.c`     | Built-in commands implementation                  | `handle_exit`, `handle_env`, `is_builtin` (3)                 |
| `AUTHORS`       | List of project contributors                      | N/A                                                           |
| `README.md`     | Project documentation (this file)                 | N/A                                                           |

**Total: 12 functions across 5 files (max 4 per file ✅)**

### Key Functions

#### `main.c`

- `main()` - Entry point, manages shell loop and exit status

#### `shell.c`

- `display_prompt()` - Displays shell prompt `$`
- `read_line()` - Reads input from user using `getline`
- `parse_line()` - Parses input into array of arguments
- `free_array()` - Frees allocated memory for argument array

#### `find_path.c`

- `get_path_env()` - Gets PATH from `environ` without `getenv`
- `find_path()` - Searches for command in PATH directories

#### `run_command.c`

- `fork_and_execute()` - Forks and executes command with proper exit status
- `execute_command()` - Main execution logic, returns correct exit codes

#### `builtin.c`

- `handle_exit()` - Handles `exit` command with last exit status
- `handle_env()` - Prints environment variables
- `is_builtin()` - Checks and executes built-in commands

## Built-in Commands

| Command | Description                                  | Usage  |
| ------- | -------------------------------------------- | ------ |
| `exit`  | Exit the shell with last command exit status | `exit` |
| `env`   | Print all environment variables              | `env`  |

## Exit Status Codes

| Code  | Meaning           | Example                       |
| ----- | ----------------- | ----------------------------- |
| `0`   | Success           | Command executed successfully |
| `1`   | General error     | Fork failure, system error    |
| `2`   | Misuse of command | `ls /nonexistent` returns 2   |
| `127` | Command not found | `invalidcmd`                  |

## Examples

### Example 1: Basic Commands

```bash
$ ./hsh
$ ls
file1  file2  file3
$ /bin/pwd
/home/user
$ exit
$ echo $?
0
```

### Example 2: Command Not Found

```bash
$ ./hsh
$ invalidcommand
./hsh: 1: invalidcommand: not found
$ exit
$ echo $?
127
```

### Example 3: Exit Status Preservation

```bash
$ ./hsh
$ ls /nonexistent
ls: cannot access '/nonexistent': No such file or directory
$ exit
$ echo $?
2
```

### Example 4: PATH Handling

```bash
$ ./hsh
$ ls
# Works - finds /bin/ls via PATH
$ /bin/ls
# Works - absolute path
$ ./hsh
# Fails - not in PATH or current directory
```

## Technical Details

### Memory Management

- All allocated memory is properly freed
- No memory leaks (verified with Valgrind)
- `exit` command frees all resources before exiting

### Process Management

- Uses `fork()` to create child processes
- Uses `execve()` to execute commands
- Uses `waitpid()` to wait for child and get exit status
- Uses `WIFEXITED()` and `WEXITSTATUS()` macros

### PATH Handling

- Custom `get_path_env()` function replaces forbidden `getenv()`
- Searches through `environ` array directly
- Handles empty PATH correctly
- Returns NULL for commands not found in PATH

### Allowed Functions

```
access, chdir, close, closedir, execve, exit, _exit, fflush, fork, free,
getcwd, getline, getpid, isatty, kill, malloc, open, opendir, perror,
read, readdir, signal, stat, lstat, fstat, strtok, wait, waitpid, wait3,
wait4, write, strdup, strlen, strcmp, strncmp, sprintf
```

**Note:** `getenv` is NOT used - we access `environ` directly.

## Authors

See [AUTHORS](AUTHORS) file for the list of contributors.

- **Abdulaziz Hamed** - [@aziz5g-tech](https://github.com/aziz5g-tech)
- **Norah Mohammed** - [@noneals](https://github.com/noneals)

## Requirements

### Environment

- Ubuntu 20.04 LTS
- GCC compiler version 9.4.0 or later

### Compilation Flags

```bash
-Wall -Werror -Wextra -pedantic -std=gnu89
```

### Code Style

- Betty style compliant
- Maximum 5 functions per file
- Maximum 40 lines per function
- Proper documentation for all functions

## Testing

### Manual Testing

```bash
# Compile
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh

# Interactive mode
./hsh

# Non-interactive mode
echo "ls" | ./hsh

# Test with multiple commands
echo -e "ls\npwd\nexit" | ./hsh
```

### Memory Leak Testing

```bash
valgrind --leak-check=full --show-leak-kinds=all ./hsh
```

Expected output:

```
HEAP SUMMARY:
    in use at exit: 0 bytes in 0 blocks
  total heap usage: X allocs, X frees

LEAK SUMMARY:
   definitely lost: 0 bytes in 0 blocks
```

### Style Checking

```bash
betty *.c *.h
```

## Project Information

This project is part of the **Holberton school Software Engineering Program** curriculum.

- **Project:** 0x16. C - Simple Shell
- **Language:** C
- **Standard:** gnu89
- **Requirements:** Ubuntu 20.04 LTS

## License

This project is for educational purposes as part of the Holberton school Software Engineering program.

---

**Note:** This shell is a learning project and is not intended for production use.
