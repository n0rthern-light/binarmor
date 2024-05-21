# BinArmor 
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
