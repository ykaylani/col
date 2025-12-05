#ifndef COL_AALLOC_H
#define COL_AALLOC_H
#include <memory>

#if defined(_WIN32) || defined(_WIN64)
    #include <malloc.h>
    #define COL_ALIGNED_ALLOC(alignment, size) _aligned_malloc(size, alignment)
    #define COL_ALIGNED_FREE(ptr) _aligned_free(ptr)
#elif defined(__linux__) || defined(__APPLE__)
    #define COL_ALIGNED_ALLOC(alignment, size) aligned_alloc(alignment, ((size + alignment - 1) / alignment) * alignment)
    #define COL_ALIGNED_FREE(ptr) std::free(ptr)
#endif

template<typename T, std::size_t Alignment>
class aalloc {
public:
    using value_type = T;
    using size_type = std::size_t;
    using pointer = T*;

    using is_always_equal = std::true_type;
    aalloc() noexcept = default;

    template<typename U>
    aalloc(const aalloc<U, Alignment>&) noexcept {}

    template<typename U>
    struct rebind { using other = aalloc<U, Alignment>; };

    pointer allocate(size_type n) {
        if (n == 0) return nullptr;

        void* ptr = COL_ALIGNED_ALLOC(Alignment, n * sizeof(T));
        if (!ptr) throw std::bad_alloc();
        return static_cast<pointer>(ptr);
    }

    void deallocate(pointer p, size_type) {
        COL_ALIGNED_FREE(p);
    }

    bool operator==(const aalloc&) const noexcept { return true; }
    bool operator!=(const aalloc&) const noexcept { return false; }
};

#endif //COL_AALLOC_H