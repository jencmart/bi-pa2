# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /home/jencmart/.bin/clion-2017.1.2/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jencmart/.bin/clion-2017.1.2/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jencmart/pa2/zkouska/teoreticky

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/teoreticky.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/teoreticky.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/teoreticky.dir/flags.make

CMakeFiles/teoreticky.dir/main.cpp.o: CMakeFiles/teoreticky.dir/flags.make
CMakeFiles/teoreticky.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/teoreticky.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/teoreticky.dir/main.cpp.o -c /home/jencmart/pa2/zkouska/teoreticky/main.cpp

CMakeFiles/teoreticky.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/teoreticky.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jencmart/pa2/zkouska/teoreticky/main.cpp > CMakeFiles/teoreticky.dir/main.cpp.i

CMakeFiles/teoreticky.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/teoreticky.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jencmart/pa2/zkouska/teoreticky/main.cpp -o CMakeFiles/teoreticky.dir/main.cpp.s

CMakeFiles/teoreticky.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/teoreticky.dir/main.cpp.o.requires

CMakeFiles/teoreticky.dir/main.cpp.o.provides: CMakeFiles/teoreticky.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/teoreticky.dir/build.make CMakeFiles/teoreticky.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/teoreticky.dir/main.cpp.o.provides

CMakeFiles/teoreticky.dir/main.cpp.o.provides.build: CMakeFiles/teoreticky.dir/main.cpp.o


# Object files for target teoreticky
teoreticky_OBJECTS = \
"CMakeFiles/teoreticky.dir/main.cpp.o"

# External object files for target teoreticky
teoreticky_EXTERNAL_OBJECTS =

teoreticky: CMakeFiles/teoreticky.dir/main.cpp.o
teoreticky: CMakeFiles/teoreticky.dir/build.make
teoreticky: CMakeFiles/teoreticky.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable teoreticky"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/teoreticky.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/teoreticky.dir/build: teoreticky

.PHONY : CMakeFiles/teoreticky.dir/build

CMakeFiles/teoreticky.dir/requires: CMakeFiles/teoreticky.dir/main.cpp.o.requires

.PHONY : CMakeFiles/teoreticky.dir/requires

CMakeFiles/teoreticky.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/teoreticky.dir/cmake_clean.cmake
.PHONY : CMakeFiles/teoreticky.dir/clean

CMakeFiles/teoreticky.dir/depend:
	cd /home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jencmart/pa2/zkouska/teoreticky /home/jencmart/pa2/zkouska/teoreticky /home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug /home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug /home/jencmart/pa2/zkouska/teoreticky/cmake-build-debug/CMakeFiles/teoreticky.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/teoreticky.dir/depend

