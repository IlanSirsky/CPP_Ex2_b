#include "Notebook.hpp"

using namespace std;
using namespace ariel;

char Notebook::read_map(int x, int y)
{
    auto ptr = notebook.find(pair<int, int>(x, y));
    if (ptr == notebook.end())
    {
        return '_';
    }
    return ptr->second;
}

void Notebook::write(int page, int row, int column, Direction direction, string const &str)
{
    if (page < 0 || row < 0 || column < 0){
        throw "Invalid input";
    }
    for (int i = 0; i < str.length(); i++)
    {
        if (str[i] == '~'){
            throw("Invalid input");
        }
    }
    switch (direction)
    {
        case Direction::Horizontal:
        {
            for (int i = 0; i < str.length(); i++)
            {
                notebook[pair<int, int>(column + i, row)] = str.at(i);
            }
        }
        break;
        case Direction::Vertical:
        {
            for (int i = 0; i < str.length(); i++)
            {
                notebook[pair<int, int>(column, row + i)] = str.at(i);
            }
        }
        break;
    }
}

string Notebook::read(int page, int row, int column, Direction direction, int length)
{
    if (page < 0 || row < 0 || column < 0){
        throw "Invalid input";
    }
    string ans;
    switch (direction)
    {
        case Direction::Horizontal:
        {
            for (u_int i = 0; i < length; i++)
            {
                ans.push_back(read_map(column + i, row));
            }
        }
        break;
        case Direction::Vertical:
        {
            for (u_int i = 0; i < length; i++)
            {
                ans.push_back(read_map(column, row + i));
            }
        }
        break;
    }
    return ans;
}

void Notebook::erase(int page, int row, int column, Direction direction, int length)
{
    if (page < 0 || row < 0 || column < 0){
        throw "invalid input";
    }
}

void Notebook::show(int page)
{
    if (page < 0){
        throw "invalid input";
    }
    int end_x = 0;
    int end_y = 0;
    int start_x = INT_MAX; 
    int start_y = INT_MAX;
    // std::map<pair<u_int, u_int>, char>::iterator iter = board.begin();
    for(auto element : notebook) // element is of type: pair<pair<u_int, u_int>, char>
    {
        if (element.first.first < start_x)
        {
            start_x = element.first.first;
        }
        if (element.first.first > end_x)
        {
            end_x = element.first.first;
        }
        if (element.first.second < start_y)
        {
            start_y = element.first.second;
        }
        if (element.first.second > end_y)
        {
            end_y = element.first.second;
        }
    }

    for (u_int y = start_y; y <= end_y; y++)
    {
        for (u_int x = start_x; x <= end_x; x++)
        {
            cout << read_map(x, y) << ends;
        }
        cout << endl;
    }
}