# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rina.karnauch/CProjects/Ex2

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rina.karnauch/CProjects/Ex2/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Ex2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Ex2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Ex2.dir/flags.make

CMakeFiles/Ex2.dir/RailWayPlanner.c.o: CMakeFiles/Ex2.dir/flags.make
CMakeFiles/Ex2.dir/RailWayPlanner.c.o: ../RailWayPlanner.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rina.karnauch/CProjects/Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/Ex2.dir/RailWayPlanner.c.o"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/Ex2.dir/RailWayPlanner.c.o   -c /Users/rina.karnauch/CProjects/Ex2/RailWayPlanner.c

CMakeFiles/Ex2.dir/RailWayPlanner.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/Ex2.dir/RailWayPlanner.c.i"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Users/rina.karnauch/CProjects/Ex2/RailWayPlanner.c > CMakeFiles/Ex2.dir/RailWayPlanner.c.i

CMakeFiles/Ex2.dir/RailWayPlanner.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/Ex2.dir/RailWayPlanner.c.s"
	/Library/Developer/CommandLineTools/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Users/rina.karnauch/CProjects/Ex2/RailWayPlanner.c -o CMakeFiles/Ex2.dir/RailWayPlanner.c.s

# Object files for target Ex2
Ex2_OBJECTS = \
"CMakeFiles/Ex2.dir/RailWayPlanner.c.o"

# External object files for target Ex2
Ex2_EXTERNAL_OBJECTS =

Ex2: CMakeFiles/Ex2.dir/RailWayPlanner.c.o
Ex2: CMakeFiles/Ex2.dir/build.make
Ex2: CMakeFiles/Ex2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rina.karnauch/CProjects/Ex2/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable Ex2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Ex2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Ex2.dir/build: Ex2

.PHONY : CMakeFiles/Ex2.dir/build

CMakeFiles/Ex2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Ex2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Ex2.dir/clean

CMakeFiles/Ex2.dir/depend:
	cd /Users/rina.karnauch/CProjects/Ex2/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rina.karnauch/CProjects/Ex2 /Users/rina.karnauch/CProjects/Ex2 /Users/rina.karnauch/CProjects/Ex2/cmake-build-debug /Users/rina.karnauch/CProjects/Ex2/cmake-build-debug /Users/rina.karnauch/CProjects/Ex2/cmake-build-debug/CMakeFiles/Ex2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Ex2.dir/depend

