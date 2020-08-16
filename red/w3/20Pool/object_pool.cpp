#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <stdexcept>
#include <string>
using namespace std;

template <class T>
class ObjectPool {
    set<T*> alloced;
    queue<T*> sleeped;
public:
    ~ObjectPool() {
        while (!sleeped.empty()) {
            delete sleeped.front();
            sleeped.pop();
        }
        for (auto &i : alloced)
            delete i;
    }

    T *Allocate() {
        if (sleeped.empty())
            return *alloced.insert(new T).first;
        return Replace();
    }
    T *TryAllocate() {
        if (sleeped.empty())
            return nullptr;
        return Replace();
    }
    void Deallocate(T *object) {
        if (auto t = alloced.find(object); t != alloced.end()) {
            sleeped.push(alloced.extract(t).value());
        } else {
            throw invalid_argument("wrong argument");
        }
    }
private:
    T *Replace() {
        auto it = alloced.insert(sleeped.front()).first;
        sleeped.pop();
        return *it;
    }
};

void TestObjectPool() {
    ObjectPool<string> pool;

    auto p1 = pool.Allocate();
    auto p2 = pool.Allocate();
    auto p3 = pool.Allocate();

    *p1 = "first";
    *p2 = "second";
    *p3 = "third";

    pool.Deallocate(p2);
    ASSERT_EQUAL(*pool.Allocate(), "second");

    pool.Deallocate(p3);
    pool.Deallocate(p1);
    ASSERT_EQUAL(*pool.Allocate(), "third");
    ASSERT_EQUAL(*pool.Allocate(), "first");

    pool.Deallocate(p1);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestObjectPool);
}
