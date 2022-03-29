#include "Notebook.hpp"

using namespace std;
using namespace ariel;

const int MAX_COL = 99;
const int SHOW_ROWS = 100;
const int mincharASCII = 32;
const int maxCharASCII = 126;

void Notebook::check_input(int page, int row, int column, Direction direction, int length){
    if((direction == Direction::Horizontal && column + length > MAX_COL + 1) 
        || (column < 0 || page < 0 || row < 0 || length < 0)
        || column > MAX_COL){
        throw invalid_argument("Invalid input");
    }
}

void Notebook::write(int page, int row, int column, Direction direction, string const &str)
{
    check_input(page, row, column, direction, str.length());

    for (int i = 0; i < str.length(); i++)
    {
        if(str.at((size_t) i) < mincharASCII || str.at((size_t) i) > maxCharASCII){
            throw invalid_argument("Invalid string input");
        }
        if (str.at((size_t) i) == '~'){
            throw invalid_argument("Invalid string input");
        }
    }
    
    switch (direction)
    {
        case Direction::Horizontal:
        {
            if (notebook[pair<int, int>(page, row)].empty())
            {
                for (int i = 0; i < MAX_COL + 1; i++)
                {
                    notebook[pair<int, int>(page, row)].push_back('_');
                } 
            }
            for (int i = 0; i < str.length(); i++)
            {
                int pos = column + i;
                if (notebook[pair<int, int>(page, row)].at((size_t) pos) != '_')
                {
                    throw invalid_argument("Trying to overwrite an existing char");
                }
            }
            notebook[pair<int, int>(page, row)].replace((size_t) column, str.length(), str);
        }
        break;

        case Direction::Vertical:
        {
            for (int i = 0; i < str.length(); i++) {
                if (notebook[pair<int, int>(page, row + i)].empty()) {
                    for (int j = 0; j < MAX_COL + 1; j++) {
                        notebook[pair<int, int>(page, row + i)].push_back('_');
                    }
                }
                if (notebook[pair<int, int>(page, row + i)].at((size_t) column) != '_')
                {
                    throw invalid_argument("Trying to overwrite an existing char");
                }
            }
            for (int i = 0; i < str.length(); i++)
            {
                string s;
                s.push_back(str.at((size_t) i));
                notebook[pair<int, int>(page, row + i)].replace((size_t) column, 1, s);
            }
        }
        break;
    }
}

string Notebook::read(int page, int row, int column, Direction direction, int length)
{
    check_input(page, row, column, direction, length);

    string ans;
    switch (direction)
    {
        case Direction::Horizontal:
        {
            if (!notebook[pair<int, int>(page, row)].empty())
            {
                for (int i = 0; i < length; i++){
                    ans.push_back(notebook[pair<int, int>(page, row)].at((size_t) column + (size_t) i));
                }
                return ans;
            }

            for (int i = 0; i < length; i++)
            {
                ans.push_back('_');
            }
            return ans;

        }
        break;

        case Direction::Vertical:
        {
            for (int i = 0; i < length; ++i) {
            if (notebook[pair<int, int>(page, row + i)].empty()) {
                ans.push_back('_');
            } else {
                ans.push_back(notebook[pair<int, int>(page, row + i)].at((size_t) column ));
            }
        }
            return ans;
        }
        break;
    }
    return ans;
}

void Notebook::erase(int page, int row, int column, Direction direction, int length)
{
    check_input(page, row, column, direction, length);
    
    switch (direction)
    {
        case Direction::Horizontal:
        {
            if (notebook[pair<int, int>(page, row)].empty())
            {
                for (int i = 0; i < MAX_COL + 1; i++)
                {
                    notebook[pair<int, int>(page, row)].push_back('_');
                } 
            }
            string del;
            for (int i = 0; i < length; i++) {
                del.push_back('~');
            }
            notebook[pair<int, int>(page, row)].replace((size_t) column, (size_t) length, del);
        }
        break;

        case Direction::Vertical:
        {
            for (int i = 0; i < length; i++) {
                if (notebook[pair<int, int>(page, row + i)].empty()) {
                    for (int j = 0; j < MAX_COL + 1; j++) {
                        notebook[pair<int, int>(page, row + i)].push_back('_');
                    }
                }
                notebook[pair<int, int>(page, row + i)].replace((size_t) column, 1, "~");
            }
        }
        break;
    }
}

void Notebook::show(int page)
{
    if (page < 0){
        throw invalid_argument("Invalid page number");
    }
    for (int i = 0; i < SHOW_ROWS; i++) {
        //cout << read(page, i, 0, Direction::Horizontal, MAX_COL) << endl;
    }
}