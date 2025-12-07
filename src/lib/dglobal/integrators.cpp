#include <vector>
#include <immintrin.h>
#include "integrators.h"
#include "../../data/ct.h"
#include "../dforce/wspace.h"
#include "../bsys/wd.h"
#include "../bsys/aalloc.h"


namespace dintegrators { //Assumption: scalar types contain 4 times the number of particles compared to vector types. Array float4x4a "masses" holds data for 16 particles whilst Array float4x3a "positions" only holds data for 4 particles.

    void psymeuler(int start, int end, std::vector<float8x3a, aalloc<float8x3a, 32>>& __restrict positions, std::vector<float8x3a, aalloc<float8x3a, 32>>& __restrict velocities, std::vector<float8x4a, aalloc<float8x4a, 32>>& __restrict masses, std::vector<float8x4a, aalloc<float8x4a, 32>>& __restrict radii, float dt) {

        __m256 dts = _mm256_set1_ps(dt);

        for (int i = start; i < end; i++) {

            int scalaridx = i;
            int vectoridx = scalaridx * 4;
            int vidx2 = vectoridx + 1;
            int vidx3 = vectoridx + 2;
            int vidx4 = vectoridx + 3;

            __m256 massblock = _mm256_load_ps(masses[scalaridx].x);

            __m256 posx = _mm256_load_ps(positions[vectoridx].x);
            __m256 posy = _mm256_load_ps(positions[vectoridx].y);
            __m256 posz = _mm256_load_ps(positions[vectoridx].z);
            __m256 velx = _mm256_load_ps(velocities[vectoridx].x);

            __m256 vely = _mm256_load_ps(velocities[vectoridx].y);
            __m256 velz = _mm256_load_ps(velocities[vectoridx].z);
            __m256 forx = _mm256_setzero_ps();
            __m256 fory = _mm256_setzero_ps();
            __m256 forz = _mm256_setzero_ps();

            wsforces::applyall(forx, fory, forz, velx, vely, velz, _mm256_load_ps(radii[scalaridx].x), massblock);
            __m256 r1 = _mm256_mul_ps(dts, massblock);
            velx = _mm256_fmadd_ps(forx, r1, velx);
            vely = _mm256_fmadd_ps(fory, r1, vely);
            velz = _mm256_fmadd_ps(forz, r1, velz);
            posx = _mm256_fmadd_ps(velx, dts, posx);
            posy = _mm256_fmadd_ps(vely, dts, posy);
            posz = _mm256_fmadd_ps(velz, dts, posz);
            _mm256_store_ps(velocities[vectoridx].x, velx);
            _mm256_store_ps(velocities[vectoridx].y, vely);
            _mm256_store_ps(velocities[vectoridx].z, velz);
            _mm256_store_ps(positions[vectoridx].x, posx);
            _mm256_store_ps(positions[vectoridx].y, posy);
            _mm256_store_ps(positions[vectoridx].z, posz);

            massblock = _mm256_load_ps(masses[scalaridx].y);
            posx = _mm256_load_ps(positions[vidx2].x);
            posy = _mm256_load_ps(positions[vidx2].y);
            posz = _mm256_load_ps(positions[vidx2].z);
            velx = _mm256_load_ps(velocities[vidx2].x);
            vely = _mm256_load_ps(velocities[vidx2].y);
            velz = _mm256_load_ps(velocities[vidx2].z);
            forx = _mm256_setzero_ps();
            fory = _mm256_setzero_ps();
            forz = _mm256_setzero_ps();

            wsforces::applyall(forx, fory, forz, velx, vely, velz, _mm256_load_ps(radii[scalaridx].y), massblock);
            r1 = _mm256_mul_ps(dts, massblock);
            velx = _mm256_fmadd_ps(forx, r1, velx);
            vely = _mm256_fmadd_ps(fory, r1, vely);
            velz = _mm256_fmadd_ps(forz, r1, velz);
            posx = _mm256_fmadd_ps(velx, dts, posx);
            posy = _mm256_fmadd_ps(vely, dts, posy);
            posz = _mm256_fmadd_ps(velz, dts, posz);
            _mm256_store_ps(velocities[vidx2].x, velx);
            _mm256_store_ps(velocities[vidx2].y, vely);
            _mm256_store_ps(velocities[vidx2].z, velz);
            _mm256_store_ps(positions[vidx2].x, posx);
            _mm256_store_ps(positions[vidx2].y, posy);
            _mm256_store_ps(positions[vidx2].z, posz);

            massblock = _mm256_load_ps(masses[scalaridx].z);
            posx = _mm256_load_ps(positions[vidx3].x);
            posy = _mm256_load_ps(positions[vidx3].y);
            posz = _mm256_load_ps(positions[vidx3].z);
            velx = _mm256_load_ps(velocities[vidx3].x);
            vely = _mm256_load_ps(velocities[vidx3].y);
            velz = _mm256_load_ps(velocities[vidx3].z);
            forx = _mm256_setzero_ps();
            fory = _mm256_setzero_ps();
            forz = _mm256_setzero_ps();

            wsforces::applyall(forx, fory, forz, velx, vely, velz, _mm256_load_ps(radii[scalaridx].z), massblock);
            r1 = _mm256_mul_ps(dts, massblock);
            velx = _mm256_fmadd_ps(forx, r1, velx);
            vely = _mm256_fmadd_ps(fory, r1, vely);
            velz = _mm256_fmadd_ps(forz, r1, velz);
            posx = _mm256_fmadd_ps(velx, dts, posx);
            posy = _mm256_fmadd_ps(vely, dts, posy);
            posz = _mm256_fmadd_ps(velz, dts, posz);
            _mm256_store_ps(velocities[vidx3].x, velx);
            _mm256_store_ps(velocities[vidx3].y, vely);
            _mm256_store_ps(velocities[vidx3].z, velz);
            _mm256_store_ps(positions[vidx3].x, posx);
            _mm256_store_ps(positions[vidx3].y, posy);
            _mm256_store_ps(positions[vidx3].z, posz);

            massblock = _mm256_load_ps(masses[scalaridx].w);
            posx = _mm256_load_ps(positions[vidx4].x);
            posy = _mm256_load_ps(positions[vidx4].y);
            posz = _mm256_load_ps(positions[vidx4].z);
            velx = _mm256_load_ps(velocities[vidx4].x);
            vely = _mm256_load_ps(velocities[vidx4].y);
            velz = _mm256_load_ps(velocities[vidx4].z);
            forx = _mm256_setzero_ps();
            fory = _mm256_setzero_ps();
            forz = _mm256_setzero_ps();

            wsforces::applyall(forx, fory, forz, velx, vely, velz, _mm256_load_ps(radii[scalaridx].w), massblock);
            r1 = _mm256_mul_ps(dts, massblock);
            velx = _mm256_fmadd_ps(forx, r1, velx);
            vely = _mm256_fmadd_ps(fory, r1, vely);
            velz = _mm256_fmadd_ps(forz, r1, velz);
            posx = _mm256_fmadd_ps(velx, dts, posx);
            posy = _mm256_fmadd_ps(vely, dts, posy);
            posz = _mm256_fmadd_ps(velz, dts, posz);
            _mm256_store_ps(velocities[vidx4].x, velx);
            _mm256_store_ps(velocities[vidx4].y, vely);
            _mm256_store_ps(velocities[vidx4].z, velz);
            _mm256_store_ps(positions[vidx4].x, posx);
            _mm256_store_ps(positions[vidx4].y, posy);
            _mm256_store_ps(positions[vidx4].z, posz);
        }

    }

    void symeuler(float dt, std::vector<float8x3a, aalloc<float8x3a, 32>>& positions, std::vector<float8x3a, aalloc<float8x3a, 32>>& velocities, std::vector<float8x4a, aalloc<float8x4a, 32>>& masses, std::vector<float8x4a, aalloc<float8x4a, 32>>& radii, tpool::wd& pool) {

        unsigned int tc = pool.inittc;
        int blocks = masses.size();

        if (blocks * 16 > 131072) {

            int cs = (blocks + tc - 1) / tc;

            for (unsigned int i = 0; i < tc; i++) {
                int start = i * cs;
                int end = std::min(start + cs, blocks);
                pool.schedule(psymeuler, start, end, std::ref(positions), std::ref(velocities), std::ref(masses), std::ref(radii), dt);
            }

            pool.wait();
        }
        else {
            int start = 0;
            int end = blocks;

            psymeuler(start, end, std::ref(positions), std::ref(velocities), std::ref(masses), std::ref(radii), dt);
        }
    }
}
