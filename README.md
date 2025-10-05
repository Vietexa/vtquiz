# image_quiz
## A quiz-like application where you have to answear the question you are shown by selecting a part of the image.

version: 0.0.9

**Note: This project is in its very early stages and it's nowhere near done.**


### How to build the project on Windows:

The fastest way to build the project on Windows is by installing VS Code and installing the CMakeTools extension and building the project with the help of it.

So, here's what you need to do step by step:

1. Install a C/C++ toolchain (such as Clang or GCC) and set it up accordingly
2. Install a build system (such as Ninja)
3. Install Visual Studio Code
4. Inside Visual Studio Code, go to the "extensions" tab and install CMakeTools (the one published by Microsoft)
5. By installing the CMakeTools extension a new tab with the icon of CMake will be created, go to that tab and configure the build options
6. After you finish configuring your build options, you can press F7 and wait for the project to be built
7. Your freshly built executable (together with the shared libraries) should be in the ``/build/output/`` directory



### How to build the project on Linux distributions:

### Arch Linux

1. install gcc (if you don't have it already), cmake and make
   
   ```sudo pacman -Syu```
   
   ```sudo pacman -S gcc make cmake```

2. Change the directory to build (``cd build``) and build the Make and CMake files
   
``cmake ..``

``make``

3. Your executable file should be in the ``/build/output/`` directory, as well as the other .so files


