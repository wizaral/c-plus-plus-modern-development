#pragma once

#include <cstdlib>
#include <cstring>

template <class T>
class SimpleVector {
    T* ptr_ = nullptr;
    T* end_ = nullptr;
    size_t size_ = 0;
    size_t capacity_ = 0;
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size) {
        ptr_ = new T[size];
        end_ = ptr_ + size;
        capacity_ = size_ = size;
    }
    ~SimpleVector() {
        delete []ptr_;
    }

    T &operator[](size_t index) {
        return ptr_[index];
    }
    const T &operator[](size_t index) const {
        return ptr_[index];
    }

    T *begin() {
        return ptr_;
    }
    T *end() {
        return end_;
    }

    const T *begin() const {
        return ptr_;
    }
    const T *end() const {
        return end_;
    }

    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(const T &value) {
        if (size_ == capacity_)
            reallocate();

        ptr_[size_] = value;
        ++size_;
        ++end_;
    }
private:
    void reallocate() {
        capacity_ = capacity_ ? capacity_ * 2 : 1;
        T *copy = new T[capacity_];

        for (size_t i = 0; i < size_; ++i)
            copy[i] = ptr_[i];

        delete []ptr_;
        ptr_ = copy;
        end_ = ptr_ + size_;
    }
};
