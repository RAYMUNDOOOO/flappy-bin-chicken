# Flappy Bin Chicken

A Flappy Bird clone without any pretty graphics and some gnarly sound effects made by yours truly.

![image](https://github.com/RAYMUNDOOOO/flappy-bin-chicken/assets/120559465/58945626-68f1-4f4d-a5d7-618176e7b8f6)
![image](https://github.com/RAYMUNDOOOO/flappy-bin-chicken/assets/120559465/6ae95356-3555-4066-b46d-c583ca946e0d)
![image](https://github.com/RAYMUNDOOOO/flappy-bin-chicken/assets/120559465/30f3ca5f-86a6-43da-badc-3cf5565651e8)


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
### Requirements
- CMake version greater than 3.20.

### Command Line Instructions
1. Clone this project into the directory of your choosing.
2. From the root directory of this project, create a new directory called `build` and change directories into it.
3. From the command line, call `cmake ..`. If **raylib** has not been installed already, it will clone it and include its `CMakeLists.txt` into the build process of this project.

```sh
git clone git@github.com:RAYMUNDOOOO/flappy-bin-chicken.git
cd flappy-bin-chicken
mkdir build
cd build
cmake ..
```

4. If you are on a Mac or a Linux distribution, CMake will generate a GNU Makefile which you can run by calling `make` in the `build/` directory.
If you are on Windows, it will generate a `*.sln` file. Open it in Visual Studio and then run the project.
