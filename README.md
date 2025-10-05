# image_quiz
## A quiz-like application where you have to answear the question you are shown by selecting a part of the image.

**Note: This project is in its very early stages and it's nowhere near done.**

How to build the project on Linux distributions:

### Arch Linux

1. install gcc (if you don't have it already), cmake and make
   
   ```sudo pacman -Syu```
   
   ```sudo pacman -S gcc make cmake```

2. Change the directory to build (``cd build``) and build the Make and CMake files
   
``cmake ..``

``make``

3. Your executable file should be in the ``/build/output/`` directory, as well as the other .so files.


