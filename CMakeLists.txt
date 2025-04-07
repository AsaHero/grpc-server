cmake_minimum_required(VERSION 3.28)
project(protobuf)

set(CMAKE_CXX_STANDARD 17)

find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)
find_package(utf8_range REQUIRED)

set(GENPROTO_LIB "genproto_lib")
set(GENPROTO_DIR "${PROJECT_SOURCE_DIR}/genproto")

file(GLOB_RECURSE PROTO_SRC "${GENPROTO_DIR}/*.pb.cc")
file(GLOB_RECURSE PROTO_HDR "${GENPROTO_DIR}/*.pb.h")

add_library(${GENPROTO_LIB} ${PROTO_SRC} ${PROTO_HDR})

target_include_directories(${GENPROTO_LIB}
    PUBLIC
        ${GENPROTO_DIR}
)

target_link_libraries(${GENPROTO_LIB}
    PUBLIC
        protobuf::libprotobuf
        gRPC::grpc++
        utf8_range::utf8_range
        utf8_range::utf8_validity
)

add_executable(${PROJECT_NAME}
    src/main.cpp
    src/service/service.cpp
    src/server/server.cpp
)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
    ${GENPROTO_LIB}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)