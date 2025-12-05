#ifndef COL_CLOCKS_H
#define COL_CLOCKS_H
#include <vector>
#include <chrono>

namespace clocks{

    class clock{
        public:
            void init();
            void dispose();
            void sync();
        
        private:
            inline static std::chrono::steady_clock internal;
    };
}


#endif //COL_CLOCKS_H