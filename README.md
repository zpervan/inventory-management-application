# Inventory Management Application #

A Windows based C++ application for inventory management and monitoring.

## Setup ##

* Development environment: [MSYS2 (MinGW64)](https://www.msys2.org/)
* Database: [PostgreSQL](https://www.postgresql.org/)
* GUI: [DearImgui](https://github.com/ocornut/imgui)
* Testing framework: [Google Test](https://github.com/google/googletest)

## Configuration ##

Navigate to the root of the repository and execute the following:

```shell
mkdir -p build
cmake .. -DCMAKE_C_COMPILER=C:/msys64/mingw64/bin/clang.exe -DCMAKE_CXX_COMPILER=C:/msys64/mingw64/bin/clang++.exe -G "CodeBlocks - MinGW Makefiles" 
cmake --build .
.\InventoryManagementApplication.exe
```

## Additional ##

TODO
