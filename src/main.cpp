#include <chrono>
#include <iostream>
#include <thread>
#include "../src/data/ct.h"
#include "../src/data/scn/dstore.h"
#include "../src/lib/bsys/wd.h"
#include "lib/dglobal/integrators.h"

int main() {

    float dt = 0.02f;
    std::chrono::time_point inittime = std::chrono::steady_clock::now();

    dynamics::dstore dynobj;
    tpool::wd threading;

    threading.init(std::thread::hardware_concurrency());

    dynobj.force.reserve(256);
    dynobj.pos.reserve(256);
    dynobj.velocity.reserve(256);
    dynobj.mass.reserve(64);

    for (int i = 0; i < 256; i++) {
        dynobj.force.emplace_back();
        dynobj.pos.emplace_back();
        dynobj.velocity.emplace_back();

        for (int j = 0; j < 4; j++) {
            dynobj.force[i].x[j] = 0;
            dynobj.force[i].y[j] = 0;
            dynobj.force[i].z[j] = 0;
            dynobj.velocity[i].x[j] = 0;
            dynobj.velocity[i].y[j] = 0;
            dynobj.velocity[i].z[j] = 0;
            dynobj.pos[i].x[j] = 0;
            dynobj.pos[i].y[j] = 0;
            dynobj.pos[i].z[j] = 0;
        }
    }

    for (int i = 0; i < 64; i++) {
        dynobj.mass.emplace_back();

        for (int j = 0; j < 4; j++) {
            dynobj.mass[i].x[j] = 10;
            dynobj.mass[i].y[j] = 10;
            dynobj.mass[i].z[j] = 10;
            dynobj.mass[i].w[j] = 10;
        }
    }

    int step = 0;

    while (true) {

        if (step == 1024) { break; }

        dintegrators::symeuler(dt, dynobj.pos, dynobj.velocity, dynobj.force, dynobj.mass, threading);

        std::cout << "dintegrators::symeuler" << " " << step << " " << dt << std::endl;
        std::cout << dynobj.pos[0].y[0] << std::endl;
        step++;
    }

    return 0;
};