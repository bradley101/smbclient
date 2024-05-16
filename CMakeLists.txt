cmake_minimum_required(VERSION 3.27)
project(smbclient)

set(CMAKE_CXX_STANDARD 11)

add_library(smbclient SHARED
        include/smb_base.h
        include/smb_commands.h
        include/defines.h
        include/smb_negotiate.h
        include/smb_negotiate_contexts.h
        src/lib/smb_negotiate.cpp
        src/lib/smb_base.cpp
        include/smb_client.h
        src/lib/smb_client.cpp
        src/util/transport.cpp
        include/transport.h
)

add_executable(crawler test/crawler.cpp)
target_link_libraries(crawler smbclient)
