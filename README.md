# BinArmor 
Binary Armor protection Software.

### A proposed build architecture
```
build
├── debug
│   ├── linux
│   │   ├── x86
│   │   └── x86_64
│   ├── osx
│   │   ├── arm64
│   │   ├── fat
│   │   └── x86_64
│   └── windows
│       └── x86_64
└── release
    ├── linux
    │   ├── x86
    │   └── x86_64
    ├── osx
    │   ├── arm64
    │   ├── fat
    │   └── x86_64
    └── windows
        └── x86_64
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
