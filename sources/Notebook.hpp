#pragma ONCE

#include "Direction.hpp"
#include <iostream>
#include <string>
#include <climits>
#include <map>
#include <stdexcept>
using namespace std;

namespace ariel {
    class Notebook{

        map<pair<int, int>, string> notebook;

        public:
        
        static void check_input(int page, int row, int column, Direction direction, int length);
        void write(int page, int row, int column, Direction direction, string const &str);
        string read(int page, int row, int column, Direction direction, int length);
        void erase(int page, int row, int column, Direction direction, int length);
        static void show(int page);
    };
}




