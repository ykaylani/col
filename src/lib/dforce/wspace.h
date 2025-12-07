#ifndef COL_WORLDSPACE_H
#define COL_WORLDSPACE_H
#include "../../data/ct.h"

namespace wsforces {

    class g {
        public:
            static constexpr float3a gmag = {{0.0f, -9.81f, 0.0f}};
            static void apply(__m256& pbx, __m256& pby, __m256& pbz, const __m256& mas);
    };

    class airres {
        public:
            static constexpr float rho = 1.225f;
            static constexpr float cd = 0.42f;
            static void apply(__m256& pbx, __m256& pby, __m256& pbz, const __m256& velx, const __m256& vely, const __m256& velz, const __m256 rad);
    };

    static void applyall(__m256& pbx, __m256& pby, __m256& pbz, const __m256& velx, const __m256& vely, const __m256& velz, const __m256 rad, const __m256& mas) {
        g::apply(pbx, pby, pbz, mas);
        airres::apply(pbx, pby, pbz, velx, vely, velz, rad);
    }
}

#endif //COL_WORLDSPACE_H