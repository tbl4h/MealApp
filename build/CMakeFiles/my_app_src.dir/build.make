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
CMAKE_SOURCE_DIR = /mntpliki_mic/C++/MealApp

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mntpliki_mic/C++/MealApp/build

# Include any dependencies generated for this target.
include CMakeFiles/my_app_src.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/my_app_src.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/my_app_src.dir/flags.make

CMakeFiles/my_app_src.dir/sources/meal.cpp.o: CMakeFiles/my_app_src.dir/flags.make
CMakeFiles/my_app_src.dir/sources/meal.cpp.o: ../sources/meal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mntpliki_mic/C++/MealApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/my_app_src.dir/sources/meal.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_app_src.dir/sources/meal.cpp.o -c /mntpliki_mic/C++/MealApp/sources/meal.cpp

CMakeFiles/my_app_src.dir/sources/meal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_app_src.dir/sources/meal.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mntpliki_mic/C++/MealApp/sources/meal.cpp > CMakeFiles/my_app_src.dir/sources/meal.cpp.i

CMakeFiles/my_app_src.dir/sources/meal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_app_src.dir/sources/meal.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mntpliki_mic/C++/MealApp/sources/meal.cpp -o CMakeFiles/my_app_src.dir/sources/meal.cpp.s

CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o: CMakeFiles/my_app_src.dir/flags.make
CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o: ../sources/meals_list.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mntpliki_mic/C++/MealApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o -c /mntpliki_mic/C++/MealApp/sources/meals_list.cpp

CMakeFiles/my_app_src.dir/sources/meals_list.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_app_src.dir/sources/meals_list.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mntpliki_mic/C++/MealApp/sources/meals_list.cpp > CMakeFiles/my_app_src.dir/sources/meals_list.cpp.i

CMakeFiles/my_app_src.dir/sources/meals_list.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_app_src.dir/sources/meals_list.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mntpliki_mic/C++/MealApp/sources/meals_list.cpp -o CMakeFiles/my_app_src.dir/sources/meals_list.cpp.s

CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o: CMakeFiles/my_app_src.dir/flags.make
CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o: ../sources/parse_meal.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mntpliki_mic/C++/MealApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o -c /mntpliki_mic/C++/MealApp/sources/parse_meal.cpp

CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mntpliki_mic/C++/MealApp/sources/parse_meal.cpp > CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.i

CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mntpliki_mic/C++/MealApp/sources/parse_meal.cpp -o CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.s

CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o: CMakeFiles/my_app_src.dir/flags.make
CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o: ../sources/rolling_function.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mntpliki_mic/C++/MealApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o"
	/bin/x86_64-linux-gnu-g++-9  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o -c /mntpliki_mic/C++/MealApp/sources/rolling_function.cpp

CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.i"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mntpliki_mic/C++/MealApp/sources/rolling_function.cpp > CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.i

CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.s"
	/bin/x86_64-linux-gnu-g++-9 $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mntpliki_mic/C++/MealApp/sources/rolling_function.cpp -o CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.s

# Object files for target my_app_src
my_app_src_OBJECTS = \
"CMakeFiles/my_app_src.dir/sources/meal.cpp.o" \
"CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o" \
"CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o" \
"CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o"

# External object files for target my_app_src
my_app_src_EXTERNAL_OBJECTS =

lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/sources/meal.cpp.o
lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/sources/meals_list.cpp.o
lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/sources/parse_meal.cpp.o
lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/sources/rolling_function.cpp.o
lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/build.make
lib/libmy_app_src.so: CMakeFiles/my_app_src.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mntpliki_mic/C++/MealApp/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Linking CXX shared library lib/libmy_app_src.so"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/my_app_src.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/my_app_src.dir/build: lib/libmy_app_src.so

.PHONY : CMakeFiles/my_app_src.dir/build

CMakeFiles/my_app_src.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/my_app_src.dir/cmake_clean.cmake
.PHONY : CMakeFiles/my_app_src.dir/clean

CMakeFiles/my_app_src.dir/depend:
	cd /mntpliki_mic/C++/MealApp/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mntpliki_mic/C++/MealApp /mntpliki_mic/C++/MealApp /mntpliki_mic/C++/MealApp/build /mntpliki_mic/C++/MealApp/build /mntpliki_mic/C++/MealApp/build/CMakeFiles/my_app_src.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/my_app_src.dir/depend

