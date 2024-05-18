# BinArmor 
Binary Armor: Binary protection Software.

### A proposed build architecture
```
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
```
cd ~/Lib/wxWidgets-3.2.4
```

```
mkdir buildWindows
```

```
cd buildWindows
```

```
../configure --host=x86_64-w64-mingw32 --build=x86_64-unknown-linux-gnu --with-msw --disable-shared --enable-debug
```

```
make -j 20
```

### Compiling wxWidgets-3.2.4 under Unix for MacOS
```
cd ~/Lib/wxWidgets-3.2.4
```

```
mkdir buildOSX
```

```
cd buildOSX
```

```
../configure --enable-debug --with-libtiff=no --disable-shared --with-macosx-version-min=10.10 --enable-universal_binary=x86_64,arm64
```

```
make -j 20
```
