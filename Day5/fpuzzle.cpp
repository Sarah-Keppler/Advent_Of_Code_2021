#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>

typedef std::pair<int, int> point;

static void fillRow(std::vector<std::string> &board, std::pair<point, point> const &points)
{
    point min{(points.first.first > points.second.first) ? points.second : points.first};
    point max{(points.first.first < points.second.first) ? points.second : points.first};
    int dif{max.first - min.first + 1};
    for (unsigned int i = 0; dif > i; ++i)
    {
        char c{board[min.second][min.first + i]};
        if ('.' == c)
            board[min.second][min.first + i] = '1';
        else if ('1' == c)
            board[min.second][min.first + i] = '2';
    }
}

static void fillCol(std::vector<std::string> &board, std::pair<point, point> const &points)
{
    point min{(points.first.second > points.second.second) ? points.second : points.first};
    point max{(points.first.second < points.second.second) ? points.second : points.first};
    int dif{max.second - min.second + 1};
    for (unsigned int i = 0; dif > i; ++i)
    {
        char c{board[min.second + i][min.first]};
        if ('.' == c)
            board[min.second + i][min.first] = '1';
        else if ('1' == c)
            board[min.second + i][min.first] = '2';
    }
}

static point crtPoint(std::string const &s)
{
    return {std::stoi(std::string{s.substr(0, s.find(","))}), std::stoi(std::string{s.substr(s.find(",") + 1)})};
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{};
    std::vector<std::pair<point, point>> vect;
    std::vector<std::string> board;
    unsigned int xmax{0}, ymax{0};
    while (std::getline(file, line))
    {
        std::string start{line.substr(0, line.find(" -> "))}, end{line.substr(line.find(" -> ") + 4)};
        point sp{crtPoint(start)}, ep{crtPoint(end)};
        if (sp.first != ep.first && sp.second != ep.second)
            continue;
        vect.emplace_back(sp, ep);
        xmax = (sp.first > xmax) ? sp.first : xmax;
        ymax = (sp.second > ymax) ? sp.second : ymax;
        xmax = (ep.first > xmax) ? ep.first : xmax;
        ymax = (ep.second > ymax) ? ep.second : ymax;
    }
    for (unsigned int y = 0; (ymax + 1) > y; ++y)
        board.emplace_back(xmax + 1, '.');
    for (std::vector<std::pair<point, point>>::iterator it = vect.begin(), et = vect.end(); et != it; ++it)
    {
        if (it->first.second == it->second.second)
            fillRow(board, *it);
        else
            fillCol(board, *it);
    }
    unsigned int count{0};
    for (std::string s : board)
        for (char c : s)
            if ('2' == c)
                ++count;
    std::cout << count << std::endl;
}