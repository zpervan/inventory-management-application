# Inventory Management Application #

A Windows based C++ application for inventory management and monitoring.

## Prerequisites ##

* Development environment: [MSYS2 (MinGW64)](https://www.msys2.org/) or [MSVC19](https://docs.microsoft.com/en-us/visualstudio/extensibility/installing-the-visual-studio-sdk?view=vs-2019)
* Database: [PostgreSQL](https://www.postgresql.org/)
* GUI: [DearImgui](https://github.com/ocornut/imgui)
* Testing framework: [Google Test](https://github.com/google/googletest)

## Setup ##

1. Install the MSYS2 (MinGW) environment by following [this](https://www.msys2.org/) tutorial OR install MSVC19 environment 
2. You can use CMake and Make which comes installed with MSYS2 to build your project or download
   the [official CMake](https://cmake.org/) for Windows

## Workflow ##

This section contains all necessary steps to configure the project, build the targets and run the executable. In order
to execute the above-mentioned workflow, navigate to the root of the repository and execute the following:

```shell
mkdir -p build
cmake .. -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/clang.exe -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/clang++.exe -G "CodeBlocks - MinGW Makefiles" 
cmake --build .
.\InventoryManagementExecutable.exe
```

Currently, there are two executable targets in the projects:

* `InventoryManagement` - The main executable which runs the inventory management application
* `ImguiDemo` - Demo application executable which comes included with the DearImgui library (handy for examples)

## Additional ##

TODO
