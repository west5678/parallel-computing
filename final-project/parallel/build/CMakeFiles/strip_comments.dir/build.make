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

# Utility rule file for strip_comments.

# Include the progress variables for this target.
include CMakeFiles/strip_comments.dir/progress.make

CMakeFiles/strip_comments:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/work/05106/west5678/lonestar/PCSE/parallel/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "strip comments"
	/usr/bin/perl -pi -e 's#^[ \t]*//.*\n##g;' main.cpp /work/05106/west5678/lonestar/PCSE/parallel/include/doxygen_mainpage.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/model.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/cell.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/utils.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/dof_counter.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/solvers.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/diffusion.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/mesh_handler.hpp /work/05106/west5678/lonestar/PCSE/parallel/include/model_manager.hpp /work/05106/west5678/lonestar/PCSE/parallel/solved_problems/problems/diffusion/test_problem1.hpp /work/05106/west5678/lonestar/PCSE/parallel/solved_problems/problems/diffusion/tokamak_anisotropy_2.hpp /work/05106/west5678/lonestar/PCSE/parallel/solved_problems/problems/diffusion/double_x_2d.hpp

strip_comments: CMakeFiles/strip_comments
strip_comments: CMakeFiles/strip_comments.dir/build.make

.PHONY : strip_comments

# Rule to build all files generated by this target.
CMakeFiles/strip_comments.dir/build: strip_comments

.PHONY : CMakeFiles/strip_comments.dir/build

CMakeFiles/strip_comments.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/strip_comments.dir/cmake_clean.cmake
.PHONY : CMakeFiles/strip_comments.dir/clean

CMakeFiles/strip_comments.dir/depend:
	cd /work/05106/west5678/lonestar/PCSE/parallel/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /work/05106/west5678/lonestar/PCSE/parallel /work/05106/west5678/lonestar/PCSE/parallel /work/05106/west5678/lonestar/PCSE/parallel/build /work/05106/west5678/lonestar/PCSE/parallel/build /work/05106/west5678/lonestar/PCSE/parallel/build/CMakeFiles/strip_comments.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/strip_comments.dir/depend
