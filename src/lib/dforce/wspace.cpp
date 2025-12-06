#include "../../data/ct.h"
#include "immintrin.h"
#include "wspace.h"

namespace wsforces {

    void g::apply(__m256& pbx, __m256& pby, __m256& pbz, __m256& mas, const float3a& direction) {

        pbx = _mm256_fmadd_ps(mas, _mm256_set1_ps(direction.i[0]), pbx);
        pby = _mm256_fmadd_ps(mas, _mm256_set1_ps(direction.i[1]), pby);
        pbz = _mm256_fmadd_ps(mas, _mm256_set1_ps(direction.i[2]), pbz);
    };
}