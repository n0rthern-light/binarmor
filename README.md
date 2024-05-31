# BinArmor
<img width="809" alt="binarmor-alpha" src="https://github.com/n0rthern-light/binarmor/assets/45363185/2626f691-f911-4850-97ff-1f16da38d7fe">

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
ln -sf build/debug-osx-fat/compile_commands.json compile_commands.json
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

Regarding Command/Event bus communication:
Every module has its components (classes, objects, functions) and an application layer used to manage those component relations and actions in a clear and a ready to change approach. The rules of using command / event communication aim to make the flow of control easy to follow and easy to read:
- components can only publish events
- components cannot publish commands
- components can only subscribe to commands
- components cannot subscribe to events
- application can only publish commands
- application cannot publish events
- application can only subscribe to events
- application cannot subscribe to commands

