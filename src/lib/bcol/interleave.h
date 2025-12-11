#ifndef COL_INTERLEAVE_H
#define COL_INTERLEAVE_H
#include <algorithm>
#include <cstdint>
#include <immintrin.h>
#include "../../data/ct.h"

namespace encoding {

    constexpr int gres = 10;
    constexpr int mask = (1 << gres) - 1;

    static uint32_t interleave(uint32_t& val) {

        val = (val | (val << 16)) & 0x030000FF;
        val = (val | (val << 8)) & 0x0300F00F;
        val = (val | (val << 4)) & 0x030C30C3;
        val = (val | (val << 2)) & 0x49249249;

        return val;
    }

    static __m256i hmin(__m256i v) {

        __m256i v2 = _mm256_permute2f128_si256(v, v, 1);
        v = _mm256_min_epi32(v, v2);

        v2 = _mm256_shuffle_epi32(v, 0x4E);
        v = _mm256_min_epi32(v, v2);

        v2 = _mm256_shuffle_epi32(v, 0xB1);
        v = _mm256_min_epi32(v, v2);

        return v;
    }

    static std::uint32_t z3db(const float8x3a& pos, int bmin, int bmax) {

        __m256 xf = _mm256_load_ps(pos.x);
        __m256 yf = _mm256_load_ps(pos.y);
        __m256 zf = _mm256_load_ps(pos.z);

        __m256i x = _mm256_cvtps_epi32(_mm256_mul_ps(xf, _mm256_set1_ps(65536.0f)));
        __m256i y = _mm256_cvtps_epi32(_mm256_mul_ps(yf, _mm256_set1_ps(65536.0f)));
        __m256i z = _mm256_cvtps_epi32(_mm256_mul_ps(zf, _mm256_set1_ps(65536.0f)));

        __m256i bminv = _mm256_set1_epi32(bmin);
        __m256i bmaxv = _mm256_set1_epi32(bmax);
        x = _mm256_min_epi32(_mm256_max_epi32(x, bminv), bmaxv);
        y = _mm256_min_epi32(_mm256_max_epi32(y, bminv), bmaxv);
        z = _mm256_min_epi32(_mm256_max_epi32(z, bminv), bmaxv);

        __m256i min_x = hmin(x);
        __m256i min_y = hmin(y);
        __m256i min_z = hmin(z);

        int min_x_s = _mm256_extract_epi32(min_x, 0);
        int min_y_s = _mm256_extract_epi32(min_y, 0);
        int min_z_s = _mm256_extract_epi32(min_z, 0);

        const int range = bmax - bmin;
        const int scale = (mask << 16) / range;
        int nx = ((min_x_s - bmin) * scale) >> 16;
        int ny = ((min_y_s - bmin) * scale) >> 16;
        int nz = ((min_z_s - bmin) * scale) >> 16;

        nx = std::min(nx, mask);
        ny = std::min(ny, mask);
        nz = std::min(nz, mask);

        return interleave(nx) | (interleave(ny) << 1) | (interleave(nz) << 2);
    }
}

#endif //COL_INTERLEAVE_H