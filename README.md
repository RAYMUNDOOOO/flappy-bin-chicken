# Flappy Bin Chicken

A Flappy Bird clone without any pretty graphics and some gnarly sound effects made by yours truly.

Powered by [raylib](<https://www.raylib.com/>)

## Goals

The purpose of this project was to learn more about C programming and game engine development and architecture
through game development with the [raylib](<https://www.raylib.com/>) framework.

Despite the *very* small scope of the game, it showed me how to:
- Handle application state through a simple state machine
- Use GNU Make before I decided to use CMake so I could develop on both my Windows and Linux machines
- Use CMake as a cross-platform build tool
- Program procedurally as I had ony done object-oriented programming til now

## Building

1. Ensure that you have CMake installed and that it is at least version 3.20.
2. From the root directory of this project, create a new directory called `build` and change directories into it.
3. From the command line, call `cmake ..`. If **raylib** has not been installed already, it will clone it and include its `CMakeLists.txt` into the build process of this project.

```sh
mkdir build
cd build
cmake ..
```

4. If you are on a Mac or a Linux distribution, CMake will generate a GNU Makefile which you can run by calling `make` in the `build/` directory.
If you are on Windows, it will generate a `*.sln` file. Open it in Visual Studio and then run the project.
