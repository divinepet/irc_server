# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.20

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
CMAKE_COMMAND = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake

# The command to remove a file.
RM = /Applications/CLion.app/Contents/bin/cmake/mac/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/cshells/Desktop/ft_irc

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/cshells/Desktop/ft_irc/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/irc_server.dir/depend.make
# Include the progress variables for this target.
include CMakeFiles/irc_server.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/irc_server.dir/flags.make

CMakeFiles/irc_server.dir/app/RunServer.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/app/RunServer.cpp.o: ../app/RunServer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/irc_server.dir/app/RunServer.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/app/RunServer.cpp.o -c /Users/cshells/Desktop/ft_irc/app/RunServer.cpp

CMakeFiles/irc_server.dir/app/RunServer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/app/RunServer.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/app/RunServer.cpp > CMakeFiles/irc_server.dir/app/RunServer.cpp.i

CMakeFiles/irc_server.dir/app/RunServer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/app/RunServer.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/app/RunServer.cpp -o CMakeFiles/irc_server.dir/app/RunServer.cpp.s

CMakeFiles/irc_server.dir/models/Channel.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/models/Channel.cpp.o: ../models/Channel.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/irc_server.dir/models/Channel.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/models/Channel.cpp.o -c /Users/cshells/Desktop/ft_irc/models/Channel.cpp

CMakeFiles/irc_server.dir/models/Channel.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/models/Channel.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/models/Channel.cpp > CMakeFiles/irc_server.dir/models/Channel.cpp.i

CMakeFiles/irc_server.dir/models/Channel.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/models/Channel.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/models/Channel.cpp -o CMakeFiles/irc_server.dir/models/Channel.cpp.s

CMakeFiles/irc_server.dir/models/User.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/models/User.cpp.o: ../models/User.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/irc_server.dir/models/User.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/models/User.cpp.o -c /Users/cshells/Desktop/ft_irc/models/User.cpp

CMakeFiles/irc_server.dir/models/User.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/models/User.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/models/User.cpp > CMakeFiles/irc_server.dir/models/User.cpp.i

CMakeFiles/irc_server.dir/models/User.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/models/User.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/models/User.cpp -o CMakeFiles/irc_server.dir/models/User.cpp.s

CMakeFiles/irc_server.dir/server/Server.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/server/Server.cpp.o: ../server/Server.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/irc_server.dir/server/Server.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/server/Server.cpp.o -c /Users/cshells/Desktop/ft_irc/server/Server.cpp

CMakeFiles/irc_server.dir/server/Server.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/server/Server.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/server/Server.cpp > CMakeFiles/irc_server.dir/server/Server.cpp.i

CMakeFiles/irc_server.dir/server/Server.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/server/Server.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/server/Server.cpp -o CMakeFiles/irc_server.dir/server/Server.cpp.s

CMakeFiles/irc_server.dir/services/YamlParser.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/services/YamlParser.cpp.o: ../services/YamlParser.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/irc_server.dir/services/YamlParser.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/services/YamlParser.cpp.o -c /Users/cshells/Desktop/ft_irc/services/YamlParser.cpp

CMakeFiles/irc_server.dir/services/YamlParser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/services/YamlParser.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/services/YamlParser.cpp > CMakeFiles/irc_server.dir/services/YamlParser.cpp.i

CMakeFiles/irc_server.dir/services/YamlParser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/services/YamlParser.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/services/YamlParser.cpp -o CMakeFiles/irc_server.dir/services/YamlParser.cpp.s

CMakeFiles/irc_server.dir/services/CommandList.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/services/CommandList.cpp.o: ../services/CommandList.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Building CXX object CMakeFiles/irc_server.dir/services/CommandList.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/services/CommandList.cpp.o -c /Users/cshells/Desktop/ft_irc/services/CommandList.cpp

CMakeFiles/irc_server.dir/services/CommandList.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/services/CommandList.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/services/CommandList.cpp > CMakeFiles/irc_server.dir/services/CommandList.cpp.i

CMakeFiles/irc_server.dir/services/CommandList.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/services/CommandList.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/services/CommandList.cpp -o CMakeFiles/irc_server.dir/services/CommandList.cpp.s

CMakeFiles/irc_server.dir/services/MessageParse.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/services/MessageParse.cpp.o: ../services/MessageParse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_7) "Building CXX object CMakeFiles/irc_server.dir/services/MessageParse.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/services/MessageParse.cpp.o -c /Users/cshells/Desktop/ft_irc/services/MessageParse.cpp

CMakeFiles/irc_server.dir/services/MessageParse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/services/MessageParse.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/services/MessageParse.cpp > CMakeFiles/irc_server.dir/services/MessageParse.cpp.i

CMakeFiles/irc_server.dir/services/MessageParse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/services/MessageParse.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/services/MessageParse.cpp -o CMakeFiles/irc_server.dir/services/MessageParse.cpp.s

CMakeFiles/irc_server.dir/services/Service.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/services/Service.cpp.o: ../services/Service.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_8) "Building CXX object CMakeFiles/irc_server.dir/services/Service.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/services/Service.cpp.o -c /Users/cshells/Desktop/ft_irc/services/Service.cpp

CMakeFiles/irc_server.dir/services/Service.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/services/Service.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/services/Service.cpp > CMakeFiles/irc_server.dir/services/Service.cpp.i

CMakeFiles/irc_server.dir/services/Service.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/services/Service.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/services/Service.cpp -o CMakeFiles/irc_server.dir/services/Service.cpp.s

CMakeFiles/irc_server.dir/services/sha256.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/services/sha256.cpp.o: ../services/sha256.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_9) "Building CXX object CMakeFiles/irc_server.dir/services/sha256.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/services/sha256.cpp.o -c /Users/cshells/Desktop/ft_irc/services/sha256.cpp

CMakeFiles/irc_server.dir/services/sha256.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/services/sha256.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/services/sha256.cpp > CMakeFiles/irc_server.dir/services/sha256.cpp.i

CMakeFiles/irc_server.dir/services/sha256.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/services/sha256.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/services/sha256.cpp -o CMakeFiles/irc_server.dir/services/sha256.cpp.s

CMakeFiles/irc_server.dir/models/Bot.cpp.o: CMakeFiles/irc_server.dir/flags.make
CMakeFiles/irc_server.dir/models/Bot.cpp.o: ../models/Bot.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_10) "Building CXX object CMakeFiles/irc_server.dir/models/Bot.cpp.o"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/irc_server.dir/models/Bot.cpp.o -c /Users/cshells/Desktop/ft_irc/models/Bot.cpp

CMakeFiles/irc_server.dir/models/Bot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/irc_server.dir/models/Bot.cpp.i"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/cshells/Desktop/ft_irc/models/Bot.cpp > CMakeFiles/irc_server.dir/models/Bot.cpp.i

CMakeFiles/irc_server.dir/models/Bot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/irc_server.dir/models/Bot.cpp.s"
	/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/cshells/Desktop/ft_irc/models/Bot.cpp -o CMakeFiles/irc_server.dir/models/Bot.cpp.s

# Object files for target irc_server
irc_server_OBJECTS = \
"CMakeFiles/irc_server.dir/app/RunServer.cpp.o" \
"CMakeFiles/irc_server.dir/models/Channel.cpp.o" \
"CMakeFiles/irc_server.dir/models/User.cpp.o" \
"CMakeFiles/irc_server.dir/server/Server.cpp.o" \
"CMakeFiles/irc_server.dir/services/YamlParser.cpp.o" \
"CMakeFiles/irc_server.dir/services/CommandList.cpp.o" \
"CMakeFiles/irc_server.dir/services/MessageParse.cpp.o" \
"CMakeFiles/irc_server.dir/services/Service.cpp.o" \
"CMakeFiles/irc_server.dir/services/sha256.cpp.o" \
"CMakeFiles/irc_server.dir/models/Bot.cpp.o"

# External object files for target irc_server
irc_server_EXTERNAL_OBJECTS =

irc_server: CMakeFiles/irc_server.dir/app/RunServer.cpp.o
irc_server: CMakeFiles/irc_server.dir/models/Channel.cpp.o
irc_server: CMakeFiles/irc_server.dir/models/User.cpp.o
irc_server: CMakeFiles/irc_server.dir/server/Server.cpp.o
irc_server: CMakeFiles/irc_server.dir/services/YamlParser.cpp.o
irc_server: CMakeFiles/irc_server.dir/services/CommandList.cpp.o
irc_server: CMakeFiles/irc_server.dir/services/MessageParse.cpp.o
irc_server: CMakeFiles/irc_server.dir/services/Service.cpp.o
irc_server: CMakeFiles/irc_server.dir/services/sha256.cpp.o
irc_server: CMakeFiles/irc_server.dir/models/Bot.cpp.o
irc_server: CMakeFiles/irc_server.dir/build.make
irc_server: CMakeFiles/irc_server.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_11) "Linking CXX executable irc_server"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/irc_server.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/irc_server.dir/build: irc_server
.PHONY : CMakeFiles/irc_server.dir/build

CMakeFiles/irc_server.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/irc_server.dir/cmake_clean.cmake
.PHONY : CMakeFiles/irc_server.dir/clean

CMakeFiles/irc_server.dir/depend:
	cd /Users/cshells/Desktop/ft_irc/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/cshells/Desktop/ft_irc /Users/cshells/Desktop/ft_irc /Users/cshells/Desktop/ft_irc/cmake-build-debug /Users/cshells/Desktop/ft_irc/cmake-build-debug /Users/cshells/Desktop/ft_irc/cmake-build-debug/CMakeFiles/irc_server.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/irc_server.dir/depend

