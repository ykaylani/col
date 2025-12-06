#ifndef COL_STATICS_H
#define COL_STATICS_H

#include <vector>
#include "../ct.h"

namespace Statics {

    struct sobj {
        float3 pos;
        uint16_t vertcount;
        uint16_t vertoffset;
    };

    struct sstore {

        std::vector<sobj> objs;
        std::vector<float3> verts;
        std::vector<float3> normals;
    };
}

#endif //COL_STATICS_H