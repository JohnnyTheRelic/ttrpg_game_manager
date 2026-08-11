cmake_minimum_required(VERSION 3.20)

project(ttrpg_rpc
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(ASIO_INCLUDE_DIR
    "C:/Users/rjbur/Documents/asio-1.36.0/asio-1.36.0/include"
)

add_executable(ttrpg_server
    src/server_main.cpp
    src/chat/ChatRoom.cpp
    src/command/ServerCommandHandler.cpp
    src/network/Connection.cpp
    src/network/Message.cpp
    src/network/Server.cpp
    src/user/User.cpp
    src/util/Logger.cpp
    src/util/Time.cpp
)

add_executable(ttrpg_client
    src/application/ClientApplication.cpp
    src/client_main.cpp
    src/network/Client.cpp
    src/network/Message.cpp
    src/user/User.cpp
    src/util/Time.cpp
)

target_include_directories(ttrpg_server
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${ASIO_INCLUDE_DIR}
)

target_include_directories(ttrpg_client
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${ASIO_INCLUDE_DIR}
)