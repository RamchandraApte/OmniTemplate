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

# Utility rule file for coverage.

# Include the progress variables for this target.
include CMakeFiles/coverage.dir/progress.make

CMakeFiles/coverage:
	gcovr -r .. --html -o coverage.html --exclude-unreachable-branches --exclude-throw-branches

coverage: CMakeFiles/coverage
coverage: CMakeFiles/coverage.dir/build.make

.PHONY : coverage

# Rule to build all files generated by this target.
CMakeFiles/coverage.dir/build: coverage

.PHONY : CMakeFiles/coverage.dir/build

CMakeFiles/coverage.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/coverage.dir/cmake_clean.cmake
.PHONY : CMakeFiles/coverage.dir/clean

CMakeFiles/coverage.dir/depend:
	cd /home/ram/OmniTemplate/docs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ram/OmniTemplate /home/ram/OmniTemplate /home/ram/OmniTemplate/docs /home/ram/OmniTemplate/docs /home/ram/OmniTemplate/docs/CMakeFiles/coverage.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/coverage.dir/depend
