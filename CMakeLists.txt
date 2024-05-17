cmake_minimum_required(VERSION 3.27)
project(smbclient)

set(CMAKE_CXX_STANDARD 11)

add_library(smbclient SHARED
        src/lib/smb_negotiate.cpp
        src/lib/smb_base.cpp
        src/lib/smb_client.cpp
        src/util/transport.cpp
        src/util/memory.cpp
        include/memory.h
)

add_executable(crawler test/crawler.cpp)
target_link_libraries(crawler smbclient)
