#ifndef COL_TIME_H
#define COL_TIME_H
#include <chrono>
#include <functional>

namespace sclock {

    class nano {
        public:

            std::vector<std::chrono::steady_clock> clocks;
            static void nano::sync(float pongrate, std::function<void()>& pinger);
    };

}

#endif COL_TIME_H