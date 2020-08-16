#pragma once

#include <stdexcept>
using namespace std;

#if 0

template <typename T, size_t N>
class StackVector {
    T arr[N];
    size_t size_;
public:
    explicit StackVector(size_t size = 0) : size_(size) {
        if (size > N)
            throw invalid_argument("");
    }

    T &operator[](size_t index) {
        return arr[index];
    }
    const T &operator[](size_t index) const {
        return arr[index];
    }

    auto begin() {
        return arr;
    }
    auto end() {
        return arr + size_;
    }
    const auto begin() const {
        return arr;
    }
    const auto end() const {
        return arr + size_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T &value) {
        if (size_ < N) {
            arr[size_] = value;
            ++size_;
        } else {
            throw overflow_error("");
        }
    }
    T PopBack() {
        if (size_ > 0) {
            --size_;
            return arr[size_];
        } else {
            throw underflow_error("");
        }
    }
};

#else

#include <array>

template <typename T, size_t N>
class StackVector {
    array<T, N> arr;
    size_t size_;
public:
    explicit StackVector(size_t size = 0) : size_(size) {
        if (size > N)
            throw invalid_argument("");
    }

    T &operator[](size_t index) {
        return arr[index];
    }
    const T &operator[](size_t index) const {
        return arr[index];
    }

    auto begin() {
        return arr.data();
    }
    auto end() {
        return arr.data() + size_;
    }
    const auto begin() const {
        return arr.data();
    }
    const auto end() const {
        return arr.data() + size_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return N;
    }

    void PushBack(const T &value) {
        if (size_ < N) {
            arr[size_] = value;
            ++size_;
        } else {
            throw overflow_error("");
        }
    }
    T PopBack() {
        if (size_ > 0) {
            --size_;
            return arr[size_];
        } else {
            throw underflow_error("");
        }
    }
};

#endif
