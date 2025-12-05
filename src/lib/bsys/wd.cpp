#include "wd.h"

#include <functional>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <cassert>

namespace tpool {

    void wd::await() {

        while (true) {
            std::function<void()> function;
            {
                std::unique_lock<std::mutex> lock(qmtx);
                qcv.wait(lock, []{ return !queue.empty() || close; });

                if (close) return;

                if (!queue.empty()) {

                    function = queue.front();
                    queue.pop();
                    atasks++;
                }
            }

            if (function) {

                try {function(); } catch (...) {}
                atasks--;
            }
        }
    }

    void wd::init(unsigned int tc) {

        if (!threads.empty()) assert("Double-Initialization of thread pool");

        unsigned int tcm = std::min(tc, std::thread::hardware_concurrency());
        threads.reserve(tcm);

        for (unsigned int i = 0; i < tcm; i++) {
            threads.emplace_back(&wd::await);
        }

        inittc = tcm;
    }

    void wd::wait() {
        std::unique_lock<std::mutex> lock(qmtx);
        qcv.wait(lock, []{ return queue.empty() && atasks == 0; });
    }

    void wd::shut() {
        {
            std::lock_guard<std::mutex> lock(qmtx);
            close.store(true);
        }

        qcv.notify_all();

        for (int i = 0; i < threads.size(); i++) {
            threads[i].join();
        }
    }



};