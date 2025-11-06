# TodoListBubble
Is a `Todo List` software used to develop the `BubbleGUI` library.

# Instalation:
Install the `binaries` here:
![latest](https://img.shields.io/github/v/tag/D4nielStone/todo_list_bubble)

---

# Compilation Guide:

## Windows
You need:

 - CMake → the build system generator
   - 🔗 Download from https://cmake.org/download/
 - Compiler toolchain:
   - MinGW or LLVM/Clang → if you prefer GCC-style.
   - 🔗 Download from https://sourceforge.net/projects/mingw/

**cmake command**:
```bash 
cmake -S . -B out -G "MinGW Makefiles"
cmake --build out
```

---
## Linux
You will just need to install `build-essential` and `libglfw3-dev` with your package manager.
**cmake command**:
```bash 
cmake -S . -B out
cmake --build out
```