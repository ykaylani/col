#include "dynintegrators.h"
#include <vector>
#include <thread>
#include <atomic>
#include "../data/ct.h"

#include <immintrin.h>
#include <stdexcept>

namespace dintegrators { //Assumption: scalar types contain 4 times the number of particles compared to 4D vector types

    void symeuleri(float dt, float4x4a& positions, float4x4a& velocities, float4x4a& forces, float4x4a& masses, int quarter) {

        __m128 velx = _mm_load_ps(velocities.x);
        __m128 vely = _mm_load_ps(velocities.y);
        __m128 velz = _mm_load_ps(velocities.z);

        __m128 forx = _mm_load_ps(forces.x);
        __m128 fory = _mm_load_ps(forces.y);
        __m128 forz = _mm_load_ps(forces.z);

        __m128 posx = _mm_load_ps(positions.x);
        __m128 posy = _mm_load_ps(positions.y);
        __m128 posz = _mm_load_ps(positions.z);

        __m128 mass;

        __m128 dts = _mm_load1_ps(&dt);

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
                throw std::runtime_error("SymeulerI: Quarter out-of-bounds");
        }

        __m128 ratio = _mm_div_ps(dts, mass);

        velx = _mm_add_ps(velx, _mm_mul_ps(forx, ratio));
        vely = _mm_add_ps(vely, _mm_mul_ps(fory, ratio));
        velz = _mm_add_ps(velz, _mm_mul_ps(forz, ratio));

        posx = _mm_add_ps(posx, _mm_mul_ps(velx, dts));
        posy = _mm_add_ps(posy, _mm_mul_ps(vely, dts));
        posz = _mm_add_ps(posz, _mm_mul_ps(velz, dts));

        _mm_store_ps(velocities.x, velx);
        _mm_store_ps(velocities.y, vely);
        _mm_store_ps(velocities.z, velz);

        _mm_store_ps(positions.x, posx);
        _mm_store_ps(positions.y, posy);
        _mm_store_ps(positions.z, posz);
    }

    void psymeuler(std::atomic<int>& unprocessedblock, int tblocks, std::vector<float4x4a>& positions, std::vector<float4x4a>& velocities, std::vector<float4x4a>& forces, std::vector<float4x4a>& masses, float dt) {

        while (true) {
            int scheduleindex = unprocessedblock.fetch_add(1);
            if (scheduleindex >= tblocks) break;

            int vectoridx = scheduleindex * 4;

            for (int i = 0; i < 4; i++) {
                int pidx = vectoridx + i;
                if (pidx >= positions.size()) break;

                float4x4a& positionblock = positions[pidx];
                float4x4a& velocitiesblock = velocities[pidx];
                float4x4a& forcesblock = forces[pidx];

                symeuleri(dt, positionblock, velocitiesblock, forcesblock, masses[scheduleindex], i);
            }
        }
    }

    void symeuler(float dt, std::vector<float4x4a>& positions, std::vector<float4x4a>& velocities, std::vector<float4x4a>& forces, std::vector<float4x4a>& masses) {

        std::atomic<int> counter = 0;
        std::vector<std::thread> threads;
        unsigned n = std::thread::hardware_concurrency();
        threads.reserve(n);

        for (int i = 0; i < n; i++) {
            threads.emplace_back(psymeuler, std::ref(counter), masses.size(), std::ref(positions), std::ref(velocities), std::ref(forces), std::ref(masses), dt);
        }

        for (int i = 0; i < n; i++) {
            threads[i].join();
        }
    }
}
