# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /home/jencmart/.bin/clion-2016.3.4/bin/cmake/bin/cmake

# The command to remove a file.
RM = /home/jencmart/.bin/clion-2016.3.4/bin/cmake/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/e_learning_pretizeni.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/e_learning_pretizeni.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/e_learning_pretizeni.dir/flags.make

CMakeFiles/e_learning_pretizeni.dir/main.cpp.o: CMakeFiles/e_learning_pretizeni.dir/flags.make
CMakeFiles/e_learning_pretizeni.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/e_learning_pretizeni.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/e_learning_pretizeni.dir/main.cpp.o -c /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/main.cpp

CMakeFiles/e_learning_pretizeni.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/e_learning_pretizeni.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/main.cpp > CMakeFiles/e_learning_pretizeni.dir/main.cpp.i

CMakeFiles/e_learning_pretizeni.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/e_learning_pretizeni.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/main.cpp -o CMakeFiles/e_learning_pretizeni.dir/main.cpp.s

CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.requires

CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.provides: CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/e_learning_pretizeni.dir/build.make CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.provides

CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.provides.build: CMakeFiles/e_learning_pretizeni.dir/main.cpp.o


# Object files for target e_learning_pretizeni
e_learning_pretizeni_OBJECTS = \
"CMakeFiles/e_learning_pretizeni.dir/main.cpp.o"

# External object files for target e_learning_pretizeni
e_learning_pretizeni_EXTERNAL_OBJECTS =

e_learning_pretizeni: CMakeFiles/e_learning_pretizeni.dir/main.cpp.o
e_learning_pretizeni: CMakeFiles/e_learning_pretizeni.dir/build.make
e_learning_pretizeni: CMakeFiles/e_learning_pretizeni.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable e_learning_pretizeni"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/e_learning_pretizeni.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/e_learning_pretizeni.dir/build: e_learning_pretizeni

.PHONY : CMakeFiles/e_learning_pretizeni.dir/build

CMakeFiles/e_learning_pretizeni.dir/requires: CMakeFiles/e_learning_pretizeni.dir/main.cpp.o.requires

.PHONY : CMakeFiles/e_learning_pretizeni.dir/requires

CMakeFiles/e_learning_pretizeni.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/e_learning_pretizeni.dir/cmake_clean.cmake
.PHONY : CMakeFiles/e_learning_pretizeni.dir/clean

CMakeFiles/e_learning_pretizeni.dir/depend:
	cd /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug /home/jencmart/Dropbox/development/CLionProjects/pa2/e-learning-pretizeni/cmake-build-debug/CMakeFiles/e_learning_pretizeni.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/e_learning_pretizeni.dir/depend

