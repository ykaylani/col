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
            std::vector<std::chrono::high_resolution_clock> clocks;
    };
}


#endif //COL_CLOCKS_H