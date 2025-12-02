#ifndef COL_STATICS_H
#define COL_STATICS_H

#include <vector>
#include "../ct.h"

namespace Statics {
    struct sstore { // only cubes allowed for now

        std::vector<float3x5a> pos;
        std::vector<float3x5a> size;
    };
}

#endif COL_STATICS_H