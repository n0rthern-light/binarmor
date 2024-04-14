# Advanced Memory program
Program made from passion to Windows internals.

## Quick design overview
The program is designed from two components the Loader and the DLL (engine). The loader source code is placed in `src` subdirectory, where the DLL code is inside `src_dll`. Both the loader and the dll share same code from `shared` directory.

## Compiling the components

All available builds are Windows PE x86 executables.

| Build Type | Module | Command |
|------------|--------|---------|
| Debug | Loader | `make debug` |
| Debug | DLL | `make debug_dll` |
| Release | Loader | `make release` |
| Release | DLL | `make release_dll` |

To build everything at once run `make`.

## Cleaning build directories

To remove build directories simply run
```
make clean
```