# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.25

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/gridware/depots/54e7fb3c/el7/pkg/apps/cmake/3.25.1/gcc-9.3.0/bin/cmake

# The command to remove a file.
RM = /opt/gridware/depots/54e7fb3c/el7/pkg/apps/cmake/3.25.1/gcc-9.3.0/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build

# Include any dependencies generated for this target.
include matching/CMakeFiles/SelectEdge.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include matching/CMakeFiles/SelectEdge.dir/compiler_depend.make

# Include the progress variables for this target.
include matching/CMakeFiles/SelectEdge.dir/progress.make

# Include the compile flags for this target's objects.
include matching/CMakeFiles/SelectEdge.dir/flags.make

matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o: matching/CMakeFiles/SelectEdge.dir/flags.make
matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o: /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/matching/SelectEdge.cpp
matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o: matching/CMakeFiles/SelectEdge.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o"
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o -MF CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o.d -o CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o -c /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/matching/SelectEdge.cpp

matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/SelectEdge.dir/SelectEdge.cpp.i"
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/matching/SelectEdge.cpp > CMakeFiles/SelectEdge.dir/SelectEdge.cpp.i

matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/SelectEdge.dir/SelectEdge.cpp.s"
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/matching/SelectEdge.cpp -o CMakeFiles/SelectEdge.dir/SelectEdge.cpp.s

# Object files for target SelectEdge
SelectEdge_OBJECTS = \
"CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o"

# External object files for target SelectEdge
SelectEdge_EXTERNAL_OBJECTS =

matching/SelectEdge: matching/CMakeFiles/SelectEdge.dir/SelectEdge.cpp.o
matching/SelectEdge: matching/CMakeFiles/SelectEdge.dir/build.make
matching/SelectEdge: matching/CMakeFiles/SelectEdge.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable SelectEdge"
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/SelectEdge.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
matching/CMakeFiles/SelectEdge.dir/build: matching/SelectEdge
.PHONY : matching/CMakeFiles/SelectEdge.dir/build

matching/CMakeFiles/SelectEdge.dir/clean:
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching && $(CMAKE_COMMAND) -P CMakeFiles/SelectEdge.dir/cmake_clean.cmake
.PHONY : matching/CMakeFiles/SelectEdge.dir/clean

matching/CMakeFiles/SelectEdge.dir/depend:
	cd /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/matching /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching /mnt/scratch2/users/40334799/GLF-Filtering/glf-imsm-run/SubgraphMatching/build/matching/CMakeFiles/SelectEdge.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : matching/CMakeFiles/SelectEdge.dir/depend

