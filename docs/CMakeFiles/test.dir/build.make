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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ram/OmniTemplate

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ram/OmniTemplate/docs

# Include any dependencies generated for this target.
include CMakeFiles/test.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test.dir/flags.make

CMakeFiles/test.dir/cmake_pch.hxx.gch: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/cmake_pch.hxx.gch: CMakeFiles/test.dir/cmake_pch.hxx.cxx
CMakeFiles/test.dir/cmake_pch.hxx.gch: CMakeFiles/test.dir/cmake_pch.hxx
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ram/OmniTemplate/docs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test.dir/cmake_pch.hxx.gch"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -o CMakeFiles/test.dir/cmake_pch.hxx.gch -c /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx.cxx

CMakeFiles/test.dir/cmake_pch.hxx.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/cmake_pch.hxx.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -E /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx.cxx > CMakeFiles/test.dir/cmake_pch.hxx.i

CMakeFiles/test.dir/cmake_pch.hxx.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/cmake_pch.hxx.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -x c++-header -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -S /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx.cxx -o CMakeFiles/test.dir/cmake_pch.hxx.s

CMakeFiles/test.dir/src/test/test.cpp.o: CMakeFiles/test.dir/flags.make
CMakeFiles/test.dir/src/test/test.cpp.o: ../src/test/test.cpp
CMakeFiles/test.dir/src/test/test.cpp.o: CMakeFiles/test.dir/cmake_pch.hxx
CMakeFiles/test.dir/src/test/test.cpp.o: CMakeFiles/test.dir/cmake_pch.hxx.gch
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/ram/OmniTemplate/docs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test.dir/src/test/test.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -o CMakeFiles/test.dir/src/test/test.cpp.o -c /home/ram/OmniTemplate/src/test/test.cpp

CMakeFiles/test.dir/src/test/test.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test.dir/src/test/test.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -E /home/ram/OmniTemplate/src/test/test.cpp > CMakeFiles/test.dir/src/test/test.cpp.i

CMakeFiles/test.dir/src/test/test.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test.dir/src/test/test.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -Winvalid-pch -include /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/cmake_pch.hxx -S /home/ram/OmniTemplate/src/test/test.cpp -o CMakeFiles/test.dir/src/test/test.cpp.s

# Object files for target test
test_OBJECTS = \
"CMakeFiles/test.dir/src/test/test.cpp.o"

# External object files for target test
test_EXTERNAL_OBJECTS =

test: CMakeFiles/test.dir/cmake_pch.hxx.gch
test: CMakeFiles/test.dir/src/test/test.cpp.o
test: CMakeFiles/test.dir/build.make
test: CMakeFiles/test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/ram/OmniTemplate/docs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test.dir/build: test

.PHONY : CMakeFiles/test.dir/build

CMakeFiles/test.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test.dir/clean

CMakeFiles/test.dir/depend:
	cd /home/ram/OmniTemplate/docs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ram/OmniTemplate /home/ram/OmniTemplate /home/ram/OmniTemplate/docs /home/ram/OmniTemplate/docs /home/ram/OmniTemplate/docs/CMakeFiles/test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test.dir/depend

