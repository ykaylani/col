#ifndef COL_RSORT_H
#define COL_RSORT_H
#include <vector>
#include <array>
#include "../bsys/wd.h"
#include "../bsys/aalloc.h"


namespace rsort {

    inline std::vector<std::array<uint32_t, 256>, aalloc<std::array<uint32_t, 256>, 64>> radices;
    inline std::vector<std::array<uint32_t, 256>, aalloc<std::array<uint32_t, 256>, 64>> istarts;

    static void lhist(std::vector<uint32_t>& __restrict values, int tid, int start, int end, int pass) {

        for (int i = start; i < end; i++) {

            int bits = pass * 8;
            uint8_t digit = (values[i] >> bits) & 0xFF;

            radices[tid][digit] += 1;
        }
    }

    static void starts(int tid) {
        std::array<uint32_t, 256>& start = istarts[tid];
        std::array<uint32_t, 256>& psum = radices.back();

        for (int i = 0; i < start.size(); i++) {
            start[i] = psum[i];

            for (int j = 0; j < tid; j++) {
                start[i] += radices[j][i];
            }
        }
    }

    static void psum() {
        std::array<uint32_t, 256>& gc = radices[radices.size() - 2];
        std::array<uint32_t, 256>& psum = radices.back();

        gc.fill(0);

        for (int i = 0; i < radices.size() - 2; i++) {
            for (int j = 0; j < 256; j++) {

                gc[j] += radices[i][j];
            }
        }

        uint32_t sum = 0;

        for (int i = 0; i < 256; i++) {

            psum[i] = sum;
            sum += gc[i];
        }
    }

    static void gscatter(std::vector<uint32_t>& __restrict values1, int start, int end, int pass, std::vector<uint32_t>& __restrict values2, int tid) {

        std::array<uint32_t, 256>& rstart = istarts[tid];

        for (int i = start; i < end; i++) {
            uint32_t input = values1[i];

            int bits = pass * 8;
            uint8_t digit = (values1[i] >> bits) & 255;

            size_t pos = rstart[digit]++;
            values2[pos] = input;
        }
    }

    static void process2(std::vector<uint32_t>& __restrict values, int start, int end, int pass, int tid, std::vector<uint32_t>& __restrict values2) {
        starts(tid);
        gscatter(values, start, end, pass, values2, tid);
    }

    static void sort(std::vector<uint32_t>& __restrict values, tpool::wd& __restrict pool, std::vector<uint32_t>& __restrict values2, bool ping) {

        unsigned int tc = pool.inittc;
        unsigned int len = values.size();

        if (tc > len) tc = len;

        if (istarts.size() != tc) {

            radices.resize(tc + 2); //prefix sum is + 2, global is +1
            istarts.resize(tc);
        }

        for (int pass = 1; pass <= 4; pass++) {
            for (int tid = 0; tid < tc; tid++) {

                int chunk = len / tc;
                int start = chunk * tid;
                int end = (tid == tc - 1) ? len : start + chunk;

                if (ping) {

                    pool.schedule(lhist, std::ref(values), tid, start, end, i);
                } else {

                    pool.schedule(lhist, std::ref(values2), tid, start, end, i);
                }
            }

            pool.wait();
            psum();

            for (int tid = 0; tid < tc; tid++) {

                int chunk = len / tc;
                int start = chunk * tid;
                int end = (tid == tc - 1) ? len : start + chunk;

                if (ping) {

                    pool.schedule(process2, std::ref(values), start, end, pass, tid, std::ref(values2));
                } else {

                    pool.schedule(process2, std::ref(values2), start, end, pass, tid, std::ref(values));
                }
            }

            pool.wait();

            ping = !ping;
        }
    }
}

#endif //COL_RSORT_H