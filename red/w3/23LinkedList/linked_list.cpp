#include "test_runner.h"

#include <vector>
using namespace std;

template <class T>
class LinkedList {
public:
    struct Node {
        T value;
        Node *next = nullptr;

        Node(const T &value, Node *next)
            : value(value), next(next) {}
    };
    ~LinkedList() {
        Clear();
    }

    void PushFront(const T &value) {
        if (auto node = new Node(value, head_); node)
            head_ = node;
    }

    void InsertAfter(Node *node, const T &value) {
        if (node) {
            node->next = new Node(value, node->next);
        } else {
            PushFront(value);
        }
    }

    void RemoveAfter(Node *node) {
        if (node) {
            if (auto temp = node->next; temp) {
                node->next = temp->next;
                delete temp;
            }
        } else {
            PopFront();
        }
    }

    void PopFront() {
        if (head_) {
            auto *temp = head_;
            head_ = head_->next;
            delete temp;
        }
    }

    void Clear() {
        if (head_ != nullptr) {
            for (auto *temp = head_; head_->next; temp = head_) {
                head_ = head_->next;
                delete temp;
            }

            delete head_;
            head_ = nullptr;
        }
    }

    Node *GetHead() {
        return head_;
    }
    const Node *GetHead() const {
        return head_;
    }
private:
    Node *head_ = nullptr;
};

template <typename T>
vector<T> ToVector(const LinkedList<T> &list) {
    vector<T> result;
    for (auto node = list.GetHead(); node; node = node->next) {
        result.push_back(node->value);
    }
    return result;
}

void TestPushFront() {
    LinkedList<int> list;

    list.PushFront(1);
    ASSERT_EQUAL(list.GetHead()->value, 1);
    list.PushFront(2);
    ASSERT_EQUAL(list.GetHead()->value, 2);
    list.PushFront(3);
    ASSERT_EQUAL(list.GetHead()->value, 3);

    const vector<int> expected = {3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);
}

void TestInsertAfter() {
    LinkedList<string> list;

    list.PushFront("a");
    auto head_ = list.GetHead();
    ASSERT(head_);
    ASSERT_EQUAL(head_->value, "a");

    list.InsertAfter(head_, "b");
    const vector<string> expected1 = {"a", "b"};
    ASSERT_EQUAL(ToVector(list), expected1);

    list.InsertAfter(head_, "c");
    const vector<string> expected2 = {"a", "c", "b"};
    ASSERT_EQUAL(ToVector(list), expected2);
}

void TestRemoveAfter() {
    LinkedList<int> list;
    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }

    const vector<int> expected = {5, 4, 3, 2, 1};
    ASSERT_EQUAL(ToVector(list), expected);

    auto next_to_head = list.GetHead()->next;
    list.RemoveAfter(next_to_head); // удаляем 3
    list.RemoveAfter(next_to_head); // удаляем 2

    const vector<int> expected1 = {5, 4, 1};
    ASSERT_EQUAL(ToVector(list), expected1);

    while (list.GetHead()->next) {
        list.RemoveAfter(list.GetHead());
    }
    ASSERT_EQUAL(list.GetHead()->value, 5);
}

void TestPopFront() {
    LinkedList<int> list;

    for (int i = 1; i <= 5; ++i) {
        list.PushFront(i);
    }
    for (int i = 1; i <= 5; ++i) {
        list.PopFront();
    }
    ASSERT(list.GetHead() == nullptr);
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestPushFront);
    RUN_TEST(tr, TestInsertAfter);
    RUN_TEST(tr, TestRemoveAfter);
    RUN_TEST(tr, TestPopFront);
    return 0;
}
