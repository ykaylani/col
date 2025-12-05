#include <chrono>
#include <iostream>
#include <thread>
#include "../src/data/ct.h"
#include "../src/data/scn/dstore.h"
#include "../src/lib/bsys/wd.h"
#include "lib/dglobal/integrators.h"

int main() {

    float dt = 0;
    std::chrono::time_point inittime = std::chrono::steady_clock::now();

    dynamics::dstore dynobj;
    tpool::wd threading;


    threading.init(std::thread::hardware_concurrency());

    dynobj.force.reserve(4);
    dynobj.pos.reserve(4);
    dynobj.velocity.reserve(4);
    dynobj.mass.reserve(1);

    for (int i = 0; i < 4; i++) {
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

    dynobj.mass.emplace_back();

    for (int i = 0; i < 4; i++) {
        dynobj.mass[0].x[i] = 10;
        dynobj.mass[0].y[i] = 10;
        dynobj.mass[0].z[i] = 10;
        dynobj.mass[0].w[i] = 10;
    }

    int step = 0;

    while (true) {

        if (step == 1000) { return 0; }

        std::chrono::time_point frametime = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = frametime - inittime;
        dt = elapsed.count();
        inittime = frametime;

        dintegrators::symeuler(dt, dynobj.pos, dynobj.velocity, dynobj.force, dynobj.mass, threading);
        std::cout << "dintegrators::symeuler" << step << std::endl;
        step++;
    }
    return 0;
};