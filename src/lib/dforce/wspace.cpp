#include "../../data/ct.h"
#include "immintrin.h"
#include "wspace.h"

namespace wsforces {

    void g::apply(float4x4a& __restrict particleblock, const float3a& __restrict direction) {

        __m128 pblockx = _mm_load_ps(particleblock.x);
        __m128 pblocky = _mm_load_ps(particleblock.y);
        __m128 pblockz = _mm_load_ps(particleblock.z);

        __m128 dirx = _mm_load1_ps(&direction.i[0]);
        __m128 diry = _mm_load1_ps(&direction.i[1]);
        __m128 dirz = _mm_load1_ps(&direction.i[2]);

        pblockx = _mm_add_ps(pblockx, dirx);
        pblocky = _mm_add_ps(pblocky, diry);
        pblockz = _mm_add_ps(pblockz, dirz);

        _mm_store_ps(particleblock.x, pblockx);
        _mm_store_ps(particleblock.y, pblocky);
        _mm_store_ps(particleblock.z, pblockz);
    };
}