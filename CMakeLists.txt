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

# ---------------------------------------------------------------------------
# Protobuf runtime
# ---------------------------------------------------------------------------

set(PROTOBUF_VERSION "36.0")

# Match this project's C++ standard.
set(ABSL_PROPAGATE_CXX_STD ON CACHE BOOL "" FORCE)

# Only build the Protobuf runtime library.
set(protobuf_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_CONFORMANCE OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_PROTOC_BINARIES OFF CACHE BOOL "" FORCE)
set(protobuf_BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
protobuf
URL
"https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protobuf-${PROTOBUF_VERSION}.tar.gz"
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_MakeAvailable(protobuf)

if(NOT TARGET protobuf::libprotobuf)
message(FATAL_ERROR
"FetchContent did not create protobuf::libprotobuf"
)
endif()

# ---------------------------------------------------------------------------
# Official precompiled protoc
# ---------------------------------------------------------------------------

if(WIN32)
FetchContent_Declare(
protoc_binary
URL
"https://github.com/protocolbuffers/protobuf/releases/download/v${PROTOBUF_VERSION}/protoc-${PROTOBUF_VERSION}-win64.zip"
DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

FetchContent_GetProperties(protoc_binary)

if(NOT protoc_binary_POPULATED)
FetchContent_Populate(protoc_binary)
endif()

set(
PROTOC_EXECUTABLE
"${protoc_binary_SOURCE_DIR}/bin/protoc.exe"
)
else()
message(FATAL_ERROR
"This configuration currently defines the protoc binary only for Windows."
)
endif()

if(NOT EXISTS "${PROTOC_EXECUTABLE}")
message(FATAL_ERROR
"protoc was not found at: ${PROTOC_EXECUTABLE}"
)
endif()

message(STATUS "Using protoc: ${PROTOC_EXECUTABLE}")

# ---------------------------------------------------------------------------
# Generate ttrpg.pb.cc and ttrpg.pb.h
# ---------------------------------------------------------------------------

set(
PROTO_FILE
"${CMAKE_CURRENT_SOURCE_DIR}/proto/ttrpg.proto"
)

set(
PROTO_GENERATED_DIR
"${CMAKE_CURRENT_BINARY_DIR}/generated"
)

set(
PROTO_GENERATED_SOURCE
"${PROTO_GENERATED_DIR}/ttrpg.pb.cc"
)

set(
PROTO_GENERATED_HEADER
"${PROTO_GENERATED_DIR}/ttrpg.pb.h"
)

file(MAKE_DIRECTORY "${PROTO_GENERATED_DIR}")

add_custom_command(
OUTPUT
"${PROTO_GENERATED_SOURCE}"
"${PROTO_GENERATED_HEADER}"

COMMAND
"${PROTOC_EXECUTABLE}"
"--proto_path=${CMAKE_CURRENT_SOURCE_DIR}/proto"
"--cpp_out=${PROTO_GENERATED_DIR}"
"${PROTO_FILE}"

DEPENDS
"${PROTO_FILE}"
"${PROTOC_EXECUTABLE}"

COMMENT
"Generating C++ sources from proto/ttrpg.proto"

VERBATIM
)

add_library(
ttrpg_proto
STATIC
"${PROTO_GENERATED_SOURCE}"
"${PROTO_GENERATED_HEADER}"
)

target_include_directories(
ttrpg_proto
PUBLIC
"$<BUILD_INTERFACE:${PROTO_GENERATED_DIR}>"
)

target_link_libraries(
ttrpg_proto
PUBLIC
protobuf::libprotobuf
)

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
    include/ttrpg/util/String.hpp src/util/String.cpp
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
    include/ttrpg/util/String.hpp src/util/String.cpp
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
        ttrpg_proto
        ftxui::screen
        ftxui::dom
        ftxui::component
)

#DEPRICATED - FTXUI
target_link_libraries(ttrpg_server
    PRIVATE
        Qt6::Widgets
        ttrpg_proto
        ftxui::screen
        ftxui::dom
        ftxui::component
)