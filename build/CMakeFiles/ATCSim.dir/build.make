# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build

# Include any dependencies generated for this target.
include CMakeFiles/ATCSim.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ATCSim.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ATCSim.dir/flags.make

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o: CMakeFiles/ATCSim.dir/flags.make
CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o: ../src/simulator/ATCSim.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o -c /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/src/simulator/ATCSim.cpp

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/src/simulator/ATCSim.cpp > CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.i

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/src/simulator/ATCSim.cpp -o CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.s

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.requires:

.PHONY : CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.requires

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.provides: CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.requires
	$(MAKE) -f CMakeFiles/ATCSim.dir/build.make CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.provides.build
.PHONY : CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.provides

CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.provides.build: CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o


# Object files for target ATCSim
ATCSim_OBJECTS = \
"CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o"

# External object files for target ATCSim
ATCSim_EXTERNAL_OBJECTS =

ATCSim: CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o
ATCSim: CMakeFiles/ATCSim.dir/build.make
ATCSim: /usr/lib/x86_64-linux-gnu/libIce.so
ATCSim: /usr/lib/x86_64-linux-gnu/libIceUtil.so
ATCSim: libATCSimLib.so
ATCSim: /usr/lib/x86_64-linux-gnu/libIce.so
ATCSim: /usr/lib/x86_64-linux-gnu/libIceUtil.so
ATCSim: CMakeFiles/ATCSim.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ATCSim"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ATCSim.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ATCSim.dir/build: ATCSim

.PHONY : CMakeFiles/ATCSim.dir/build

CMakeFiles/ATCSim.dir/requires: CMakeFiles/ATCSim.dir/src/simulator/ATCSim.cpp.o.requires

.PHONY : CMakeFiles/ATCSim.dir/requires

CMakeFiles/ATCSim.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ATCSim.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ATCSim.dir/clean

CMakeFiles/ATCSim.dir/depend:
	cd /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build /home/alumnos/pasensio/Escritorio/universidad/programacion/cpp/git/ATCSim/build/CMakeFiles/ATCSim.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ATCSim.dir/depend

