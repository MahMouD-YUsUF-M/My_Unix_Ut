
## 📋 Table of Contents

- [Overview](#overview)
- [Shell Implementations](#shell-implementations)
- [Unix Utilities](#unix-utilities)
- [Feature Comparison](#feature-comparison)
- [Getting Started](#getting-started)
- [Usage Examples](#usage-examples)
- [Testing](#testing)
- [Technical Details](#technical-details)
- [Performance Benchmarks](#performance-benchmarks)
- [Troubleshooting](#troubleshooting)
- [Educational Value](#educational-value)
- [Contributing](#contributing)
- [License](#license)

## 🔍 Overview

This repository contains a progressive series of Unix shell implementations, each building upon the previous with additional features and complexity. Additionally, it includes custom implementations of essential Linux commands, providing a comprehensive understanding of system-level programming in C.

## 🐚 Shell Implementations

The repository includes four shell implementations, each demonstrating different levels of complexity:

### 1. Femtoshell
- **Purpose**: Minimal shell implementation
- **Features**: 
  - Basic command parsing with `strtok()`
  - Built-in commands: `exit`, `echo`
  - Simple input validation
  - No external command execution
- **Complexity**: Beginner level

### 2. Picoshell
- **Purpose**: Enhanced basic shell with process management
- **Features**: 
  - All femtoshell features plus:
  - **Built-in Commands**: `cd`, `pwd`, `export`
  - **Variable Assignment**: Direct variable setting (`VAR=value`)
  - **External Commands**: Fork/exec model for system commands
  - **Process Management**: Basic `waitpid()` implementation
  - **Error Handling**: System call error reporting
- **Complexity**: Intermediate beginner

### 3. Nanoshell
- **Purpose**: Feature-rich shell with variable expansion
- **Features**: 
  - All picoshell features plus:
  - **Variable Expansion**: Full environment variable substitution (`$VAR`)
  - **Enhanced Parsing**: Dynamic string expansion and reconstruction
  - **Memory Management**: Dynamic allocation with `strdup()`
  - **Improved Error Handling**: More robust validation
  - **I/O Redirection**: Partial implementation (variables declared but incomplete)
- **Complexity**: Intermediate

### 4. Microshell
- **Purpose**: Full-featured shell implementation
- **Features**: 
  - All nanoshell features plus:
  - **Complete I/O Redirection**: Input (`<`), Output (`>`), Error (`2>`)
  - **Advanced Variable Expansion**: Comprehensive `$VAR` substitution
  - **Robust Memory Management**: Complete cleanup and leak prevention
  - **Enhanced Security**: Input validation and buffer overflow protection
  - **Process Management**: Sophisticated fork/exec with proper signal handling
  - **Error Recovery**: Comprehensive error handling with resource cleanup
- **Complexity**: Advanced

## 🛠️ Unix Utilities

Custom C implementations of essential Linux commands:

### Core Commands
- **`pwd`** - Print Working Directory
  - Displays the current working directory path
  - Handles path resolution and error cases

- **`cat`** - Concatenate Files
  - Reads and displays file contents
  - Supports multiple file arguments
  - Proper file handling and error reporting

- **`mv`** - Move/Rename Files
  - Moves files and directories
  - Handles cross-filesystem moves
  - Preserves file permissions and metadata

- **`cp`** - Copy Files
  - Copies files and directories
  - Supports recursive directory copying
  - Maintains file attributes and permissions

## 📊 Feature Comparison

| Feature | Femtoshell | Picoshell | Nanoshell | Microshell |
|---------|------------|-----------|-----------|------------|
| **Basic Commands** | ✅ | ✅ | ✅ | ✅ |
| `exit` | ✅ | ✅ | ✅ | ✅ |
| `echo` | ✅ | ✅ | ✅ | ✅ |
| `cd` | ❌ | ✅ | ✅ | ✅ |
| `pwd` | ❌ | ✅ | ✅ | ✅ |
| `export` | ❌ | ✅ | ✅ | ✅ |
| **Process Management** | ❌ | ✅ | ✅ | ✅ |
| External Commands | ❌ | ✅ | ✅ | ✅ |
| Fork/Exec | ❌ | ✅ | ✅ | ✅ |
| Process Waiting | ❌ | ✅ | ✅ | ✅ |
| **Variable Features** | ❌ | ⚠️ | ✅ | ✅ |
| Variable Assignment | ❌ | ✅ | ✅ | ✅ |
| Variable Expansion ($VAR) | ❌ | ❌ | ✅ | ✅ |
| **I/O Redirection** | ❌ | ❌ | ⚠️ | ✅ |
| Input Redirection (<) | ❌ | ❌ | ❌ | ✅ |
| Output Redirection (>) | ❌ | ❌ | ❌ | ✅ |
| Error Redirection (2>) | ❌ | ❌ | ❌ | ✅ |
| **Memory Management** | ⚠️ | ⚠️ | ✅ | ✅ |
| Dynamic Allocation | ❌ | ❌ | ✅ | ✅ |
| Memory Cleanup | ⚠️ | ⚠️ | ✅ | ✅ |
| **Error Handling** | ⚠️ | ✅ | ✅ | ✅ |
| System Call Errors | ❌ | ✅ | ✅ | ✅ |
| Resource Cleanup | ❌ | ❌ | ✅ | ✅ |

**Legend:** ✅ Fully Implemented | ⚠️ Partially Implemented | ❌ Not Implemented

## ✨ Features

### Microshell Advanced Features

#### I/O Redirection
```bash
# Input redirection
command < input_file

# Output redirection
command > output_file

# Error redirection
command 2> error_file
```

#### Environment Variables
```bash
# Variable expansion
echo $HOME
echo $USER

# Variable assignment
export VAR=value
VAR=value
```

#### Built-in Commands
- `exit` - Graceful shell termination
- `cd [directory]` - Change directory (defaults to $HOME)
- `pwd` - Print current working directory
- `echo [args...]` - Display arguments
- `export VAR=value` - Set environment variables

#### Error Handling
- Comprehensive error messages with `strerror()`
- Proper exit status propagation
- Resource cleanup on errors
- Memory leak prevention

## 🚀 Getting Started

### Prerequisites
- GCC compiler
- Unix/Linux environment
- Standard C library

### Compilation
```bash
# Clone the repository
git clone https://github.com/yourusername/My_Unix_Ut.git
cd My_Unix_Ut

# Compile all shells at once
make all

# Or compile individually
gcc -o femtoshell femtoshell.c
gcc -o picoshell picoshell.c
gcc -o nanoshell nanoshell.c
gcc -o microshell microshell.c

# Compile utilities with error checking
gcc -Wall -Wextra -o mypwd pwd.c
gcc -Wall -Wextra -o mycat cat.c
gcc -Wall -Wextra -o mymv mv.c
gcc -Wall -Wextra -o mycp cp.c

# Create debug versions
gcc -g -DDEBUG -o microshell-debug microshell.c
```

### Quick Setup Script
```bash
#!/bin/bash
# setup.sh - Quick installation script

echo "🔨 Compiling My_Unix_Ut..."

# Compile all shells
for shell in femto pico nano micro; do
    gcc -Wall -Wextra -o ${shell}shell ${shell}shell.c
    if [ $? -eq 0 ]; then
        echo "✅ ${shell}shell compiled successfully"
    else
        echo "❌ ${shell}shell compilation failed"
        exit 1
    fi
done

# Compile utilities
for util in pwd cat mv cp; do
    gcc -Wall -Wextra -o my${util} ${util}.c
    if [ $? -eq 0 ]; then
        echo "✅ my${util} compiled successfully"
    else
        echo "❌ my${util} compilation failed"
        exit 1
    fi
done

# Make executable
chmod +x *shell my*

echo "🎉 All components compiled successfully!"
echo "💡 Try: ./microshell"
```

### Installation
```bash
# Make executables
chmod +x femtoshell picoshell nanoshell microshell
chmod +x mypwd mycat mymv mycp

# Optional: Add to PATH
export PATH=$PATH:$(pwd)
```

## 📚 Usage Examples

### Femtoshell - Basic Commands
```bash
./femtoshell
Femto shell prompt >echo Hello World
Hello World

Femto shell prompt >echo Testing multiple arguments
Testing multiple arguments

Femto shell prompt >invalid_command
Invalid command

Femto shell prompt >exit
Good Bye
```

### Picoshell - Process Management
```bash
./picoshell
Nano shell prompt > pwd
/home/user/My_Unix_Ut

Nano shell prompt > cd /tmp
Nano shell prompt > pwd
/tmp

Nano shell prompt > export PATH=/usr/bin
Nano shell prompt > VAR=hello
Nano shell prompt > ls -la
# Executes external ls command

Nano shell prompt > exit
Good Bye
```

### Nanoshell - Variable Expansion
```bash
./nanoshell
Nano shell prompt > export HOME=/home/user
Nano shell prompt > echo $HOME
/home/user

Nano shell prompt > TEST=world
Nano shell prompt > echo Hello $TEST
Hello world

Nano shell prompt > cd $HOME
Nano shell prompt > pwd
/home/user

Nano shell prompt > exit
Good Bye
```

### Microshell - Full Features
```bash
./microshell
micro shell prompt > pwd
/home/user/My_Unix_Ut

micro shell prompt > export TEST=hello
micro shell prompt > echo $TEST
hello

micro shell prompt > ls > output.txt
micro shell prompt > cat < input.txt > processed.txt
micro shell prompt > command_with_error 2> errors.log
micro shell prompt > cd /tmp
micro shell prompt > pwd
/tmp

micro shell prompt > exit
Good Bye
```

### Using Custom Utilities
```bash
# Print working directory
./mypwd

# Display file contents
./mycat file.txt
./mycat file1.txt file2.txt

# Copy files
./mycp source.txt destination.txt
./mycp -r source_dir/ dest_dir/

# Move/rename files
./mymv oldname.txt newname.txt
./mymv file.txt /path/to/destination/
```

## 🧪 Testing

### Automated Test Suite

The repository includes comprehensive tests for all shells and utilities:

```bash
# Run all tests
make test

# Run specific shell tests
./tests/test_femtoshell.sh
./tests/test_picoshell.sh
./tests/test_nanoshell.sh
./tests/test_microshell.sh

# Run utility tests
./tests/test_utilities.sh

# Performance benchmarks
./tests/benchmark.sh
```


## 🔧 Technical Details

### Architecture
- **Process Model**: Fork-exec pattern for external commands
- **Memory Management**: Dynamic allocation with proper cleanup
- **Error Handling**: Systematic error checking and reporting
- **Signal Handling**: Proper child process management

### Key Components

### Key Components

#### Progressive Feature Development

**Femtoshell Architecture:**
- Simple string tokenization with `strtok()`
- Basic built-in command matching
- No process creation or external commands
- Minimal error handling

**Picoshell Enhancements:**
- Fork-exec process model introduction
- System call integration (`chdir`, `getcwd`)
- Basic environment variable handling with `putenv()`
- Process synchronization with `waitpid()`

**Nanoshell Advanced Features:**
- Dynamic variable expansion algorithm
- Complex string manipulation and reconstruction
- Memory allocation with `strdup()` and proper cleanup
- Enhanced parsing for environment variables

**Microshell Complete Implementation:**
- File descriptor manipulation with `dup2()`
- Comprehensive I/O redirection system
- Advanced memory management with cleanup functions
- Robust error handling with `strerror()` integration

## 📈 Performance Benchmarks

### Shell Performance Comparison

```bash
# Benchmark script (tests/benchmark.sh)
#!/bin/bash

echo "🚀 Performance Benchmarks"
echo "========================="

benchmark_shell() {
    local shell=$1
    local commands=1000
    
    echo "Testing $shell with $commands commands..."
    
    time_result=$( { time for i in $(seq 1 $commands); do echo "echo test"; done | timeout 60 ./$shell > /dev/null; } 2>&1 )
    
    echo "$shell: $time_result"
}

# Run benchmarks
benchmark_shell "femtoshell"
benchmark_shell "picoshell" 
benchmark_shell "nanoshell"
benchmark_shell "microshell"
```

### Memory Usage Analysis
```bash
# Memory profiling with valgrind
valgrind --tool=massif --pages-as-heap=yes ./microshell

# Check for memory leaks
valgrind --leak-check=full --show-leak-kinds=all ./microshell
```


## 🔧 Troubleshooting

### Common Issues and Solutions

#### Issue 1: Compilation Errors
```bash
# Error: "limits.h not found"
# Solution: Install build-essential
sudo apt-get update
sudo apt-get install build-essential

# Error: "PATH_MAX undeclared"
# Solution: Add explicit definition
#define PATH_MAX 4096
```

#### Issue 2: Shell Hangs or Infinite Loops
```bash
# Problem: Shell doesn't respond
# Solution 1: Use timeout for testing
timeout 10 ./microshell

# Solution 2: Send interrupt signal
kill -INT <shell_pid>

# Solution 3: Force kill if necessary
kill -9 <shell_pid>
```

#### Issue 3: Variable Expansion Not Working
```bash
# Problem: $VAR not expanding in nanoshell/microshell
# Debug steps:
1. Check if variable is set: echo $VAR
2. Verify shell supports expansion
3. Check for syntax errors in variable name

# Common mistakes:
echo $123VAR    # Invalid: starts with number
echo ${VAR}     # Not supported in basic implementation
echo $         # Special variables not implemented
```

#### Issue 4: I/O Redirection Failures
```bash
# Problem: Redirection not working in microshell
# Debug steps:
1. Check file permissions: ls -la target_file
2. Verify directory exists: ls -la target_directory
3. Test with simple commands first

# Example debugging:
echo "test" > /tmp/debug.txt    # Should work
cat < /nonexistent.txt          # Should show error
```

#### Issue 5: Memory Leaks
```bash
# Use valgrind to identify leaks
valgrind --leak-check=full ./microshell

# Common leak sources:
1. Unreleased strdup() memory in nanoshell
2. Unfreed argument arrays
3. Unclosed file descriptors

# Fix by ensuring cleanup in error paths
```


```

## 🎓 Educational Value

### Learning Objectives

This project teaches essential systems programming concepts:

#### **Level 1: Basic Programming (Femtoshell)**
- String manipulation with `strtok()`
- Basic input/output operations
- Simple control structures
- Function organization

#### **Level 2: Process Management (Picoshell)**
- Understanding processes and process creation
- `fork()` and `exec()` system calls
- Process synchronization with `wait()`
- Basic error handling with `perror()`

#### **Level 3: Advanced String Processing (Nanoshell)**
- Dynamic memory allocation
- Complex string parsing algorithms
- Environment variable handling
- Memory management best practices

#### **Level 4: System Programming (Microshell)**
- File descriptor manipulation
- I/O redirection implementation
- Advanced error handling and recovery
- Resource management and cleanup




## 🏗️ Project Structure

```
My_Unix_Ut/
├── src/                      # Source files
│   ├── femtoshell.c         # Minimal shell (echo, exit)
│   ├── picoshell.c          # Basic shell with process management
│   ├── nanoshell.c          # Enhanced shell with variable expansion
│   ├── microshell.c         # Full-featured shell with I/O redirection
│   ├── pwd.c                # Print working directory implementation
│   ├── cat.c                # File concatenation utility
│   ├── mv.c                 # Move/rename files utility
│   └── cp.c                 # Copy files utility
├── tests/                   # Comprehensive test suite
│   ├── test_shells.sh       # Shell functionality tests
│   ├── test_utilities.sh    # Utility command tests
├── build/                   # Compiled binaries (gitignored)
├── Makefile                 # Build configuration with multiple targets
├── setup.sh                 # Automated setup script
├── .gitignore              # Git ignore file
├── LICENSE                  # MIT License
└── README.md               # This comprehensive guide
```


### 🚀 Quick Start for Contributors

1. **Fork and Clone**
```bash
git clone https://github.com/yourusername/My_Unix_Ut.git
cd My_Unix_Ut
git checkout -b feature/your-feature-name
```

2. **Set Up Development Environment**
```bash
# Install dependencies
sudo apt-get install build-essential valgrind gdb

# Run setup script
chmod +x setup.sh
./setup.sh

# Run tests to ensure everything works
make test
```



#### **🛠️ Utility Improvements**
- **Enhanced `cp`**: Add recursive copying with `-r` flag
- **Advanced `mv`**: Cross-filesystem move support
- **Extended `cat`**: Add line numbering (`-n` flag)
- **New Utilities**: Implement `ls`, `grep`, `find`, `wc`




### 🎯 Development Guidelines

#### **Code Style**
```c
// Use consistent indentation (4 spaces)
int main(int argc, char *argv[]) {
    char *buffer = NULL;
    size_t buffer_size = 0;
    
    // Use descriptive variable names
    ssize_t bytes_read = getline(&buffer, &buffer_size, stdin);
    
    // Add error checking for all system calls
    if (bytes_read == -1) {
        perror("getline failed");
        return 1;
    }
    
    // Clean up resources
    free(buffer);
    return 0;
}
```

#### **Testing Requirements**
```bash
# All new features must include tests
./tests/test_new_feature.sh

# Memory leak testing is mandatory
valgrind --leak-check=full ./your_shell

# Performance regression testing
./tests/benchmark.sh
```

#### **Commit Message Format**
```
feat: add pipe support to microshell

- Implement basic pipe parsing
- Add pipe execution with fork/exec
- Include comprehensive tests
- Update documentation

Closes #123
```











---

**Note**: This project is for educational purposes and demonstrates system programming concepts in C. While functional, these implementations may not include all features or optimizations found in production Unix utilities.
