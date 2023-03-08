# When The Chess

h

## Dependencies

- CMake (build system)
- SDL2
- SDL_image 2

## Build
We use CMake with a helper shell script.<br>
For now we use a global recursive method for more simplicity although it's commonly known as a bad pratice.

A script is usable for build.<br>
Usage:
```bash
./cmakebuild.sh [-r]
```
Use the `-r` option to run the executable right after the build if it succeeds.
