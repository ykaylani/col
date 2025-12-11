#ifndef COL_DYNAMICS_H
#define COL_DYNAMICS_H

#include <vector>
#include "../ct.h"
#include "../../lib/bsys/aalloc.h"

namespace dynamics {

    struct dstore {

        std::vector<float8x3a, aalloc<float8x3a, 32>> pos;
        std::vector<uint32_t> bpping; // encoded positions "ping"
        std::vector<uint32_t> bppong; // encoded positions "pong"
        bool ping;

        std::vector<float8x3a, aalloc<float8x3a, 32>> velocity;
        std::vector<float8x4a, aalloc<float8x4a, 32>> mass;

        std::vector<float8x4a, aalloc<float8x4a, 32>> radii;
    };
}

#endif //COL_DYNAMICS_H