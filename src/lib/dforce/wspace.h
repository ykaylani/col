#ifndef COL_WORLDSPACE_H
#define COL_WORLDSPACE_H
#include "../../data/ct.h"

namespace wsforces {

    const float3a gmag = {{0.0f, -9.81f, 0.0f}};

    class g {
        public:
            static void apply(__m256& pbx, __m256& pby, __m256& pbz, __m256& mas, const float3a& direction);
    };

    static void applyall(__m256& pbx, __m256& pby, __m256& pbz, __m256& mas) {
        g::apply(pbx, pby, pbz, mas, gmag);
    }
}

#endif //COL_WORLDSPACE_H