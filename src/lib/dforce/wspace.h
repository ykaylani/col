#ifndef COL_WORLDSPACE_H
#define COL_WORLDSPACE_H
#include "../../data/ct.h"

namespace wsforces {

    const float3a gmag = {{0.0f, -9.81f, 0.0f}};

    class g {
        public:
            static void apply(__m128& __restrict pbx, __m128& __restrict pby, __m128& __restrict pbz, const float3a& __restrict direction);
    };

    static void applyall(__m128& __restrict pbx, __m128& __restrict pby, __m128& __restrict pbz) {
        g::apply(pbx, pby, pbz, gmag);
    }
}

#endif //COL_WORLDSPACE_H