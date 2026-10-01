cmake_minimum_required(VERSION 3.20)

project(ttrpg_rpc
    VERSION 0.1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    asio
    GIT_REPOSITORY https://github.com/chriskohlhoff/asio.git
    GIT_TAG asio-1-36-0
)

FetchContent_MakeAvailable(asio)

FetchContent_Declare(
    protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v36.2
)

set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(protobuf)

#DEPRICATED
FetchContent_Declare(
    ftxui
    GIT_REPOSITORY https://github.com/ArthurSonzogni/FTXUI.git
    GIT_TAG main
)

FetchContent_MakeAvailable(ftxui)
#END DEPRICATED

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_AUTOUIC_SEARCH_PATHS
    ${CMAKE_SOURCE_DIR}/ui/client
    ${CMAKE_SOURCE_DIR}/ui/server
)

add_executable(ttrpg_server
    src/server_main.cpp
    src/application/ServerApplication.cpp
    src/chat/ChatRoom.cpp
    src/command/ServerCommandHandler.cpp
    src/network/Connection.cpp
    src/network/Message.cpp
    src/network/Server.cpp

    #DEPRICATED - FTXUI
    src/ui/server/ServerUI.cpp

    src/user/User.cpp
    src/util/Logger.cpp
    src/util/Time.cpp

    include/ttrpg/application/ServerApplication.hpp
    include/ttrpg/chat/ChatRoom.hpp
    include/ttrpg/command/ServerCommandHandler.hpp
    include/ttrpg/network/Connection.hpp
    include/ttrpg/network/Message.hpp
    include/ttrpg/network/Server.hpp

    #DEPRICATED - FTXUI
    include/ttrpg/ui/server/ServerUI.hpp

    include/ttrpg/user/User.hpp
    include/ttrpg/util/Logger.hpp
    include/ttrpg/util/Time.hpp
)

add_executable(ttrpg_client
    src/application/ClientApplication.cpp
    src/client_main.cpp
    src/network/Client.cpp
    src/network/Message.cpp

    #DEPRICATED - FTXUI
    src/ui/client/ChatScene.cpp
    src/ui/client/ClientUI.cpp
    src/ui/client/LoginScene.cpp

    src/user/User.cpp
    src/util/Time.cpp
    src/ui/client/client_window.cpp

    include/ttrpg/application/ClientApplication.hpp
    include/ttrpg/network/Client.hpp
    include/ttrpg/network/Message.hpp

    #DEPRICATED - FTXUI
    include/ttrpg/ui/client/ChatScene.hpp
    include/ttrpg/ui/client/ClientUI.hpp
    include/ttrpg/ui/client/LoginScene.hpp

    include/ttrpg/user/User.hpp
    include/ttrpg/util/Time.hpp
    include/ttrpg/ui/client/client_window.hpp
    ui/client/LoginWindow.ui
    include/ttrpg/ui/client/LoginWindow.hpp src/ui/client/LoginWindow.cpp
)

if (WIN32)
    target_link_libraries(ttrpg_server PRIVATE ws2_32 mswsock)
    target_link_libraries(ttrpg_client PRIVATE ws2_32 mswsock)
endif()

target_include_directories(ttrpg_server
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${asio_SOURCE_DIR}/asio/include
)

target_include_directories(ttrpg_client
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
        ${asio_SOURCE_DIR}/asio/include
)

#DEPRICATED - FTXUI
target_link_libraries(ttrpg_client
    PRIVATE
        Qt6::Widgets
        protobuf::libprotobuf
        ftxui::screen
        ftxui::dom
        ftxui::component
)

#DEPRICATED - FTXUI
target_link_libraries(ttrpg_server
    PRIVATE
        Qt6::Widgets
        protobuf::libprotobuf
        ftxui::screen
        ftxui::dom
        ftxui::component
)