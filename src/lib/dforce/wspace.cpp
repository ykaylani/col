#include "../../data/ct.h"
#include "immintrin.h"
#include "wspace.h"

namespace wsforces {

    void g::apply(__m128& pbx, __m128& pby, __m128& pbz, __m128& mas, const float3a& direction) {

        pbx = _mm_fmadd_ps(mas, _mm_load1_ps(&direction.i[0]), pbx);
        pby = _mm_fmadd_ps(mas, _mm_load1_ps(&direction.i[1]), pby);
        pbz = _mm_fmadd_ps(mas, _mm_load1_ps(&direction.i[2]), pbz);
    };
}