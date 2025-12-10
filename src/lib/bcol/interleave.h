#ifndef COL_INTERLEAVE_H
#define COL_INTERLEAVE_H
#include <immintrin.h>

namespace encoding {

    constexpr int gres = 15;
    constexpr int mask = (1 << gres) - 1;

    static __m256i interleave(__m256i val) {

        val = _mm256_and_si256(_mm256_or_si256(val, _mm256_slli_epi32(val, 16)), _mm256_set1_epi32(0x030000FF));
        val = _mm256_and_si256(_mm256_or_si256(val, _mm256_slli_epi32(val, 8)), _mm256_set1_epi32(0x0300F00F));
        val = _mm256_and_si256(_mm256_or_si256(val, _mm256_slli_epi32(val, 4)), _mm256_set1_epi32(0x030C30C3));
        val = _mm256_and_si256(_mm256_or_si256(val, _mm256_slli_epi32(val, 2)), _mm256_set1_epi32(0x49249249));
        return val;
    }

    static __m256i z3d(__m256i x, __m256i y, __m256i z, __m256i bmin, __m256i bmax) {

        x = _mm256_min_epi32(_mm256_max_epi32(x, bmin), bmax);
        y = _mm256_min_epi32(_mm256_max_epi32(y, bmin), bmax);
        z = _mm256_min_epi32(_mm256_max_epi32(z, bmin), bmax);

        int bmins = _mm_cvtsi128_si32(_mm256_castsi256_si128(bmin));
        int bmaxs = _mm_cvtsi128_si32(_mm256_castsi256_si128(bmax));

        const int range = bmaxs - bmins;
        const int scale = ((mask << 16) + range - 1) / range;

        __m256i scalev = _mm256_set1_epi32(scale);

        __m256i nx = _mm256_sub_epi32(x, bmin);
        __m256i ny = _mm256_sub_epi32(y, bmin);
        __m256i nz = _mm256_sub_epi32(z, bmin);

        nx = _mm256_mullo_epi32(nx, scalev);
        nx = _mm256_srli_epi32(nx, 16);

        ny = _mm256_mullo_epi32(ny, scalev);
        ny = _mm256_srli_epi32(ny, 16);

        nz = _mm256_mullo_epi32(nz, scalev);
        nz = _mm256_srli_epi32(nz, 16);

        return _mm256_or_si256(_mm256_or_si256(interleave(nx), _mm256_slli_epi32(interleave(ny), 1)), _mm256_slli_epi32(interleave(nz), 2));
    }
}

#endif //COL_INTERLEAVE_H