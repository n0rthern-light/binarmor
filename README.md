# BinArmor
<img width="804" alt="gui" src="https://github.com/user-attachments/assets/f731ca95-f137-42e4-ac39-454de38f1640" />

Binary Armor: Binary protection Software.

### A proposed build architecture
```zsh
build
├── debug-linux-x86_64
├── debug-osx-arm64
├── debug-osx-fat
├── debug-osx-x86_64
├── debug-windows-x86_64
├── release-linux-x86_64
├── release-osx-arm64
├── release-osx-fat
├── release-osx-x86_64
└── release-windows-x86_64
```

### Compiling wxWidgets-3.2.4 under Unix for Windows Target
```zsh
cd ~/Lib/wxWidgets-3.2.4
```

```zsh
mkdir buildWindows
```

```zsh
cd buildWindows
```

```zsh
../configure --host=x86_64-w64-mingw32 --build=x86_64-unknown-linux-gnu --with-msw --disable-shared --enable-debug
```

```zsh
make -j 20
```

### Compiling wxWidgets-3.2.4 under Unix for MacOS
```zsh
cd ~/Lib/wxWidgets-3.2.4
```

```zsh
mkdir buildOSX
```

```zsh
cd buildOSX
```

```zsh
../configure --enable-debug --with-libtiff=no --disable-shared --with-macosx-version-min=10.10 --enable-universal_binary=x86_64,arm64
```

```zsh
make -j 20
```

### Creating symlink for Clangd LSP on MacOS
In order to fix some issues related to not present compile_commands.json like for example missing library symbols, warnings about invalid header imports etc.
Make sure that in Cmake the global setting is set: `set(CMAKE_EXPORT_COMPILE_COMMANDS ON)` - this will generate compile_commands.json in the build directory;
Afterwards create this symlink in the root directory of the project to make LSP capable of resolving the compile commands:

```zsh
ln -sf build/debug-osx-arm64/compile_commands.json compile_commands.json
```

### Coding architecture
Regarding the codebase architecture, the concept is quite simple. We got three modules:
- `core` aka Engine - where all recipes of doing stuff lives.
- `loader` - the User Interface module
- `shared` - very generic stuff that can be used independently anywhere.

The dependencies rules are:
- The `shared` depends on itself only. 
- The `core` depends on itself and the `shared` module stuff only. 
- The `loader` depends on itself, the `shared` module, and the `core` stuff - it is the highest level module. 
- Any of the modules can depend on external libraries as well, but the dependency must be hidden behind abstract interface.

### MacOS ARM64 target under MacOS/unix Host:
1. Install packages it will install arm64 libraries:
Debug:
```zsh
conan install . --build=missing --settings=build_type=Debug --profile:host=conan-profiles/osx_arm64.ini
```

Release:
```zsh
conan install . --build=missing --settings=build_type=Release --profile:host=conan-profiles/osx_arm64.ini
```

### MacOS X64 target under MacOS/unix Host:
1. Install packages it will install x86_64 libraries:
Debug:
```zsh
conan install . --build=missing --settings=build_type=Debug --profile:host=conan-profiles/osx_x64.ini
```

Release:
```zsh
conan install . --build=missing --settings=build_type=Release --profile:host=conan-profiles/osx_x64.ini
```

### Windows compiling under MacOS/unix Host:
1. make sure mingw installed:
```zsh
brew install mingw-w64
```

2. Create toolchain file for example in ~/toolchain/windows.tc.cmake
Example toolchain, might be adjusted:
```zsh
set(CMAKE_SYSTEM_NAME Windows)

set(CMAKE_C_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-g++)
set(CMAKE_RC_COMPILER /opt/homebrew/bin/x86_64-w64-mingw32-windres)

set(CMAKE_FIND_ROOT_PATH /opt/homebrew/opt/mingw-w64/toolchain-x86_64/mingw)

set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY BOTH)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE BOTH)
```

3. Build conan dependencies with correct Host Profile (Target platform build):
```zsh
conan install . --build=missing --settings=build_type=Debug --profile:host=conan-profiles/windows_x64.ini
```

4. Specify the toolchain in the CMake when building
