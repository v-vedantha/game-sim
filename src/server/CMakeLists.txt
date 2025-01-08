cmake_minimum_required(VERSION 3.14)
project(my_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(Boost 1.87 REQUIRED) 



add_library(Server  Server.cpp
                    RoomId.cpp
                    Server.cpp
                    HttpListener.cpp
                    Rooms.cpp
                    Room.cpp
                    Uri.cpp
)



target_include_directories(
    Server
    PUBLIC ../../include/server
    PUBLIC ${Boost_INCLUDE_DIRS}
)

