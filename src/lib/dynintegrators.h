#ifndef COL_DYNINTEGRATORS_H
#define COL_DYNINTEGRATORS_H
#include <vector>
#include "../data/ct.h"

namespace dintegrators {
    void symeuler(float dt, std::vector<float4x4a>& positions, std::vector<float4x4a>& velocities, std::vector<float4x4a>& forces, std::vector<float16a>& masses);
}

#endif //COL_DYNINTEGRATORS_H