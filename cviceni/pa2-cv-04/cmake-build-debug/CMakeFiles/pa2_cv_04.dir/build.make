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
CMAKE_SOURCE_DIR = /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/pa2_cv_04.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/pa2_cv_04.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/pa2_cv_04.dir/flags.make

CMakeFiles/pa2_cv_04.dir/main.cpp.o: CMakeFiles/pa2_cv_04.dir/flags.make
CMakeFiles/pa2_cv_04.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/pa2_cv_04.dir/main.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/pa2_cv_04.dir/main.cpp.o -c /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/main.cpp

CMakeFiles/pa2_cv_04.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pa2_cv_04.dir/main.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/main.cpp > CMakeFiles/pa2_cv_04.dir/main.cpp.i

CMakeFiles/pa2_cv_04.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pa2_cv_04.dir/main.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/main.cpp -o CMakeFiles/pa2_cv_04.dir/main.cpp.s

CMakeFiles/pa2_cv_04.dir/main.cpp.o.requires:

.PHONY : CMakeFiles/pa2_cv_04.dir/main.cpp.o.requires

CMakeFiles/pa2_cv_04.dir/main.cpp.o.provides: CMakeFiles/pa2_cv_04.dir/main.cpp.o.requires
	$(MAKE) -f CMakeFiles/pa2_cv_04.dir/build.make CMakeFiles/pa2_cv_04.dir/main.cpp.o.provides.build
.PHONY : CMakeFiles/pa2_cv_04.dir/main.cpp.o.provides

CMakeFiles/pa2_cv_04.dir/main.cpp.o.provides.build: CMakeFiles/pa2_cv_04.dir/main.cpp.o


# Object files for target pa2_cv_04
pa2_cv_04_OBJECTS = \
"CMakeFiles/pa2_cv_04.dir/main.cpp.o"

# External object files for target pa2_cv_04
pa2_cv_04_EXTERNAL_OBJECTS =

pa2_cv_04: CMakeFiles/pa2_cv_04.dir/main.cpp.o
pa2_cv_04: CMakeFiles/pa2_cv_04.dir/build.make
pa2_cv_04: CMakeFiles/pa2_cv_04.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pa2_cv_04"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pa2_cv_04.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/pa2_cv_04.dir/build: pa2_cv_04

.PHONY : CMakeFiles/pa2_cv_04.dir/build

CMakeFiles/pa2_cv_04.dir/requires: CMakeFiles/pa2_cv_04.dir/main.cpp.o.requires

.PHONY : CMakeFiles/pa2_cv_04.dir/requires

CMakeFiles/pa2_cv_04.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/pa2_cv_04.dir/cmake_clean.cmake
.PHONY : CMakeFiles/pa2_cv_04.dir/clean

CMakeFiles/pa2_cv_04.dir/depend:
	cd /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04 /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04 /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug /home/jencmart/Dropbox/development/CLionProjects/pa2/cv/pa2-cv-04/cmake-build-debug/CMakeFiles/pa2_cv_04.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/pa2_cv_04.dir/depend

