# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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
CMAKE_COMMAND = C:\Users\chenx\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\191.6183.77\bin\cmake\win\bin\cmake.exe

# The command to remove a file.
RM = C:\Users\chenx\AppData\Local\JetBrains\Toolbox\apps\CLion\ch-1\191.6183.77\bin\cmake\win\bin\cmake.exe -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\Users\chenx\my-cpp-library

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo

# Include any dependencies generated for this target.
include CMakeFiles/my_cpp_library.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_cpp_library.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_cpp_library.dir/flags.make

CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj: CMakeFiles/my_cpp_library.dir/flags.make
CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj: CMakeFiles/my_cpp_library.dir/includes_CXX.rsp
CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj: ../my-cpp-library/Source.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj"
	C:\msys64\mingw64\bin\g++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\my_cpp_library.dir\my-cpp-library\Source.cpp.obj -c C:\Users\chenx\my-cpp-library\my-cpp-library\Source.cpp

CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.i"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\Users\chenx\my-cpp-library\my-cpp-library\Source.cpp > CMakeFiles\my_cpp_library.dir\my-cpp-library\Source.cpp.i

CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.s"
	C:\msys64\mingw64\bin\g++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S C:\Users\chenx\my-cpp-library\my-cpp-library\Source.cpp -o CMakeFiles\my_cpp_library.dir\my-cpp-library\Source.cpp.s

# Object files for target my_cpp_library
my_cpp_library_OBJECTS = \
"CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj"

# External object files for target my_cpp_library
my_cpp_library_EXTERNAL_OBJECTS =

my_cpp_library.exe: CMakeFiles/my_cpp_library.dir/my-cpp-library/Source.cpp.obj
my_cpp_library.exe: CMakeFiles/my_cpp_library.dir/build.make
my_cpp_library.exe: CMakeFiles/my_cpp_library.dir/linklibs.rsp
my_cpp_library.exe: CMakeFiles/my_cpp_library.dir/objects1.rsp
my_cpp_library.exe: CMakeFiles/my_cpp_library.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable my_cpp_library.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\my_cpp_library.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_cpp_library.dir/build: my_cpp_library.exe

.PHONY : CMakeFiles/my_cpp_library.dir/build

CMakeFiles/my_cpp_library.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\my_cpp_library.dir\cmake_clean.cmake
.PHONY : CMakeFiles/my_cpp_library.dir/clean

CMakeFiles/my_cpp_library.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" C:\Users\chenx\my-cpp-library C:\Users\chenx\my-cpp-library C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo C:\Users\chenx\my-cpp-library\cmake-build-relwithdebinfo\CMakeFiles\my_cpp_library.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_cpp_library.dir/depend

