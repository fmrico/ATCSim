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
CMAKE_SOURCE_DIR = /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build

# Include any dependencies generated for this target.
include googlemock/gtest/CMakeFiles/gtest_main.dir/depend.make

# Include the progress variables for this target.
include googlemock/gtest/CMakeFiles/gtest_main.dir/progress.make

# Include the compile flags for this target's objects.
include googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: googlemock/gtest/CMakeFiles/gtest_main.dir/flags.make
googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o: /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest/googletest/src/gtest_main.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.o -c /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest/googletest/src/gtest_main.cc

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/gtest_main.dir/src/gtest_main.cc.i"
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest/googletest/src/gtest_main.cc > CMakeFiles/gtest_main.dir/src/gtest_main.cc.i

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/gtest_main.dir/src/gtest_main.cc.s"
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest/googletest/src/gtest_main.cc -o CMakeFiles/gtest_main.dir/src/gtest_main.cc.s

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires:

.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides: googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires
	$(MAKE) -f googlemock/gtest/CMakeFiles/gtest_main.dir/build.make googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build
.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides

googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.provides.build: googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o


# Object files for target gtest_main
gtest_main_OBJECTS = \
"CMakeFiles/gtest_main.dir/src/gtest_main.cc.o"

# External object files for target gtest_main
gtest_main_EXTERNAL_OBJECTS =

lib/libgtest_main.a: googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o
lib/libgtest_main.a: googlemock/gtest/CMakeFiles/gtest_main.dir/build.make
lib/libgtest_main.a: googlemock/gtest/CMakeFiles/gtest_main.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library ../../lib/libgtest_main.a"
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean_target.cmake
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/gtest_main.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
googlemock/gtest/CMakeFiles/gtest_main.dir/build: lib/libgtest_main.a

.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/build

googlemock/gtest/CMakeFiles/gtest_main.dir/requires: googlemock/gtest/CMakeFiles/gtest_main.dir/src/gtest_main.cc.o.requires

.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/requires

googlemock/gtest/CMakeFiles/gtest_main.dir/clean:
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest && $(CMAKE_COMMAND) -P CMakeFiles/gtest_main.dir/cmake_clean.cmake
.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/clean

googlemock/gtest/CMakeFiles/gtest_main.dir/depend:
	cd /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest/googletest /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest /home/pablo/git/ATCSim/build_ubuntu_18_04/googletest-prefix/src/googletest-build/googlemock/gtest/CMakeFiles/gtest_main.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : googlemock/gtest/CMakeFiles/gtest_main.dir/depend

