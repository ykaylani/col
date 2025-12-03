#ifndef COL_WORLDSPACE_H
#define COL_WORLDSPACE_H
#include "../../data/ct.h"

namespace wsforces {

    const float3a gmag = {{0.0f, -9.81f, 0.0f}};

    class g {
        public:
            static void apply(float4x4a& __restrict particleblock, const float3a& __restrict direction);
    };
}

#endif //COL_WORLDSPACE_H