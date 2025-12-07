#include "../../data/ct.h"
#include "immintrin.h"
#include "wspace.h"

namespace wsforces {

    void g::apply(__m256& pbx, __m256& pby, __m256& pbz, __m256& mas) {

        pbx = _mm256_fmadd_ps(mas, _mm256_set1_ps(gmag.i[0]), pbx);
        pby = _mm256_fmadd_ps(mas, _mm256_set1_ps(gmag.i[1]), pby);
        pbz = _mm256_fmadd_ps(mas, _mm256_set1_ps(gmag.i[2]), pbz);
    };

    void airres::apply(__m256& pbx, __m256& pby, __m256& pbz, __m256& velx, __m256& vely, __m256& velz, __m256 rad) {

        __m256 vmag = _mm256_sqrt_ps(_mm256_fmadd_ps(velx, velx, _mm256_fmadd_ps(vely, vely, _mm256_mul_ps(velz, velz))));
        __m256 area = _mm256_mul_ps(_mm256_set1_ps(3.14159265358979323846f), _mm256_mul_ps(rad, rad));

        __m256 fmag = _mm256_mul_ps(_mm256_set1_ps(-0.5f), _mm256_mul_ps(_mm256_set1_ps(rho), _mm256_mul_ps(_mm256_set1_ps(cd), _mm256_mul_ps(area, vmag))));

        pbx = _mm256_fmadd_ps(fmag, velx, pbx);
        pby = _mm256_fmadd_ps(fmag, vely, pby);
        pbz = _mm256_fmadd_ps(fmag, velz, pbz);
    }
}