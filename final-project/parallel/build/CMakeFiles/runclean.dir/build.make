# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.4

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
CMAKE_COMMAND = /opt/apps/cmake/3.4.1/bin/cmake

# The command to remove a file.
RM = /opt/apps/cmake/3.4.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /work/05106/west5678/lonestar/PCSE/parallel

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /work/05106/west5678/lonestar/PCSE/parallel/build

# Utility rule file for runclean.

# Include the progress variables for this target.
include CMakeFiles/runclean.dir/progress.make

CMakeFiles/runclean:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/05106/west5678/lonestar/PCSE/parallel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "runclean invoked"
	/opt/apps/cmake/3.4.1/bin/cmake -E remove *.log *.gmv *.gnuplot *.gpl *.eps *.pov *.vtk *.ucd *.d2

runclean: CMakeFiles/runclean
runclean: CMakeFiles/runclean.dir/build.make

.PHONY : runclean

# Rule to build all files generated by this target.
CMakeFiles/runclean.dir/build: runclean

.PHONY : CMakeFiles/runclean.dir/build

CMakeFiles/runclean.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/runclean.dir/cmake_clean.cmake
.PHONY : CMakeFiles/runclean.dir/clean

CMakeFiles/runclean.dir/depend:
	cd /work/05106/west5678/lonestar/PCSE/parallel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/05106/west5678/lonestar/PCSE/parallel /work/05106/west5678/lonestar/PCSE/parallel /work/05106/west5678/lonestar/PCSE/parallel/build /work/05106/west5678/lonestar/PCSE/parallel/build /work/05106/west5678/lonestar/PCSE/parallel/build/CMakeFiles/runclean.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/runclean.dir/depend

