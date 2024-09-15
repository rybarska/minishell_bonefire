# Minishell

A simple command line interpreter written in C, taking the Bourne-Again Shell (`bash`) as inspiration.

## Description

Minishell is a small-scale shell that allows you to execute commands, manage files, and navigate the file system.
It's one of our biggest projects in 42 school that involves writing a shell with basic features like command execution, pipelines, I/O redirection, and built-in commands.

## Features

- **Prompt Display**: Shows a prompt when waiting for a new command.
- **Command History**: Keeps a history of executed commands.
- **Command Execution**: Searches and runs executables based on the `PATH` environment variable or using a relative/absolute path.
- **Hashing**: Uses a simple hashtable to remember utility locations. Building a path for commands is necessary only once. If `PATH` changes, the hashtable gets automatically cleared.
- **Signal Handling**: Properly handles `Ctrl-C` and `Ctrl-\` similar to bash.
  - `Ctrl-C`: In parent process: displays a new prompt on a new line. Default `SIGINT` in children.
  - `Ctrl-\`: Ignored in parent process. Default `SIGQUIT` in children.
  - `Ctrl-D` (this is actually not a signal, but `EOF`): can be used to delimit a heredoc or exit the shell.
- **Quotes**:
  - Single quotes `'`: Prevent the shell from interpreting metacharacters in the quoted sequence.
  - Double quotes `"`: Prevent interpretation of metacharacters except for `$` (dollar sign).
- **Variable expansion**:
  - Handles the expansion of environment variables using `$`. For any `NAME=value` present in `env`, `$NAME` in the command line gets replaced with `value`. Word splitting is performed on `value` (except for redirections).
- **Redirections**:
  - `<`: Input redirection.
  - `>`: Output redirection.
  - `<<` (heredoc): Reads input until a delimiter is found.
  - `>>`: Output redirection in append mode.
- **Pipes**: Supports the `|` character to connect commands.
- **Exit Status**: Supports `$?` to get the exit status of the last executed command.

## Built-in Commands

- `echo` with `-n` option: prints its arguments. `-n` removes the trailing newline.
- `cd` with a relative or absolute path: changes directory.
- `pwd` without options: prints the name of the current/working directory.
- `export` with arguments: sets the value of a new or existing environment variable. Local assignment is also supported to an extent.
- `unset` with arguments: removes an existing variable from the environment list.
- `env` without options or arguments: displays the environment variable list.
- `hash` without options or arguments: displays all key/value pairs currently stored in the hashtable.
- `exit` with one argument: exits the shell with `argument` exit status.

## Installation and use

Clone the repository, compile the source code & run the executable:

```
git clone https://github.com/rybarska/minishell_bonefire.git
cd minishell_bonefire
make
./minishell
```
Be aware that it will probably not run on your mac for our use of x86-64 inline Assembly.
