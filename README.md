# Sekiro Refresh Rate Fix

Sekiro forces the monitors refresh rate to 60 Hz when running in full-screen.
This makes simple frame-rate unlocks useless, unless you run Sekiro in window mode.
These interceptor DLLs prevent changes to the refresh rate.

## Elden Ring

Apparently this also works for Elden Ring - do note that Elden Ring supports online multiplayer and anti-cheat.
So, be sure to only use the DLLs when playing offline with anti-cheat disabled.
However, the DLLs are actually not needed if you are using [Flawless Widescreen](https://www.flawlesswidescreen.org/).
Their plugin takes care of the FPS lock.

## Install Pre-compiled

- Grab `dlls.zip` from the [latest release](https://github.com/W4RH4WK/Sekiro-Refresh-Rate-Fix/releases)
- Extract and place `d3d11.dll` and `dxgi.dll` inside Sekiro install directory (e.g. `F:\SteamLibrary\steamapps\common\Sekiro`).

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
