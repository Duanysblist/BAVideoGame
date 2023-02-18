Welcome to Bionic Apocalypse!!! I made this game with three other students in my game design course at William & Mary. We had a great time making it, and I hope you have a fun time playing it. 



**PREREQUISITES**
- GCC
- CMAKE (www.cmake.org)
- SDL 2.0 (www.libsdl.org)
- SDL2_image
- SDL2_gfx
- SDL2_ttf
- SDL2_mixer

**Linux**

Just install the packages above with your distributions package manager and
everything should work out of the box.  Only resort to compiling from source
if no suitable package exists.  Also, do not forget to install the 'devel'
package for SDL2.

Download the repository code.  Make a subdir 'Debug', and in
'Debug' type: 'cmake ..'.  This should generate the makefiles.  Once
succesfully generated, you can now compile the code with 'make'. You can then run the game by running the main executable.

**Windows**

To make install easy, we will use MSYS2 and mingw64.

1) Install MSYS2: https://www.msys2.org/
2) Open the MSYS2 terminal
2) Install mingw64:    pacman -S mingw-w64-x86_64-toolchain
3) Install cmake:      pacman -S mingw-w64-x86_64-cmake
4) Install SDL2:       pacman -S mingw-w64-x86_64-SDL2
5) Install SDL2 gfx:   pacman -S mingw-w64-x86_64-SDL2_gfx
6) Install SDL2 image: pacman -S mingw-w64-x86_64-SDL2_image
7) Install SDL2 ttf:   pacman -S mingw-w64-x86_64-SDL2_ttf
8) Install SDL2 ttf:   pacman -S mingw-w64-x86_64-SDL2_mixer
8) Optional: add <msys2 install path>/mingw64/bin to your path if you also want to be able to run your code by double clicking.  To add to your path, open "Edit environment variables" -> select Path -> Edit -> New -> Browse

We will use the msys2 terminal for all steps. To access your c:\ drive use:

cd /c/

Next, download the repo to your location of choice, and use cd /c/<path> to
enter the location in msys2.

1) Make the directory in which you will compile the project code.  Inside
your source directory make a directory 'Debug'.

mkdir Debug

2) Next, generate make files:

cd Debug
cmake.exe -G "MinGW Makefiles" ..

3) The above step should find a C++ compiler and the SDL2 libraries.  Next we
can compile the code:

mingw32-make.exe

4) We can now test the code:

./bionic_apocalypse_main.exe


**Mac**

Use homebrew to install prerequisites (listed at the top of this file).

Next, download the repo to your location of choice, and use cd to
enter the location in your terminal.

1) Make the directory in which you will compile the project code:  Inside
your source directory make a directory 'Debug'.

2) Next, generate make files:

cd Debug
cmake ..

3) The above step should find a C++ compiler and the SDL2 libraries.  Next we
can compile the code:

make

4) We can now test the code:

./bionic_apocalypse_main


***bionic_apocalypse_main***

If the above worked without error, it should  produce a 'bionic_apocalypse_main' executable that will open a window.  You can quit by pressing 'q'.


**ADDING FILES**

- If you want to add an executable, just add the corresponding .cpp file in the 'bin' subdirectory, and _rerun_ 'cmake .' to update the Makefiles.
- If you want to add a source file, just add the corresponding .cpp file in the 'src' subdirectory, and _rerun_ 'cmake .' to update the Makefile.
- If you want to add a header file, just add the corresponding .h file to the 'include' subdirectory. You do not need to update the Makefile.


**ADVANCED COMPILING**

The above instructions will compile your executable with all debug information embedded and compiler optimizations minimized.  To compile a 'release' version, just create a subdirectory 'Release' instead of 'Debug' and follow the same instructions as above. Note: in release mode certain safety checks are disabled and 'assert' statement are ignored. Hence, it is recommended to test your code in 'Debug' mode, and only when everything works, compile it in the 'Release' mode.

If you want to use additional external libraries, you will need to add them to 'CMakeLists.txt' (line 48). Please refer to the CMake documentation for more information on how to include libraries to your project with CMake.


<img width="875" alt="Screenshot 2023-02-17 200945" src="https://user-images.githubusercontent.com/33470234/219825620-c702cbc9-0322-4d2d-b306-e7cc9c56c81b.png">

<img width="876" alt="Screenshot 2023-02-17 201022" src="https://user-images.githubusercontent.com/33470234/219825629-d4d0cbcd-f308-4fc1-9332-94c761817ba0.png">

<img width="874" alt="Screenshot 2023-02-17 201038" src="https://user-images.githubusercontent.com/33470234/219825636-3bc50ec5-675e-41ed-b91f-6bedfdaa7e76.png">

<img width="873" alt="Screenshot 2023-02-17 201050" src="https://user-images.githubusercontent.com/33470234/219825640-cbfb8e07-111a-4766-929d-faaf9b74c974.png">

<img width="875" alt="Screenshot 2023-02-17 201107" src="https://user-images.githubusercontent.com/33470234/219825644-329f393f-f7a6-4eb3-af5f-71bf7799e5be.png">

https://user-images.githubusercontent.com/33470234/219825662-a5985528-f4e9-41b3-9160-34f839075897.mp4

https://user-images.githubusercontent.com/33470234/219825714-ccceee55-85f9-4e79-ab46-f3701a1e880b.mp4

https://user-images.githubusercontent.com/33470234/219825718-fac6614e-9665-4c0a-a48d-924cef908bc9.mp4

https://user-images.githubusercontent.com/33470234/219825731-1e2aa28f-d443-4a1a-9ee2-559617d22e3b.mp4

https://user-images.githubusercontent.com/33470234/219825734-d0027722-2094-442e-8df6-dfba4d19b50e.mp4
