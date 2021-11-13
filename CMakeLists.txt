cmake_minimum_required(VERSION 3.20)
project(irc_server)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)
include_directories(app)
include_directories(models)
include_directories(server)
include_directories(services)

add_executable(irc_server
        app/RunServer.cpp
        models/Channel.cpp
        models/Channel.hpp
        models/User.cpp
        models/User.hpp
        server/Server.cpp
        server/Server.hpp
        services/YamlParser.cpp
        services/YamlParser.hpp
        services/CommandList.cpp
        services/CommandList.hpp
        services/MessageParse.cpp
        services/MessageParse.hpp
        services/Service.cpp
        services/Service.hpp)
