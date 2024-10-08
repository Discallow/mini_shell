# Minishell Project - 42 School

## Table of Contents
- [About the Project](#about-the-project)
- [Features](#features)
- [Getting Started](#getting-started)
- [Installation](#installation)
- [Usage](#usage)
- [Built-in Commands](#built-in-commands)
- [External Commands](#external-commands)
- [Error Handling](#error-handling)
- [Resources](#resources)
- [Author](#author)

---

## About the Project
Minishell is a simplified, custom shell implementation created as part of the curriculum at 42 School. The goal of this project is to understand how a basic UNIX shell operates and to gain experience in building a command interpreter from scratch. This project is written in C and focuses on process management, input parsing, and executing commands using system calls.

This project adheres to the norms and requirements of the 42 School's "Minishell" project.

---

## Features
Minishell includes the following key features:

- **Prompt display**: Shows a prompt waiting for user input.
- **Execution of commands**: Handles external commands by searching through `$PATH` and forking processes.
- **Built-in commands**: Implements several built-in shell commands like `echo`, `cd`, `pwd`, `export`, `unset`, `env`, and `exit`.
- **Redirections**: Supports input and output redirection using `>` (output redirection), `>>` (append), and `<` (input redirection).
- **Pipes**: Executes commands in sequence while passing output from one to another using pipes (`|`).
- **Environment Variables**: Handles environment variable expansion with `$`.
- **Signals**: Manages signals like `Ctrl-C`, `Ctrl-D`, and `Ctrl-\` to mimic the behavior of a typical shell.
- **Error Handling**: Provides meaningful error messages and handles common shell errors gracefully.

---

## Getting Started

### Prerequisites
To run the minishell project, you'll need:
- A Unix-like environment (Linux or macOS)
- GCC or another C compiler
- The `make` utility
- Basic knowledge of how shells and system calls work

---

## Installation

1. Clone the repository:
   ```bash
   git clone https://github.com/your-username/minishell.git
   cd minishell
## Usage
Once you’ve started minishell, you can type commands just like in a normal shell. The prompt will appear, and you can type built-in or external commands.

Example:
   ```bash
   $ ls -l
   $ cd ..
   $ echo "Hello, Minishell"
   $ cat file.txt | grep pattern
```
## Built-in Commands

`echo`: Print arguments to the standard output.
Usage: echo [-n] [string ...]

`cd`: Change the current directory.
Usage: cd [directory]

`pwd`: Print the current directory.
Usage: pwd

`export`: Set environment variables.
Usage: export VAR=value

`unset`: Remove environment variables.
Usage: unset VAR

`env`: Display environment variables.
Usage: env

`exit`: Exit the shell.
Usage: exit [exit_code]

## External Commands
Minishell supports external commands found in the system's $PATH. For example:

   ```bash
   $ ls
   $ grep
   $ wc
   $ cat
```
You can also combine them with redirections and pipes.

Redirections and Pipes
Redirect output: >, >>
Redirect input: <
Use pipes: |
Example:
   ```bash
   $ cat file.txt | grep search_term > result.txt
```
## Error Handling
Minishell provides error messages when:

A command is not found.
Incorrect arguments are provided to a built-in command.
Redirections or pipes fail.
Invalid syntax is used (e.g., unclosed quotes, incorrect redirection).
For example:
   ```bash
   $ ls | | grep
   minishell: syntax error near unexpected token `|'
```
## Conclusion
Minishell was an exciting and challenging project, and it helped deepen my understanding of how shells work under the hood, from command execution and process handling to signal management and input/output redirection. It was by far my favorite project so far, since it started a journey in working on group projects and the challenges that come with that as well. I was lucky to have a great partner! 
