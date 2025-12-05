#ifndef COL_DYNINTEGRATORS_H
#define COL_DYNINTEGRATORS_H
#include <vector>
#include "../../data/ct.h"
#include "../bsys/aalloc.h"
#include "../bsys/wd.h"

namespace dintegrators {
    void symeuler(float dt, std::vector<float4x3a, aalloc<float4x3a, 16>>& positions, std::vector<float4x3a, aalloc<float4x3a, 16>>& velocities, std::vector<float4x3a, aalloc<float4x3a, 16>>& forces, std::vector<float4x4a, aalloc<float4x4a, 16>>& masses, tpool::wd& pool);
}

#endif //COL_DYNINTEGRATORS_H