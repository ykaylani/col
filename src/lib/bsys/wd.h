#ifndef COL_WD_H
#define COL_WD_H

#include <functional>
#include <mutex>
#include <queue>
#include <vector>
#include <thread>
#include <atomic>
#include <condition_variable>

namespace tpool {

    class wd {
        public:
            void init(unsigned int tc);
            void shut();
            void wait();
        
            template<typename Func, typename... Args>
            void schedule(Func&& function, Args&&... args) {
                std::lock_guard<std::mutex> lock(qmtx);
                queue.push( [function = std::forward<Func>(function), tuple = std::make_tuple(std::forward<Args>(args)...)] {std::apply(function, tuple);} );
                qcv.notify_one();
            }

            unsigned int inittc;
            ~wd() { if (!close.load()) shut(); }

        private:
            void await();

            std::vector<std::thread> threads;
            std::queue<std::function<void()>> queue;

            std::mutex qmtx;
            std::condition_variable qcv;
            std::atomic<bool> close = false;
            std::atomic<int> atasks{0};
    };
}

#endif //COL_WD_H