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
CMAKE_SOURCE_DIR = /home/jencmart/pa2/zkouska/StarTrekIII

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/StarTrekIII.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/StarTrekIII.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/StarTrekIII.dir/flags.make

CMakeFiles/StarTrekIII.dir/main.cpp.o: CMakeFiles/StarTrekIII.dir/flags.make
CMakeFiles/StarTrekIII.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/StarTrekIII.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/StarTrekIII.dir/main.cpp.o -c /home/jencmart/pa2/zkouska/StarTrekIII/main.cpp

CMakeFiles/StarTrekIII.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/StarTrekIII.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jencmart/pa2/zkouska/StarTrekIII/main.cpp > CMakeFiles/StarTrekIII.dir/main.cpp.i

CMakeFiles/StarTrekIII.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/StarTrekIII.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jencmart/pa2/zkouska/StarTrekIII/main.cpp -o CMakeFiles/StarTrekIII.dir/main.cpp.s

CMakeFiles/StarTrekIII.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/StarTrekIII.dir/main.cpp.o.requires

CMakeFiles/StarTrekIII.dir/main.cpp.o.provides: CMakeFiles/StarTrekIII.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/StarTrekIII.dir/build.make CMakeFiles/StarTrekIII.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/StarTrekIII.dir/main.cpp.o.provides

CMakeFiles/StarTrekIII.dir/main.cpp.o.provides.build: CMakeFiles/StarTrekIII.dir/main.cpp.o


# Object files for target StarTrekIII
StarTrekIII_OBJECTS = \
"CMakeFiles/StarTrekIII.dir/main.cpp.o"

# External object files for target StarTrekIII
StarTrekIII_EXTERNAL_OBJECTS =

StarTrekIII: CMakeFiles/StarTrekIII.dir/main.cpp.o
StarTrekIII: CMakeFiles/StarTrekIII.dir/build.make
StarTrekIII: CMakeFiles/StarTrekIII.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable StarTrekIII"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/StarTrekIII.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/StarTrekIII.dir/build: StarTrekIII

.PHONY : CMakeFiles/StarTrekIII.dir/build

CMakeFiles/StarTrekIII.dir/requires: CMakeFiles/StarTrekIII.dir/main.cpp.o.requires

.PHONY : CMakeFiles/StarTrekIII.dir/requires

CMakeFiles/StarTrekIII.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/StarTrekIII.dir/cmake_clean.cmake
.PHONY : CMakeFiles/StarTrekIII.dir/clean

CMakeFiles/StarTrekIII.dir/depend:
	cd /home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jencmart/pa2/zkouska/StarTrekIII /home/jencmart/pa2/zkouska/StarTrekIII /home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug /home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug /home/jencmart/pa2/zkouska/StarTrekIII/cmake-build-debug/CMakeFiles/StarTrekIII.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/StarTrekIII.dir/depend

