cmake_minimum_required(VERSION 4.0)
project(col)

set(CMAKE_CXX_STANDARD 26)

add_executable(col src/main.cpp
        src/lib/dglobal/integrators.cpp
        src/lib/dforce/wspace.cpp
        src/lib/dforce/lspace.cpp
        src/lib/bsys/wd.cpp
        src/data/scn/dstore.h
        src/lib/bsys/aalloc.h
)
