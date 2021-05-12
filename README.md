# Sekiro Refresh Rate Fix

## Install Pre-compiled

Grab latest release and place `d3d11.dll` and `dxgi.dll` inside Sekiro install directory (e.g. `F:\SteamLibrary\steamapps\common\Sekiro`).

## Build It Yourself

Prerequisites:

- Visual Studio with C++ compiler
- DirectX SDK
- [CMake](https://cmake.org/)

Build:

- Grab sources from Github
- Open Visual Studio x64 native command prompt and navigate to sources
- Run `cmake.exe -G "Visual Studio 16 2019" -B build`
- Run `cmake.exe --build build --config Release`
- DLLs are located in `build/Release`
