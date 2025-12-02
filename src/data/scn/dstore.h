#ifndef COL_DYNAMICS_H
#define COL_DYNAMICS_H

#include <vector>
#include "../ct.h"

namespace dynamics {
    struct dstore {

        std::vector<float4x4a> velocity;
        std::vector<float4x4a> force;
        std::vector<float4x4a> pos;
        std::vector<float4x4a> mass;
    };
}

#endif COL_DYNAMICS_H