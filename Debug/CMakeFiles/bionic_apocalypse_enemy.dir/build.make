# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = C:\msys64\mingw64\bin\cmake.exe

# The command to remove a file.
RM = C:\msys64\mingw64\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\SCHOOL\Game_Design\bionic_apocalypse

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\SCHOOL\Game_Design\bionic_apocalypse\Debug

# Include any dependencies generated for this target.
include CMakeFiles/bionic_apocalypse_enemy.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/bionic_apocalypse_enemy.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/bionic_apocalypse_enemy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/bionic_apocalypse_enemy.dir/flags.make

CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj: CMakeFiles/bionic_apocalypse_enemy.dir/flags.make
CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj: CMakeFiles/bionic_apocalypse_enemy.dir/includes_CXX.rsp
CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj: ../bin/bionic_apocalypse_enemy.cpp
CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj: CMakeFiles/bionic_apocalypse_enemy.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\SCHOOL\Game_Design\bionic_apocalypse\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj -MF CMakeFiles\bionic_apocalypse_enemy.dir\bin\bionic_apocalypse_enemy.cpp.obj.d -o CMakeFiles\bionic_apocalypse_enemy.dir\bin\bionic_apocalypse_enemy.cpp.obj -c C:\SCHOOL\Game_Design\bionic_apocalypse\bin\bionic_apocalypse_enemy.cpp

CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\SCHOOL\Game_Design\bionic_apocalypse\bin\bionic_apocalypse_enemy.cpp > CMakeFiles\bionic_apocalypse_enemy.dir\bin\bionic_apocalypse_enemy.cpp.i

CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\SCHOOL\Game_Design\bionic_apocalypse\bin\bionic_apocalypse_enemy.cpp -o CMakeFiles\bionic_apocalypse_enemy.dir\bin\bionic_apocalypse_enemy.cpp.s

# Object files for target bionic_apocalypse_enemy
bionic_apocalypse_enemy_OBJECTS = \
"CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj"

# External object files for target bionic_apocalypse_enemy
bionic_apocalypse_enemy_EXTERNAL_OBJECTS =

bionic_apocalypse_enemy.exe: CMakeFiles/bionic_apocalypse_enemy.dir/bin/bionic_apocalypse_enemy.cpp.obj
bionic_apocalypse_enemy.exe: CMakeFiles/bionic_apocalypse_enemy.dir/build.make
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2_image.dll.a
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2_gfx.dll.a
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2_ttf.dll.a
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2_mixer.dll.a
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2main.a
bionic_apocalypse_enemy.exe: C:/msys64/mingw64/lib/libSDL2.dll.a
bionic_apocalypse_enemy.exe: CMakeFiles/bionic_apocalypse_enemy.dir/linklibs.rsp
bionic_apocalypse_enemy.exe: CMakeFiles/bionic_apocalypse_enemy.dir/objects1.rsp
bionic_apocalypse_enemy.exe: CMakeFiles/bionic_apocalypse_enemy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\SCHOOL\Game_Design\bionic_apocalypse\Debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable bionic_apocalypse_enemy.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\bionic_apocalypse_enemy.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/bionic_apocalypse_enemy.dir/build: bionic_apocalypse_enemy.exe
.PHONY : CMakeFiles/bionic_apocalypse_enemy.dir/build

CMakeFiles/bionic_apocalypse_enemy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\bionic_apocalypse_enemy.dir\cmake_clean.cmake
.PHONY : CMakeFiles/bionic_apocalypse_enemy.dir/clean

CMakeFiles/bionic_apocalypse_enemy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\SCHOOL\Game_Design\bionic_apocalypse C:\SCHOOL\Game_Design\bionic_apocalypse C:\SCHOOL\Game_Design\bionic_apocalypse\Debug C:\SCHOOL\Game_Design\bionic_apocalypse\Debug C:\SCHOOL\Game_Design\bionic_apocalypse\Debug\CMakeFiles\bionic_apocalypse_enemy.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/bionic_apocalypse_enemy.dir/depend
