#include <cstdint>
#include <algorithm>
using namespace std;

template <typename T>
class SimpleVector {
    size_t size_ = 0;
    size_t capacity_ = 0;
    T *ptr_ = nullptr;
public:
    SimpleVector() = default;
    explicit SimpleVector(size_t size)
        : size_(size)
        , capacity_(size) {
        ptr_ = new T[size];
    }

    SimpleVector(const SimpleVector &sv)
        : size_(sv.size_), capacity_(sv.capacity_) {
        ptr_ = new T[capacity_];
        copy(sv.begin(), sv.end(), begin());
    }

    SimpleVector(SimpleVector &&sv)
        : size_(sv.size_), capacity_(sv.capacity_) {
        ptr_ = sv.ptr_;
        sv.ptr_ = nullptr;
    }

    SimpleVector &operator=(const SimpleVector &sv) {
        if (sv.size_ <= capacity_) {
            copy(sv.begin(), sv.end(), begin());
            size_ = sv.size_;
        } else {
            SimpleVector tmp(sv);
            swap(tmp.ptr_, ptr_);
            swap(tmp.size_, size_);
            swap(tmp.capacity_, capacity_);
        }
        return *this;
    }
    SimpleVector &operator=(SimpleVector &&sv) {
        delete[] ptr_;
        ptr_ = sv.ptr_, size_ = sv.size_, capacity_ = sv.capacity_;
        sv.ptr_ = nullptr, sv.size_ = sv.capacity_ = 0;
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
        return ptr_ + size_;
    }
    const T *begin() const {
        return ptr_;
    }
    const T *end() const {
        return ptr_ + size_;
    }
    size_t Size() const {
        return size_;
    }
    size_t Capacity() const {
        return capacity_;
    }

    void PushBack(T value) {
        if (size_ == capacity_)
            reallocate();

        ptr_[size_] = move(value);
        ++size_;
    }
private:
    void reallocate() {
        capacity_ = capacity_ ? capacity_ * 2 : 1;
        T *temp = new T[capacity_];
        move(begin(), end(), temp);

        delete[] ptr_;
        ptr_ = temp;
    }
};
