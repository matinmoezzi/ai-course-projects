# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /home/rio/Downloads/JetBrains.CLion.2020.1.1.Linux/clion-2020.1.1/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/rio/Downloads/JetBrains.CLion.2020.1.1.Linux/clion-2020.1.1/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/rio/Documents/8-puzzle_A star"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/rio/Documents/8-puzzle_A star/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/8_puzzle_A_star.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/8_puzzle_A_star.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/8_puzzle_A_star.dir/flags.make

CMakeFiles/8_puzzle_A_star.dir/main.c.o: CMakeFiles/8_puzzle_A_star.dir/flags.make
CMakeFiles/8_puzzle_A_star.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/rio/Documents/8-puzzle_A star/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/8_puzzle_A_star.dir/main.c.o"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/8_puzzle_A_star.dir/main.c.o   -c "/home/rio/Documents/8-puzzle_A star/main.c"

CMakeFiles/8_puzzle_A_star.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/8_puzzle_A_star.dir/main.c.i"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E "/home/rio/Documents/8-puzzle_A star/main.c" > CMakeFiles/8_puzzle_A_star.dir/main.c.i

CMakeFiles/8_puzzle_A_star.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/8_puzzle_A_star.dir/main.c.s"
	/usr/bin/gcc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S "/home/rio/Documents/8-puzzle_A star/main.c" -o CMakeFiles/8_puzzle_A_star.dir/main.c.s

# Object files for target 8_puzzle_A_star
8_puzzle_A_star_OBJECTS = \
"CMakeFiles/8_puzzle_A_star.dir/main.c.o"

# External object files for target 8_puzzle_A_star
8_puzzle_A_star_EXTERNAL_OBJECTS =

8_puzzle_A_star: CMakeFiles/8_puzzle_A_star.dir/main.c.o
8_puzzle_A_star: CMakeFiles/8_puzzle_A_star.dir/build.make
8_puzzle_A_star: CMakeFiles/8_puzzle_A_star.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/rio/Documents/8-puzzle_A star/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable 8_puzzle_A_star"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/8_puzzle_A_star.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/8_puzzle_A_star.dir/build: 8_puzzle_A_star

.PHONY : CMakeFiles/8_puzzle_A_star.dir/build

CMakeFiles/8_puzzle_A_star.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/8_puzzle_A_star.dir/cmake_clean.cmake
.PHONY : CMakeFiles/8_puzzle_A_star.dir/clean

CMakeFiles/8_puzzle_A_star.dir/depend:
	cd "/home/rio/Documents/8-puzzle_A star/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/rio/Documents/8-puzzle_A star" "/home/rio/Documents/8-puzzle_A star" "/home/rio/Documents/8-puzzle_A star/cmake-build-debug" "/home/rio/Documents/8-puzzle_A star/cmake-build-debug" "/home/rio/Documents/8-puzzle_A star/cmake-build-debug/CMakeFiles/8_puzzle_A_star.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/8_puzzle_A_star.dir/depend

