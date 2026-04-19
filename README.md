# Virtual File Directory Management System

A robust C++ console application that simulates a hierarchical file system. This project utilizes advanced data structures to manage virtual files and directories, providing a full suite of management tools from basic creation to complex merging and persistence.

## 📝 Project Description
This system implements a virtualized directory structure where "Directories" act as nodes that can contain other directories or "Files". It is built entirely using custom-implemented data structures, avoiding the standard template library (STL) for core logic to demonstrate a deep understanding of **Trees**, **Stacks**, and **Queues**.

## 💎 Core Concepts & Features
- **Hierarchical Tree Structure**: Manages files and folders as a tree, where directories are parent nodes and files are leaf nodes.
- **CRUD Operations**:
  - **Create**: Add new files (e.g., `.txt`, `.pdf`) or directories.
  - **Read**: List directories in a structured Tree View or search for specific items.
  - **Update**: Rename existing files or directories.
  - **Delete**: Remove individual files or entire directory branches.
- **Advanced File Management**:
  - **Merge**: Combine the contents of two directories.
  - **Move & Copy**: Relocate or duplicate files within the virtual system.
- **Persistence Layer**: Import and export the entire directory state to `TreeFile.txt` to save progress between sessions.
- **Custom Data Structures**: Includes manual implementations of a **Dynamic Stack** and **Queue** for system-level operations.

## 📂 File Structure
* **`main.cpp`**: The user interface. It handles the command loop and coordinates with the `FileDirectoryTree` class.
* **`FileDirectoryTree.h`**: The engine of the project. Contains the logic for tree manipulation, serialization (export), and deserialization (import).
* **`Stack.h` & `Queue.h`**: Support structures used for various tree traversal algorithms (BFS/DFS).
* **`TreeFile.txt`**: A plain text representation of the tree used for data persistence.

## 🚀 How to Run

### 1. Prerequisites
- A C++ compiler (e.g., GCC/MinGW, Clang).
- Ensure all `.h` and `.cpp` files are in the same directory.

### 2. Compilation
Compile the project using the following command:
```bash
g++ main.cpp -o FileSystemApp
```

### 3. Execution
Run the executable:
```bash
./FileSystemApp
```

## 📊 Sample Menu Options
1. **Add Directory**: Create a new folder.
2. **Add File**: Create a file with a specific extension.
3. **List Tree View**: See a visual hierarchy of your virtual drive.
4. **Export to File**: Save your current tree structure to the disk.

## 👤 Author
**Muhammad Yousaf**
