#include <iostream>
#include "lib/sglobal/time.h"

float fixedstep = 20.0f; //in microseconds

void init() {
    Nanoclock clock;
    clock.Start();

    std::cout << clock.Wall() << std::endl;
}


int main() {
    init();
}
