#ifndef COL_DYNINTEGRATORS_H
#define COL_DYNINTEGRATORS_H
#include <vector>
#include "../../data/ct.h"
#include "../bsys/aalloc.h"
#include "../bsys/wd.h"

namespace dintegrators {
    void symeuler(float dt, std::vector<float8x3a, aalloc<float8x3a, 32>>& positions, std::vector<float8x3a, aalloc<float8x3a, 32>>& velocities, std::vector<float8x4a, aalloc<float8x4a, 32>>& masses, tpool::wd& pool);
}

#endif //COL_DYNINTEGRATORS_H