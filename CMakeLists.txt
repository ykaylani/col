cmake_minimum_required(VERSION 4.0)
project(col)

set(CMAKE_CXX_STANDARD 26)

add_executable(col src/main.cpp
        src/data/scn/sstore.h
        src/data/scn/dstore.h
        src/data/ct.h
        src/data/rt/time.h
        src/lib/dynintegrators.cpp
        src/lib/dynintegrators.h
        src/lib/force/wspace.cpp
        src/lib/force/wspace.h
        src/lib/force/lspace.cpp
        src/lib/force/lspace.h
)
