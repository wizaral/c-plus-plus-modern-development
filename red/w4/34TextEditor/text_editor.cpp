#include "test_runner.h"
#include <list>
#include <string>
using namespace std;

class Editor {
    list<char> text;
    list<char>::iterator pos = text.begin();
    list<char> buffer;
public:
    Editor() = default;

    void Left() {
        if (pos != text.begin())
            --pos;
    }
    void Right() {
        if (pos != text.end())
            ++pos;
    }

    void Insert(char token) {
        text.insert(pos, token);
    }

    void Cut(size_t tokens = 1) {
        auto end = get_pos(tokens);
        buffer.clear();

        buffer.splice(buffer.begin(), text, pos, end);
        pos = end;
    }
    void Copy(size_t tokens = 1) {
        buffer.assign(pos, get_pos(tokens));
    }
    void Paste() {
        text.insert(pos, buffer.begin(), buffer.end());
    }

    string GetText() const {
        return {text.begin(), text.end()};
    }
private:
    list<char>::iterator get_pos(size_t tokens) {
        auto pos_ = pos;
        for (size_t i = 0; i < tokens && pos_ != text.end(); ++i)
            ++pos_;
        return pos_;
    }
};

void TypeText(Editor &editor, const string &text) {
    for (char c : text) {
        editor.Insert(c);
    }
}

void TestEditing() {
    {
        Editor editor;

        const size_t text_len = 12;
        const size_t first_part_len = 7;
        TypeText(editor, "hello, world");
        for (size_t i = 0; i < text_len; ++i) {
            editor.Left();
        }
        editor.Cut(first_part_len);
        for (size_t i = 0; i < text_len - first_part_len; ++i) {
            editor.Right();
        }
        TypeText(editor, ", ");
        editor.Paste();
        editor.Left();
        editor.Left();
        editor.Cut(3);

        ASSERT_EQUAL(editor.GetText(), "world, hello");
    }
    {
        Editor editor;

        TypeText(editor, "misprnit");
        editor.Left();
        editor.Left();
        editor.Left();
        editor.Cut(1);
        editor.Right();
        editor.Paste();

        ASSERT_EQUAL(editor.GetText(), "misprint");
    }
}

void TestReverse() {
    Editor editor;

    const string text = "esreveR";
    for (char c : text) {
        editor.Insert(c);
        editor.Left();
    }

    ASSERT_EQUAL(editor.GetText(), "Reverse");
}

void TestNoText() {
    Editor editor;
    ASSERT_EQUAL(editor.GetText(), "");

    editor.Left();
    editor.Left();
    editor.Right();
    editor.Right();
    editor.Copy(0);
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "");
}

void TestEmptyBuffer() {
    Editor editor;

    editor.Paste();
    TypeText(editor, "example");
    editor.Left();
    editor.Left();
    editor.Paste();
    editor.Right();
    editor.Paste();
    editor.Copy(0);
    editor.Paste();
    editor.Left();
    editor.Cut(0);
    editor.Paste();

    ASSERT_EQUAL(editor.GetText(), "example");
}

void TestCut() {
    Editor editor;

    editor.Cut(10);
    editor.Insert('a');
    editor.Left();

    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");

    editor.Cut(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "a");
    TypeText(editor, "bcde");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();

    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcde");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();

    editor.Cut(5);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();

    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bcde");
    editor.Right();
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "bde");
    editor.Cut(1);
    editor.Cut(1);
    ASSERT_EQUAL(editor.GetText(), "b");
}

void TestCopy() {
    Editor editor;

    editor.Copy(10);
    editor.Insert('a');
    editor.Paste();
    editor.Left();
    ASSERT_EQUAL(editor.GetText(), "a");

    editor.Copy(1);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa"); //between a

    editor.Copy(0);
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "aa");
    TypeText(editor, "bcde");
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();
    editor.Left();

    editor.Cut(10);
    ASSERT_EQUAL(editor.GetText(), "");
    editor.Paste();
    ASSERT_EQUAL(editor.GetText(), "abcdea");
}

int main() {
    TestRunner tr;
    RUN_TEST(tr, TestEditing);
    RUN_TEST(tr, TestReverse);
    RUN_TEST(tr, TestNoText);
    RUN_TEST(tr, TestEmptyBuffer);
    RUN_TEST(tr, TestCut);
    RUN_TEST(tr, TestCopy);
}
