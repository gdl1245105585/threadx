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
CMAKE_SOURCE_DIR = /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build

# Include any dependencies generated for this target.
include CMakeFiles/ProjectHelloWorld.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/ProjectHelloWorld.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/ProjectHelloWorld.dir/flags.make

CMakeFiles/ProjectHelloWorld.dir/main.c.o: CMakeFiles/ProjectHelloWorld.dir/flags.make
CMakeFiles/ProjectHelloWorld.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/ProjectHelloWorld.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/ProjectHelloWorld.dir/main.c.o   -c /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/main.c

CMakeFiles/ProjectHelloWorld.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/ProjectHelloWorld.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/main.c > CMakeFiles/ProjectHelloWorld.dir/main.c.i

CMakeFiles/ProjectHelloWorld.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/ProjectHelloWorld.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/main.c -o CMakeFiles/ProjectHelloWorld.dir/main.c.s

# Object files for target ProjectHelloWorld
ProjectHelloWorld_OBJECTS = \
"CMakeFiles/ProjectHelloWorld.dir/main.c.o"

# External object files for target ProjectHelloWorld
ProjectHelloWorld_EXTERNAL_OBJECTS =

ProjectHelloWorld: CMakeFiles/ProjectHelloWorld.dir/main.c.o
ProjectHelloWorld: CMakeFiles/ProjectHelloWorld.dir/build.make
ProjectHelloWorld: lib/libthreadx.a
ProjectHelloWorld: /home/guodl/Desktop/ics2023/abstract-machine/am/build/am-native.a
ProjectHelloWorld: CMakeFiles/ProjectHelloWorld.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable ProjectHelloWorld"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/ProjectHelloWorld.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/ProjectHelloWorld.dir/build: ProjectHelloWorld

.PHONY : CMakeFiles/ProjectHelloWorld.dir/build

CMakeFiles/ProjectHelloWorld.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/ProjectHelloWorld.dir/cmake_clean.cmake
.PHONY : CMakeFiles/ProjectHelloWorld.dir/clean

CMakeFiles/ProjectHelloWorld.dir/depend:
	cd /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build /home/guodl/Desktop/azure-rtos-learn-samples/courses/threadx/ProjectHelloWorld/build/CMakeFiles/ProjectHelloWorld.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/ProjectHelloWorld.dir/depend

