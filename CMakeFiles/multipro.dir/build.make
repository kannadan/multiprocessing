# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.13

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /home/kannadan/Lataukset/clion-2018.3.4/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/kannadan/Lataukset/clion-2018.3.4/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/kannadan/CLionProjects/multipro

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/kannadan/CLionProjects/multipro

# Include any dependencies generated for this target.
include CMakeFiles/multipro.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/multipro.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/multipro.dir/flags.make

CMakeFiles/multipro.dir/main.cpp.o: CMakeFiles/multipro.dir/flags.make
CMakeFiles/multipro.dir/main.cpp.o: main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kannadan/CLionProjects/multipro/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/multipro.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multipro.dir/main.cpp.o -c /home/kannadan/CLionProjects/multipro/main.cpp

CMakeFiles/multipro.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multipro.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kannadan/CLionProjects/multipro/main.cpp > CMakeFiles/multipro.dir/main.cpp.i

CMakeFiles/multipro.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multipro.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kannadan/CLionProjects/multipro/main.cpp -o CMakeFiles/multipro.dir/main.cpp.s

CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o: CMakeFiles/multipro.dir/flags.make
CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o: lodepng/lodepng.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/kannadan/CLionProjects/multipro/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o -c /home/kannadan/CLionProjects/multipro/lodepng/lodepng.cpp

CMakeFiles/multipro.dir/lodepng/lodepng.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/multipro.dir/lodepng/lodepng.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/kannadan/CLionProjects/multipro/lodepng/lodepng.cpp > CMakeFiles/multipro.dir/lodepng/lodepng.cpp.i

CMakeFiles/multipro.dir/lodepng/lodepng.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/multipro.dir/lodepng/lodepng.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/kannadan/CLionProjects/multipro/lodepng/lodepng.cpp -o CMakeFiles/multipro.dir/lodepng/lodepng.cpp.s

# Object files for target multipro
multipro_OBJECTS = \
"CMakeFiles/multipro.dir/main.cpp.o" \
"CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o"

# External object files for target multipro
multipro_EXTERNAL_OBJECTS =

multipro: CMakeFiles/multipro.dir/main.cpp.o
multipro: CMakeFiles/multipro.dir/lodepng/lodepng.cpp.o
multipro: CMakeFiles/multipro.dir/build.make
multipro: /usr/lib/x86_64-linux-gnu/libOpenCL.so
multipro: CMakeFiles/multipro.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/kannadan/CLionProjects/multipro/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable multipro"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/multipro.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/multipro.dir/build: multipro

.PHONY : CMakeFiles/multipro.dir/build

CMakeFiles/multipro.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/multipro.dir/cmake_clean.cmake
.PHONY : CMakeFiles/multipro.dir/clean

CMakeFiles/multipro.dir/depend:
	cd /home/kannadan/CLionProjects/multipro && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/kannadan/CLionProjects/multipro /home/kannadan/CLionProjects/multipro /home/kannadan/CLionProjects/multipro /home/kannadan/CLionProjects/multipro /home/kannadan/CLionProjects/multipro/CMakeFiles/multipro.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/multipro.dir/depend

