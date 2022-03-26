#pragma ONCE

#include "Direction.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <tuple>
#include <map>
#include <stdexcept>
using namespace std;

namespace ariel {
    class Notebook{
            std::map<pair<int, int>, char> notebook;
        public:
        char read_map(u_int x, u_int y);
        void write(int page, int row, int column, Direction direction, string const &str);
        static string read(int page, int row, int column, Direction direction, int length);
        void erase(int page, int row, int column, Direction direction, int length);
        void show(int page);
    };
}
