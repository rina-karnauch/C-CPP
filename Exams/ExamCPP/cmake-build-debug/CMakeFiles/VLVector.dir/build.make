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
CMAKE_COMMAND = "/Applications/CLion 2.app/Contents/bin/cmake/mac/bin/cmake"

# The command to remove a file.
RM = "/Applications/CLion 2.app/Contents/bin/cmake/mac/bin/cmake" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/rina.karnauch/Desktop/Exams/ExamCPP

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/VLVector.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/VLVector.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/VLVector.dir/flags.make

CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o: CMakeFiles/VLVector.dir/flags.make
CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o: ../PresubmissionTests.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o -c /Users/rina.karnauch/Desktop/Exams/ExamCPP/PresubmissionTests.cpp

CMakeFiles/VLVector.dir/PresubmissionTests.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/VLVector.dir/PresubmissionTests.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/rina.karnauch/Desktop/Exams/ExamCPP/PresubmissionTests.cpp > CMakeFiles/VLVector.dir/PresubmissionTests.cpp.i

CMakeFiles/VLVector.dir/PresubmissionTests.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/VLVector.dir/PresubmissionTests.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/rina.karnauch/Desktop/Exams/ExamCPP/PresubmissionTests.cpp -o CMakeFiles/VLVector.dir/PresubmissionTests.cpp.s

# Object files for target VLVector
VLVector_OBJECTS = \
"CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o"

# External object files for target VLVector
VLVector_EXTERNAL_OBJECTS =

VLVector: CMakeFiles/VLVector.dir/PresubmissionTests.cpp.o
VLVector: CMakeFiles/VLVector.dir/build.make
VLVector: CMakeFiles/VLVector.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable VLVector"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/VLVector.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/VLVector.dir/build: VLVector

.PHONY : CMakeFiles/VLVector.dir/build

CMakeFiles/VLVector.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/VLVector.dir/cmake_clean.cmake
.PHONY : CMakeFiles/VLVector.dir/clean

CMakeFiles/VLVector.dir/depend:
	cd /Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/rina.karnauch/Desktop/Exams/ExamCPP /Users/rina.karnauch/Desktop/Exams/ExamCPP /Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug /Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug /Users/rina.karnauch/Desktop/Exams/ExamCPP/cmake-build-debug/CMakeFiles/VLVector.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/VLVector.dir/depend

