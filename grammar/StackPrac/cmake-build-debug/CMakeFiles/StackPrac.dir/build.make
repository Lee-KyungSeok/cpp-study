# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_SOURCE_DIR = /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StackPrac.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StackPrac.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StackPrac.dir/flags.make

CMakeFiles/StackPrac.dir/main.cpp.o: CMakeFiles/StackPrac.dir/flags.make
CMakeFiles/StackPrac.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StackPrac.dir/main.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StackPrac.dir/main.cpp.o -c /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/main.cpp

CMakeFiles/StackPrac.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StackPrac.dir/main.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/main.cpp > CMakeFiles/StackPrac.dir/main.cpp.i

CMakeFiles/StackPrac.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StackPrac.dir/main.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/main.cpp -o CMakeFiles/StackPrac.dir/main.cpp.s

# Object files for target StackPrac
StackPrac_OBJECTS = \
"CMakeFiles/StackPrac.dir/main.cpp.o"

# External object files for target StackPrac
StackPrac_EXTERNAL_OBJECTS =

StackPrac: CMakeFiles/StackPrac.dir/main.cpp.o
StackPrac: CMakeFiles/StackPrac.dir/build.make
StackPrac: CMakeFiles/StackPrac.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StackPrac"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StackPrac.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StackPrac.dir/build: StackPrac

.PHONY : CMakeFiles/StackPrac.dir/build

CMakeFiles/StackPrac.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StackPrac.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StackPrac.dir/clean

CMakeFiles/StackPrac.dir/depend:
	cd /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug /Users/kyung/Desktop/workspace/cpp/grammar/StackPrac/cmake-build-debug/CMakeFiles/StackPrac.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StackPrac.dir/depend

