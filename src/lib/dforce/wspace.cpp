#include "../../data/ct.h"
#include "immintrin.h"
#include "wspace.h"

namespace wsforces {

    void g::apply(__m128& __restrict pbx, __m128& __restrict pby, __m128& __restrict pbz, const float3a& __restrict direction) {

        pbx = _mm_add_ps(pbx, _mm_load1_ps(&direction.i[0]));
        pby = _mm_add_ps(pby, _mm_load1_ps(&direction.i[1]));
        pbz = _mm_add_ps(pbz, _mm_load1_ps(&direction.i[2]));
    };
}