# My_Unix_Ut 🐚

A collection of Unix shell implementations and core system utilities written in C, demonstrating progressive shell development from basic to advanced features.

## 📋 Table of Contents

- [Overview](#overview)
- [Shell Implementations](#shell-implementations)
- [Unix Utilities](#unix-utilities)
- [Features](#features)
- [Getting Started](#getting-started)
- [Usage Examples](#usage-examples)
- [Technical Details](#technical-details)
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

# Compile individual shells
gcc -o femtoshell femtoshell.c
gcc -o picoshell picoshell.c
gcc -o nanoshell nanoshell.c
gcc -o microshell microshell.c

# Compile utilities
gcc -o mypwd pwd.c
gcc -o mycat cat.c
gcc -o mymv mv.c
gcc -o mycp cp.c
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

### Security Considerations
- Buffer overflow protection
- Input validation
- Safe string handling
- Resource limit enforcement

## 🏗️ Project Structure

```
My_Unix_Ut/
├── femtoshell.c          # Minimal shell (echo, exit)
├── picoshell.c           # Basic shell with process management
├── nanoshell.c           # Enhanced shell with variable expansion
├── microshell.c          # Full-featured shell with I/O redirection
├── pwd.c                 # Print working directory implementation
├── cat.c                 # File concatenation utility
├── mv.c                  # Move/rename files utility
├── cp.c                  # Copy files utility
├── Makefile              # Build configuration
├── tests/                # Test scripts and example files
├── examples/             # Usage examples and sample inputs
└── README.md             # This file
```

## 🤝 Contributing

Contributions are welcome! Here's how you can help:

1. **Fork the repository**
2. **Create a feature branch** (`git checkout -b feature/amazing-feature`)
3. **Commit your changes** (`git commit -m 'Add amazing feature'`)
4. **Push to the branch** (`git push origin feature/amazing-feature`)
5. **Open a Pull Request**

### Development Guidelines
- Follow POSIX C standards
- Include comprehensive error handling
- Add comments for complex logic
- Test thoroughly on different systems
- Update documentation as needed

## 📝 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## 📞 Contact

- **GitHub**: [@yourusername](https://github.com/yourusername)
- **Email**: your.email@example.com

## 🙏 Acknowledgments

- Unix/Linux documentation and specifications
- Advanced Programming in the UNIX Environment by W. Richard Stevens
- The C Programming Language by Kernighan and Ritchie
- Open source community contributions

---

**Note**: This project is for educational purposes and demonstrates system programming concepts in C. While functional, these implementations may not include all features or optimizations found in production Unix utilities.
