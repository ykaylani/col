#ifndef COL_DYNAMICS_H
#define COL_DYNAMICS_H

#include <vector>
#include "../ct.h"
#include "../../lib/bsys/aalloc.h"

namespace dynamics {
    struct dstore {

        std::vector<float4x3a, aalloc<float4x3a, 16>> velocity;
        std::vector<float4x3a, aalloc<float4x3a, 16>> force;
        std::vector<float4x3a, aalloc<float4x3a, 16>> pos;
        std::vector<float4x4a, aalloc<float4x4a, 16>> mass;
    };
}

#endif COL_DYNAMICS_H