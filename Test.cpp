#include "doctest.h"
#include "Notebook.hpp"
#include <climits>
using namespace ariel;
using namespace std;

Direction horizontal = Direction::Horizontal;
Direction vertical = Direction::Vertical;

TEST_CASE("GOOD")
{
    Notebook notebook;
    notebook.write(0, 0, 0, horizontal, "abcde");
    notebook.write(1, 0, 0, vertical, "abcdefghij");
    CHECK(notebook.read(0, 0, 0, horizontal, 5) == "abcde");
    CHECK(notebook.read(1, 0, 0, vertical, 10) == "abcdefghij");
    CHECK(notebook.read(12, 57, 25, horizontal, 5) == "_____");
    CHECK(notebook.read(35, 32, 48, vertical, 10) == "__________");
}

TEST_CASE("NORMAL TESTS")
{
    Notebook notebook;
    string a = string("ABCDE");
    string b = string("0123456789");
    string c = string("ASDFGHJK");
    string d = string("ZXCVBNM<");
    string e = string("QWERTYUIOP");
    string f = string("QAZWSXEDC");
    string g = string("!@#$%^&*()_+");
    string empty12 = string("____________");

    // random locations
    notebook.write(50, 50, 50, horizontal, a);
    CHECK(notebook.read(50, 50, 50, horizontal, a.size()) == a);
    notebook.write(80, 80, 80, vertical, b);
    CHECK(notebook.read(80, 80, 80, vertical, b.size()) == b);

    // edge locations
    notebook.write(1, 0, 0, horizontal, c);
    CHECK(notebook.read(1, 0, 0, horizontal, c.size()) == c);
    notebook.write(2, 0, 0, vertical, d);
    CHECK(notebook.read(2, 0, 0, vertical, d.size()) == d);

    notebook.write(3, INT_MAX, INT_MAX - e.size(), horizontal, e);
    CHECK(notebook.read(3, INT_MAX, INT_MAX - e.size(), horizontal, e.size()) == e);
    notebook.write(4, INT_MAX - f.size(), INT_MAX, vertical, f);
    CHECK(notebook.read(4, INT_MAX - f.size(), INT_MAX, vertical, f.size()) == f);

}

TEST_CASE("Invalid page, row, column index"){
    Notebook notebook;
    //write
    CHECK_THROWS(notebook.write(-10, 10, 10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(10, -10, 10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(10, 10, -10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(-10, -10, 10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(10, -10, -10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(-10, 10, -10, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(-10, -10, -10, horizontal, "aaaaa"));

    //read
    CHECK_THROWS(notebook.read(-10, 10, 10, horizontal, 5));
    CHECK_THROWS(notebook.read(10, -10, 10, horizontal, 5));
    CHECK_THROWS(notebook.read(10, 10, -10, horizontal, 5));
    CHECK_THROWS(notebook.read(-10, -10, 10, horizontal, 5));
    CHECK_THROWS(notebook.read(10, -10, -10, horizontal, 5));
    CHECK_THROWS(notebook.read(-10, 10, -10, horizontal, 5));
    CHECK_THROWS(notebook.read(-10, -10, -10, horizontal, 5));

    //erase
    CHECK_THROWS(notebook.erase(-10, 10, 10, horizontal, 5));
    CHECK_THROWS(notebook.erase(10, -10, 10, horizontal, 5));
    CHECK_THROWS(notebook.erase(10, 10, -10, horizontal, 5));
    CHECK_THROWS(notebook.erase(-10, -10, 10, horizontal, 5));
    CHECK_THROWS(notebook.erase(10, -10, -10, horizontal, 5));
    CHECK_THROWS(notebook.erase(-10, 10, -10, horizontal, 5));
    CHECK_THROWS(notebook.erase(-10, -10, -10, horizontal, 5));
}


TEST_CASE("Invalid column index")
{
    Notebook notebook;
    //write
    CHECK_THROWS(notebook.write(10, 10, 100, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(10, 100, 150, horizontal, "aaaaa"));
    CHECK_THROWS(notebook.write(10, 10, 404, horizontal, "aaaaa"));

    CHECK_THROWS(notebook.read(10, 10, 100, horizontal, 5));
    CHECK_THROWS(notebook.read(10, 100, 150, horizontal, 5));
    CHECK_THROWS(notebook.read(10, 10, 404, horizontal, 5));

    CHECK_THROWS(notebook.erase(10, 10, 100, horizontal, 5));
    CHECK_THROWS(notebook.erase(10, 100, 150, horizontal, 5));
    CHECK_THROWS(notebook.erase(10, 10, 404, horizontal, 5));
}

TEST_CASE("String too long")
{
    Notebook notebook;
    //string too long horizontaly, verticaly is okay
    //100 char string
    string longstr = "HtznB6nQiCqNQoV1tqF2qiVNY9LaoE1u10BMRHxFvsgHYFnWf6tAHkTNBO4ATJi7jxSk346G1HunYrd0RM77fJrRguH0yqAV3FuD1";
    CHECK_THROWS(notebook.write(0, 0, 0, horizontal, longstr));

    //15 char string too long to input in column 90
    CHECK_THROWS(notebook.write(0, 1, 90, horizontal, "Ln2AHkNbchMUzwy"));
}

TEST_CASE("Write on written or erased lines")
{
    Notebook notebook;
    notebook.write(0, 0, 0, horizontal, "aaaaa");
    CHECK_THROWS(notebook.write(0, 0, 0, horizontal, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 0, vertical, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 4, horizontal, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 4, vertical, "bbbbb"));

    notebook.erase(0, 0, 0, horizontal, 5);
    CHECK_THROWS(notebook.write(0, 0, 0, horizontal, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 0, vertical, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 4, horizontal, "bbbbb"));
    CHECK_THROWS(notebook.write(0, 0, 4, vertical, "bbbbb"));   
}