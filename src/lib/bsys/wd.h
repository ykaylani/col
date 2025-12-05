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
            static void init(unsigned int tc);
            static void shut();
            static void wait();
        
            template<typename Func, typename... Args>
            static void schedule(Func&& function, Args&&... args) {
                std::lock_guard<std::mutex> lock(qmtx);
                queue.push( [func = std::forward<Func>(function), tup = std::make_tuple(std::forward<Args>(args)...)]() mutable {std::apply(func, std::move(tup));} );
                qcv.notify_one();
            }

            static unsigned int inittc;

        private:
            static void await();

            inline static std::vector<std::thread> threads;
            inline static std::queue<std::function<void()>> queue;

            inline static std::mutex qmtx;
            inline static std::condition_variable qcv;
            inline static std::atomic<bool> close = false;

            inline static std::atomic<int> atasks{0};
    };
}

#endif //COL_WD_H