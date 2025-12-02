#ifndef COL_TIME_H
#define COL_TIME_H
#include <chrono>

class Nanoclock {
    private:
        std::chrono::time_point<std::chrono::high_resolution_clock> stime;
    public:
        void Start() {
            stime = std::chrono::high_resolution_clock::now();
        }

        long long Wall() {
            std::chrono::time_point<std::chrono::high_resolution_clock> now = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::nanoseconds>(now - stime).count();
        }
};

#endif COL_TIME_H