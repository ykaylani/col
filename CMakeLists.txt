cmake_minimum_required(VERSION 4.0)
project(col)

set(CMAKE_CXX_STANDARD 26)

add_executable(col src/main.cpp
        src/data/scn/sstore.h
        src/data/scn/dstore.h
        src/data/ct.h
        src/lib/dglobal/integrators.cpp
        src/lib/dglobal/integrators.h
        src/lib/dforce/wspace.cpp
        src/lib/dforce/wspace.h
        src/lib/dforce/lspace.cpp
        src/lib/dforce/lspace.h
        src/lib/bsys/wd.cpp
        src/lib/bsys/wd.h
        src/lib/bsys/clocks.cpp
        src/lib/bsys/clocks.cpp
)
