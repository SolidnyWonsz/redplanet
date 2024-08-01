#pragma once

#include <debug/assert.h>
#include <sys/defines.h>

namespace LibCPP {
 
template <typename T, size_t N>
class Array {
    public:
        using value_type = T;
        using reference = T&;
        using const_reference = const T&;
        using pointer = T*;
        using const_pointer = const T*;

        pointer data() noexcept {
            return array_data;
        }
        
        const_pointer data() const noexcept {
            return array_data;
        }

        reference at(size_t pos) noexcept {
            ASSERT(pos < N);    // I don't have C++ exceptions implemented right now so that's all
                                // I can do. Make sure not to access index higher than possible.
                                // Same applies to function below.
            return array_data[pos];
        }
        
        const_reference at(size_t pos) const noexcept {
            ASSERT(pos < N);
            return array_data[pos];
        }
        
        reference operator[](size_t pos) {
            return array_data[pos];
        }

        const_reference operator[](size_t pos) const {
            return array_data[pos];
        }

        reference operator=(const T(&data)[N]) {
            for (size_t i = 0; i < N; ++i) {
                array_data[i] = data[i];
            }
            return *this;
        }

        reference front() const {
            return at(0);
        }
        
        const_reference front() {
            return at(0);
        }

        reference back() const {
            return at(N - 1);
        }

        const_reference back() {
            return at(N - 1);
        }

        size_t size() const {
            return N;
        }

        bool empty() const {
            if (size() == 0) return true;
            else return false;
        }

    private:
        T array_data[N];
};

}