#pragma once

#include <algorithm>
#include <iostream>
using namespace std;

template <class T>
class SimpleVector {
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *ptr_ = nullptr;
    T *end_ = nullptr;
public:
    SimpleVector() = default;

    explicit SimpleVector(size_t size)
        : size_(size), capacity_(size) {
        ptr_ = new T[size];
        end_ = ptr_ + size;
    }

    SimpleVector(const SimpleVector &sv)
        : size_(sv.size_), capacity_(sv.capacity_) {
        ptr_ = new T[capacity_];
        end_ = ptr_ + size_;
        copy(sv.begin(), sv.end(), begin());
    }

    SimpleVector &operator=(const SimpleVector &sv) {
        if (sv.size_ <= capacity_) {
            copy(sv.begin(), sv.end(), begin());
            size_ = sv.size_;
            end_ = sv.end_;
        } else {
            SimpleVector tmp(sv);
            swap(tmp.ptr_, ptr_);
            swap(tmp.end_, end_);
            swap(tmp.size_, size_);
            swap(tmp.capacity_, capacity_);
        }
        return *this;
    }

    ~SimpleVector() {
        delete[] ptr_;
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

        delete[] ptr_;
        ptr_ = copy;
        end_ = ptr_ + size_;
    }
};
