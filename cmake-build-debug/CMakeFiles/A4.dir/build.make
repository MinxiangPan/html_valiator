# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.8

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2017.2.2\bin\cmake\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\LocalFiles\a4-handout

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\LocalFiles\a4-handout\cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/A4.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/A4.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/A4.dir/flags.make

CMakeFiles/A4.dir/main.cpp.obj: CMakeFiles/A4.dir/flags.make
CMakeFiles/A4.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\LocalFiles\a4-handout\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/A4.dir/main.cpp.obj"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\A4.dir\main.cpp.obj -c C:\LocalFiles\a4-handout\main.cpp

CMakeFiles/A4.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A4.dir/main.cpp.i"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\LocalFiles\a4-handout\main.cpp > CMakeFiles\A4.dir\main.cpp.i

CMakeFiles/A4.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A4.dir/main.cpp.s"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\LocalFiles\a4-handout\main.cpp -o CMakeFiles\A4.dir\main.cpp.s

CMakeFiles/A4.dir/main.cpp.obj.requires:

.PHONY : CMakeFiles/A4.dir/main.cpp.obj.requires

CMakeFiles/A4.dir/main.cpp.obj.provides: CMakeFiles/A4.dir/main.cpp.obj.requires
	$(MAKE) -f CMakeFiles\A4.dir\build.make CMakeFiles/A4.dir/main.cpp.obj.provides.build
.PHONY : CMakeFiles/A4.dir/main.cpp.obj.provides

CMakeFiles/A4.dir/main.cpp.obj.provides.build: CMakeFiles/A4.dir/main.cpp.obj


CMakeFiles/A4.dir/a4.cpp.obj: CMakeFiles/A4.dir/flags.make
CMakeFiles/A4.dir/a4.cpp.obj: ../a4.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\LocalFiles\a4-handout\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/A4.dir/a4.cpp.obj"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\A4.dir\a4.cpp.obj -c C:\LocalFiles\a4-handout\a4.cpp

CMakeFiles/A4.dir/a4.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/A4.dir/a4.cpp.i"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\LocalFiles\a4-handout\a4.cpp > CMakeFiles\A4.dir\a4.cpp.i

CMakeFiles/A4.dir/a4.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/A4.dir/a4.cpp.s"
	C:\PROGRA~1\mingw-w64\x86_64-6.1.0-posix-seh-rt_v5-rev1\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\LocalFiles\a4-handout\a4.cpp -o CMakeFiles\A4.dir\a4.cpp.s

CMakeFiles/A4.dir/a4.cpp.obj.requires:

.PHONY : CMakeFiles/A4.dir/a4.cpp.obj.requires

CMakeFiles/A4.dir/a4.cpp.obj.provides: CMakeFiles/A4.dir/a4.cpp.obj.requires
	$(MAKE) -f CMakeFiles\A4.dir\build.make CMakeFiles/A4.dir/a4.cpp.obj.provides.build
.PHONY : CMakeFiles/A4.dir/a4.cpp.obj.provides

CMakeFiles/A4.dir/a4.cpp.obj.provides.build: CMakeFiles/A4.dir/a4.cpp.obj


# Object files for target A4
A4_OBJECTS = \
"CMakeFiles/A4.dir/main.cpp.obj" \
"CMakeFiles/A4.dir/a4.cpp.obj"

# External object files for target A4
A4_EXTERNAL_OBJECTS =

A4.exe: CMakeFiles/A4.dir/main.cpp.obj
A4.exe: CMakeFiles/A4.dir/a4.cpp.obj
A4.exe: CMakeFiles/A4.dir/build.make
A4.exe: CMakeFiles/A4.dir/linklibs.rsp
A4.exe: CMakeFiles/A4.dir/objects1.rsp
A4.exe: CMakeFiles/A4.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\LocalFiles\a4-handout\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable A4.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\A4.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/A4.dir/build: A4.exe

.PHONY : CMakeFiles/A4.dir/build

CMakeFiles/A4.dir/requires: CMakeFiles/A4.dir/main.cpp.obj.requires
CMakeFiles/A4.dir/requires: CMakeFiles/A4.dir/a4.cpp.obj.requires

.PHONY : CMakeFiles/A4.dir/requires

CMakeFiles/A4.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\A4.dir\cmake_clean.cmake
.PHONY : CMakeFiles/A4.dir/clean

CMakeFiles/A4.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\LocalFiles\a4-handout C:\LocalFiles\a4-handout C:\LocalFiles\a4-handout\cmake-build-debug C:\LocalFiles\a4-handout\cmake-build-debug C:\LocalFiles\a4-handout\cmake-build-debug\CMakeFiles\A4.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/A4.dir/depend

