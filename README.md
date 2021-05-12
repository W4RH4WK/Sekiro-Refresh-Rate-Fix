# Sekiro Refresh Rate Fix

Sekiro forces the monitors refresh rate to 60 Hz when running in full-screen.
This makes simple frame-rate unlocks useless, unless you run Sekiro in window mode.
These interceptor DLLs prevent changes to the refresh rate.

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
