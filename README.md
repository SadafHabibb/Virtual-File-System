# Virtual File System (VFS)

## Overview
The Virtual File System (VFS) is a C++ implementation of a simulated file system that provides users with a command-line interface for managing folders and files, similar to a Unix-like environment. It supports basic file system operations such as creating, navigating, deleting, and displaying the contents of files and folders. The VFS also includes a "Bin" feature for temporarily storing deleted files before they are permanently removed.

## Features
- **Directory Navigation:** Commands like `cd` allow users to change the current directory.
- **File and Folder Creation:** Use `mkdir` to create directories and `touch` to create files of a specified size.
- **Directory Listing (`ls`):** Display the contents of the current directory with an option to sort files based on size.
- **Path Display (`pwd`):** Show the current directory path.
- **File and Folder Deletion (`rm`):** Remove files or empty folders, which are then sent to a temporary "Bin."
- **Bin Management:** `showbin` to display the contents of the Bin and `emptybin` to restore or permanently delete the items.
- **File/Folder Size Calculation (`size`):** Display the size of a specified file or folder.
- **Search (`find`):** Recursively search for a file or folder by name.
- **Exit Command (`exit`):** Cleanly exit the virtual file system.

## Installation
1. **Clone the repository:**
   ```bash
   git clone https://github.com/yourusername/vfs-project.git
   ```
2. **Compile the project:**
   Make sure you have a C++ compiler (such as `g++`) installed. Use the following command to compile:
   ```bash
   g++ -o vfs main.cpp vfs.cpp inode.cpp queue.cpp -std=c++17
   ```
3. **Run the executable:**
   ```bash
   ./vfs
   ```

## Usage
The VFS provides a variety of commands to interact with the virtual file system:
- `help` - List all available commands and their descriptions.
- `pwd` - Show the current directory path.
- `ls [sort]` - List the contents of the current directory. If `sort` is specified, items will be sorted by size.
- `mkdir <folder_name>` - Create a new folder.
- `touch <file_name> <size>` - Create a new file with a specified size.
- `cd <path>` - Change the current directory. Supports relative, absolute, and special paths like `..` or `/`.
- `rm <file_name>` - Remove a file or empty folder (moves it to the Bin).
- `size <path>` - Show the size of a file or folder.
- `showbin` - Display the contents of the Bin.
- `emptybin` - Permanently delete all items from the Bin.
- `find <name>` - Search for a file or folder in the current directory and subdirectories.
- `exit` - Exit the program.

## Example Commands
```bash
mkdir my_folder
cd my_folder
touch file1.txt 1024
cd ..
ls
rm file1.txt
showbin
emptybin
```

## Implementation Details
The VFS utilizes the following classes:
- **VFS:** Manages file system operations and maintains the state of the virtual file system.
- **Inode:** Represents an inode in the file system, supporting file and folder types.
- **Queue:** Used to implement the Bin for managing recently deleted items.
  
The virtual file system uses an in-memory tree structure, where each `Inode` acts as a node representing a file or directory. Commands manipulate the tree to simulate file system behavior.

## Future Improvements
- Implement file content manipulation (read/write).
- Add permission controls for files and folders.
- Support for symbolic links.
- Persistent storage using serialization.
- Extended search capabilities (wildcards, regular expressions).

## License
This project is open-source and available under the MIT License.

