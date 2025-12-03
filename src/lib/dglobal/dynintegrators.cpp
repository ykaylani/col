#include <vector>
#include <immintrin.h>
#include <thread>
#include <atomic>
#include <cassert>
#include "dynintegrators.h"
#include "../../data/ct.h"
#include "../dforce/wspace.h"
#include "../bsys/wd.h"


namespace dintegrators { //Assumption: scalar types contain 4 times the number of particles compared to 4D vector types

    const int callgranularity = 1;

    void symeuleri(__m128& __restrict dt, float4x4a& __restrict positions, float4x4a& __restrict velocities, float4x4a& __restrict forces, float4x4a& __restrict masses, int quarter) {

        __m128 velx = _mm_load_ps(velocities.x);
        __m128 vely = _mm_load_ps(velocities.y);
        __m128 velz = _mm_load_ps(velocities.z);

        wsforces::g::apply(forces, wsforces::gmag);

        __m128 forx = _mm_load_ps(forces.x);
        __m128 fory = _mm_load_ps(forces.y);
        __m128 forz = _mm_load_ps(forces.z);

        __m128 posx = _mm_load_ps(positions.x);
        __m128 posy = _mm_load_ps(positions.y);
        __m128 posz = _mm_load_ps(positions.z);

        __m128 mass;

        switch (quarter) {
            case 0:
                mass = _mm_load_ps(masses.x);
                break;
            case 1:
                mass = _mm_load_ps(masses.y);
                break;
            case 2:
                mass = _mm_load_ps(masses.z);
                break;
            case 3:
                mass = _mm_load_ps(masses.w);
                break;
            default:
                assert(quarter >= 0 && quarter < 4 && "Quarter out of bounds");
        }

        __m128 ratio = _mm_div_ps(dt, mass);

        velx = _mm_add_ps(velx, _mm_mul_ps(forx, ratio));
        vely = _mm_add_ps(vely, _mm_mul_ps(fory, ratio));
        velz = _mm_add_ps(velz, _mm_mul_ps(forz, ratio));

        posx = _mm_add_ps(posx, _mm_mul_ps(velx, dt));
        posy = _mm_add_ps(posy, _mm_mul_ps(vely, dt));
        posz = _mm_add_ps(posz, _mm_mul_ps(velz, dt));

        _mm_store_ps(velocities.x, velx);
        _mm_store_ps(velocities.y, vely);
        _mm_store_ps(velocities.z, velz);

        _mm_store_ps(positions.x, posx);
        _mm_store_ps(positions.y, posy);
        _mm_store_ps(positions.z, posz);
    }

    void psymeuler(std::atomic<int>& unprocessedblock, int tblocks, std::vector<float4x4a>& positions, std::vector<float4x4a>& velocities, std::vector<float4x4a>& forces, std::vector<float4x4a>& masses, float dt) {

        while (true) {
            int scheduleindex = unprocessedblock.fetch_add(callgranularity);
            if (scheduleindex >= tblocks) { return; }

            __m128 dts = _mm_load1_ps(&dt);

            for (int i = 0; i < callgranularity && scheduleindex + i < tblocks; i++) {

                int vectoridx = (scheduleindex + i) * 4;

                for (int j = 0; j < 4; j++) {
                    int pidx = vectoridx + j;
                    if (pidx >= positions.size()) break;

                    float4x4a& positionblock = positions[pidx];
                    float4x4a& velocitiesblock = velocities[pidx];
                    float4x4a& forcesblock = forces[pidx];

                    symeuleri(dts, positionblock, velocitiesblock, forcesblock, masses[scheduleindex + i], j);
                }
            }
        }
    }

    void symeuler(float dt, std::vector<float4x4a>& positions, std::vector<float4x4a>& velocities, std::vector<float4x4a>& forces, std::vector<float4x4a>& masses) {

        std::atomic<int> counter = 0;
        tpool::wd::schedule(psymeuler, std::ref(counter), masses.size(), std::ref(positions), std::ref(velocities), std::ref(forces), std::ref(masses), dt);
    }
}
