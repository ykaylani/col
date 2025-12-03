cmake_minimum_required(VERSION 4.0)
project(col)

set(CMAKE_CXX_STANDARD 26)

add_executable(col src/main.cpp
        src/data/scn/sstore.h
        src/data/scn/dstore.h
        src/data/ct.h
        src/lib/sglobal/time.h
        src/lib/dglobal/dynintegrators.cpp
        src/lib/dglobal/dynintegrators.h
        src/lib/dforce/wspace.cpp
        src/lib/dforce/wspace.h
        src/lib/dforce/lspace.cpp
        src/lib/dforce/lspace.h
        src/lib/sglobal/time.cpp
)
