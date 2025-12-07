#include <chrono>
#include <iostream>
#include <thread>
#include "../data/ct.h"
#include "../data/scn/dstore.h"
#include "bsys/wd.h"
#include "dglobal/integrators.h"

void testsimloop(uint32_t particlecount, float dt, uint32_t stepcount) {

    std::cout << "Particle count: " << particlecount << " // dt: " << dt << " // stepcount: " << stepcount << std::endl;

    std::chrono::time_point<std::chrono::steady_clock> astart = std::chrono::steady_clock::now();

    dynamics::dstore dynobj;
    tpool::wd threading;

    threading.init(std::thread::hardware_concurrency());

    int vectoridx = particlecount / 8;
    int scalaridx = particlecount / 32;

    dynobj.pos.reserve(vectoridx);
    dynobj.velocity.reserve(vectoridx);
    dynobj.mass.reserve(scalaridx);

    for (int i = 0; i < vectoridx; i++) {
        dynobj.pos.emplace_back();
        dynobj.velocity.emplace_back();

        for (int j = 0; j < 8; j++) {
            dynobj.velocity[i].x[j] = 0;
            dynobj.velocity[i].y[j] = 0;
            dynobj.velocity[i].z[j] = 0;
            dynobj.pos[i].x[j] = 0;
            dynobj.pos[i].y[j] = 0;
            dynobj.pos[i].z[j] = 0;
        }
    }

    for (int i = 0; i < scalaridx; i++) {
        dynobj.mass.emplace_back();

        for (int j = 0; j < 8; j++) {
            dynobj.mass[i].x[j] = 1.0 / 10.0;
            dynobj.mass[i].y[j] = 1.0 / 10.0;
            dynobj.mass[i].z[j] = 1.0 / 10.0;
            dynobj.mass[i].w[j] = 1.0 / 10.0;
        }
    }

    int step = 0;
    std::chrono::time_point<std::chrono::steady_clock> astartainit = std::chrono::steady_clock::now();

    while (true) {

        if (step == stepcount) { break; }

        dintegrators::symeuler(dt, dynobj.pos, dynobj.velocity, dynobj.mass, threading);
        step++;
    }

    std::chrono::steady_clock::time_point aend = std::chrono::steady_clock::now();
    float d = std::chrono::duration_cast<std::chrono::nanoseconds>(aend - astart).count();
    float d2 = std::chrono::duration_cast<std::chrono::nanoseconds>(aend - astartainit).count();

    std::cout << "Duration w/ Initialization: " << d << " ns" << std::endl;
    std::cout << "Duration w/o Initialization: " << d2 << " ns" << std::endl;
    std::cout << "P1 Y-axis: " << dynobj.pos[0].y[0] << std::endl;

    std::cout << "Press Enter to continue...";
    std::cin.get();
    std::cout << std::endl;
}

int main() {

    int pc = 2;
    int iterations = 25;

    for (int i = 5; i < iterations + 5; i++) {

        testsimloop(pow(pc, i), 0.02, 1024);
    }

    return 0;
};