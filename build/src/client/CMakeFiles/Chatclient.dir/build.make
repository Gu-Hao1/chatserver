# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/gu/Chat/chatserver

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/gu/Chat/chatserver/build

# Include any dependencies generated for this target.
include src/client/CMakeFiles/Chatclient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include src/client/CMakeFiles/Chatclient.dir/compiler_depend.make

# Include the progress variables for this target.
include src/client/CMakeFiles/Chatclient.dir/progress.make

# Include the compile flags for this target's objects.
include src/client/CMakeFiles/Chatclient.dir/flags.make

src/client/CMakeFiles/Chatclient.dir/main.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/main.cpp.o: ../src/client/main.cpp
src/client/CMakeFiles/Chatclient.dir/main.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object src/client/CMakeFiles/Chatclient.dir/main.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/main.cpp.o -MF CMakeFiles/Chatclient.dir/main.cpp.o.d -o CMakeFiles/Chatclient.dir/main.cpp.o -c /home/gu/Chat/chatserver/src/client/main.cpp

src/client/CMakeFiles/Chatclient.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/main.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/client/main.cpp > CMakeFiles/Chatclient.dir/main.cpp.i

src/client/CMakeFiles/Chatclient.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/main.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/client/main.cpp -o CMakeFiles/Chatclient.dir/main.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o: ../src/server/model/friendmodel.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o -c /home/gu/Chat/chatserver/src/server/model/friendmodel.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/friendmodel.cpp > CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/friendmodel.cpp -o CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o: ../src/server/model/group.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o -c /home/gu/Chat/chatserver/src/server/model/group.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/group.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/group.cpp > CMakeFiles/Chatclient.dir/__/server/model/group.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/group.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/group.cpp -o CMakeFiles/Chatclient.dir/__/server/model/group.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o: ../src/server/model/groupmodel.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o -c /home/gu/Chat/chatserver/src/server/model/groupmodel.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/groupmodel.cpp > CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/groupmodel.cpp -o CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o: ../src/server/model/groupuser.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o -c /home/gu/Chat/chatserver/src/server/model/groupuser.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/groupuser.cpp > CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/groupuser.cpp -o CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o: ../src/server/model/offlinemessagemodel.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o -c /home/gu/Chat/chatserver/src/server/model/offlinemessagemodel.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/offlinemessagemodel.cpp > CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/offlinemessagemodel.cpp -o CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o: ../src/server/model/user.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o -c /home/gu/Chat/chatserver/src/server/model/user.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/user.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/user.cpp > CMakeFiles/Chatclient.dir/__/server/model/user.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/user.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/user.cpp -o CMakeFiles/Chatclient.dir/__/server/model/user.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o: ../src/server/model/usermodel.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o -c /home/gu/Chat/chatserver/src/server/model/usermodel.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/model/usermodel.cpp > CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/model/usermodel.cpp -o CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.s

src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o: src/client/CMakeFiles/Chatclient.dir/flags.make
src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o: ../src/server/db/db.cpp
src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o: src/client/CMakeFiles/Chatclient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o -MF CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o.d -o CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o -c /home/gu/Chat/chatserver/src/server/db/db.cpp

src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Chatclient.dir/__/server/db/db.cpp.i"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/gu/Chat/chatserver/src/server/db/db.cpp > CMakeFiles/Chatclient.dir/__/server/db/db.cpp.i

src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Chatclient.dir/__/server/db/db.cpp.s"
	cd /home/gu/Chat/chatserver/build/src/client && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/gu/Chat/chatserver/src/server/db/db.cpp -o CMakeFiles/Chatclient.dir/__/server/db/db.cpp.s

# Object files for target Chatclient
Chatclient_OBJECTS = \
"CMakeFiles/Chatclient.dir/main.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o" \
"CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o"

# External object files for target Chatclient
Chatclient_EXTERNAL_OBJECTS =

../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/main.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/friendmodel.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/group.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/groupmodel.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/groupuser.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/offlinemessagemodel.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/user.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/model/usermodel.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/__/server/db/db.cpp.o
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/build.make
../bin/Chatclient: src/client/CMakeFiles/Chatclient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/gu/Chat/chatserver/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Linking CXX executable ../../../bin/Chatclient"
	cd /home/gu/Chat/chatserver/build/src/client && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Chatclient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
src/client/CMakeFiles/Chatclient.dir/build: ../bin/Chatclient
.PHONY : src/client/CMakeFiles/Chatclient.dir/build

src/client/CMakeFiles/Chatclient.dir/clean:
	cd /home/gu/Chat/chatserver/build/src/client && $(CMAKE_COMMAND) -P CMakeFiles/Chatclient.dir/cmake_clean.cmake
.PHONY : src/client/CMakeFiles/Chatclient.dir/clean

src/client/CMakeFiles/Chatclient.dir/depend:
	cd /home/gu/Chat/chatserver/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/gu/Chat/chatserver /home/gu/Chat/chatserver/src/client /home/gu/Chat/chatserver/build /home/gu/Chat/chatserver/build/src/client /home/gu/Chat/chatserver/build/src/client/CMakeFiles/Chatclient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/client/CMakeFiles/Chatclient.dir/depend
