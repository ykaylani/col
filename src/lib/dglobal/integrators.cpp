#include <vector>
#include <immintrin.h>
#include <thread>
#include <atomic>
#include "integrators.h"
#include "../../data/ct.h"
#include "../dforce/wspace.h"
#include "../bsys/wd.h"


namespace dintegrators { //Assumption: scalar types contain 4 times the number of particles compared to vector types. Array float4x4a "masses" holds data for 16 particles whilst Array float4x3a "positions" only holds data for 4 particles.

    const int callgranularity = 64;

    void psymeuler(std::atomic<int>& unprocessedblock, int tblocks, std::vector<float4x3a>& positions, std::vector<float4x3a>& velocities, std::vector<float4x3a>& forces, std::vector<float4x4a>& masses, float dt) {

        while (true) {
            int scheduleindex = unprocessedblock.fetch_add(callgranularity);
            if (scheduleindex >= tblocks) { return; }

            __m128 dts = _mm_load1_ps(&dt);

            for (int i = 0; i < callgranularity && scheduleindex + i < tblocks; i++) {

                int vectoridx = (scheduleindex + i) * 4;
                int scalaridx = (scheduleindex + i);

                int vidx2 = vectoridx + 1;
                int vidx3 = vectoridx + 2;
                int vidx4 = vectoridx + 3;

                __m128 massblock1 = _mm_load_ps(masses[scalaridx].x);
                __m128 massblock2 = _mm_load_ps(masses[scalaridx].y);
                __m128 massblock3 = _mm_load_ps(masses[scalaridx].z);
                __m128 massblock4 = _mm_load_ps(masses[scalaridx].w);

                __m128 posx = _mm_load_ps(positions[vectoridx].x);
                __m128 posy = _mm_load_ps(positions[vectoridx].y);
                __m128 posz = _mm_load_ps(positions[vectoridx].z);

                __m128 velx = _mm_load_ps(velocities[vectoridx].x);
                __m128 vely = _mm_load_ps(velocities[vectoridx].y);
                __m128 velz = _mm_load_ps(velocities[vectoridx].z);

                __m128 forx = _mm_load_ps(forces[vectoridx].x);
                __m128 fory = _mm_load_ps(forces[vectoridx].y);
                __m128 forz = _mm_load_ps(forces[vectoridx].z);

                wsforces::g::apply(forx, fory, forz, wsforces::gmag);
                __m128 r1 = _mm_div_ps(dts, massblock1);
                velx = _mm_add_ps(velx, _mm_mul_ps(forx, r1));
                vely = _mm_add_ps(vely, _mm_mul_ps(fory, r1));
                velz = _mm_add_ps(velz, _mm_mul_ps(forz, r1));
                posx = _mm_add_ps(posx, _mm_mul_ps(velx, dts));
                posy = _mm_add_ps(posy, _mm_mul_ps(vely, dts));
                posz = _mm_add_ps(posz, _mm_mul_ps(velz, dts));
                _mm_store_ps(velocities[vectoridx].x, velx);
                _mm_store_ps(velocities[vectoridx].y, vely);
                _mm_store_ps(velocities[vectoridx].z, velz);
                _mm_store_ps(positions[vectoridx].x, posx);
                _mm_store_ps(positions[vectoridx].y, posy);
                _mm_store_ps(positions[vectoridx].z, posz);

                posx = _mm_load_ps(positions[vidx2].x);
                posy = _mm_load_ps(positions[vidx2].y);
                posz = _mm_load_ps(positions[vidx2].z);

                velx = _mm_load_ps(velocities[vidx2].x);
                vely = _mm_load_ps(velocities[vidx2].y);
                velz = _mm_load_ps(velocities[vidx2].z);

                forx = _mm_load_ps(forces[vidx2].x);
                fory = _mm_load_ps(forces[vidx2].y);
                forz = _mm_load_ps(forces[vidx2].z);

                wsforces::g::apply(forx, fory, forz, wsforces::gmag);
                r1 = _mm_div_ps(dts, massblock2);
                velx = _mm_add_ps(velx, _mm_mul_ps(forx, r1));
                vely = _mm_add_ps(vely, _mm_mul_ps(fory, r1));
                velz = _mm_add_ps(velz, _mm_mul_ps(forz, r1));
                posx = _mm_add_ps(posx, _mm_mul_ps(velx, dts));
                posy = _mm_add_ps(posy, _mm_mul_ps(vely, dts));
                posz = _mm_add_ps(posz, _mm_mul_ps(velz, dts));
                _mm_store_ps(velocities[vidx2].x, velx);
                _mm_store_ps(velocities[vidx2].y, vely);
                _mm_store_ps(velocities[vidx2].z, velz);
                _mm_store_ps(positions[vidx2].x, posx);
                _mm_store_ps(positions[vidx2].y, posy);
                _mm_store_ps(positions[vidx2].z, posz);

                posx = _mm_load_ps(positions[vidx3].x);
                posy = _mm_load_ps(positions[vidx3].y);
                posz = _mm_load_ps(positions[vidx3].z);

                velx = _mm_load_ps(velocities[vidx3].x);
                vely = _mm_load_ps(velocities[vidx3].y);
                velz = _mm_load_ps(velocities[vidx3].z);

                forx = _mm_load_ps(forces[vidx3].x);
                fory = _mm_load_ps(forces[vidx3].y);
                forz = _mm_load_ps(forces[vidx3].z);

                wsforces::g::apply(forx, fory, forz, wsforces::gmag);
                r1 = _mm_div_ps(dts, massblock3);
                velx = _mm_add_ps(velx, _mm_mul_ps(forx, r1));
                vely = _mm_add_ps(vely, _mm_mul_ps(fory, r1));
                velz = _mm_add_ps(velz, _mm_mul_ps(forz, r1));
                posx = _mm_add_ps(posx, _mm_mul_ps(velx, dts));
                posy = _mm_add_ps(posy, _mm_mul_ps(vely, dts));
                posz = _mm_add_ps(posz, _mm_mul_ps(velz, dts));
                _mm_store_ps(velocities[vidx3].x, velx);
                _mm_store_ps(velocities[vidx3].y, vely);
                _mm_store_ps(velocities[vidx3].z, velz);
                _mm_store_ps(positions[vidx3].x, posx);
                _mm_store_ps(positions[vidx3].y, posy);
                _mm_store_ps(positions[vidx3].z, posz);

                posx = _mm_load_ps(positions[vidx4].x);
                posy = _mm_load_ps(positions[vidx4].y);
                posz = _mm_load_ps(positions[vidx4].z);

                velx = _mm_load_ps(velocities[vidx4].x);
                vely = _mm_load_ps(velocities[vidx4].y);
                velz = _mm_load_ps(velocities[vidx4].z);

                forx = _mm_load_ps(forces[vidx4].x);
                fory = _mm_load_ps(forces[vidx4].y);
                forz = _mm_load_ps(forces[vidx4].z);

                wsforces::g::apply(forx, fory, forz, wsforces::gmag);
                r1 = _mm_div_ps(dts, massblock4);
                velx = _mm_add_ps(velx, _mm_mul_ps(forx, r1));
                vely = _mm_add_ps(vely, _mm_mul_ps(fory, r1));
                velz = _mm_add_ps(velz, _mm_mul_ps(forz, r1));
                posx = _mm_add_ps(posx, _mm_mul_ps(velx, dts));
                posy = _mm_add_ps(posy, _mm_mul_ps(vely, dts));
                posz = _mm_add_ps(posz, _mm_mul_ps(velz, dts));
                _mm_store_ps(velocities[vidx4].x, velx);
                _mm_store_ps(velocities[vidx4].y, vely);
                _mm_store_ps(velocities[vidx4].z, velz);
                _mm_store_ps(positions[vidx4].x, posx);
                _mm_store_ps(positions[vidx4].y, posy);
                _mm_store_ps(positions[vidx4].z, posz);
            }
        }
    }

    void symeuler(float dt, std::vector<float4x3a>& positions, std::vector<float4x3a>& velocities, std::vector<float4x3a>& forces, std::vector<float4x4a>& masses) {

        std::atomic<int> counter = 0;
        unsigned int tc = tpool::wd::inittc;

        for (unsigned int i = 0; i < tc; i++) {
            tpool::wd::schedule(psymeuler, std::ref(counter), masses.size(), std::ref(positions), std::ref(velocities), std::ref(forces), std::ref(masses), dt);
        }

        tpool::wd::wait();
    }
}
