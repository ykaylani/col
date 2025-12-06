#ifndef COL_DYNAMICS_H
#define COL_DYNAMICS_H

#include <vector>
#include "../ct.h"
#include "../../lib/bsys/aalloc.h"

namespace dynamics {

    enum class meshtype : uint8_t {
        Spherical = 0,
        Cubic = 1
    };


    struct dstore {

        std::vector<float8x3a, aalloc<float8x3a, 32>> velocity;
        std::vector<float8x3a, aalloc<float8x3a, 32>> pos;
        std::vector<float8x4a, aalloc<float8x4a, 32>> mass;

        std::vector<meshtype> mtype;
        std::vector<float> ssize; //Would be radius for sphere, line segment for cubes
    };
}

#endif COL_DYNAMICS_H