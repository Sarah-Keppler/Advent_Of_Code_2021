#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <functional>

typedef std::pair<unsigned int, unsigned int> Point;

void print_disp(std::vector<std::string> const &disp)
{
    for (std::string s : disp)
        std::cerr << s << std::endl;
    std::cerr << "-------------------" << std::endl;
}

bool is_visited(std::vector<Point> const &visited, Point const &point)
{
    for (Point vp : visited)
        if (vp.first == point.first && vp.second == point.second)
            return true;
    return false;
}

//void see_horizon(std::vector<std::string> const &map, std::vector<std::string> &disp, std::vector<Point> &visited, unsigned int const x, unsigned int const y)
void see_horizon(std::vector<std::string> const &map, std::vector<Point> &visited, unsigned int const x, unsigned int const y)
{
    std::vector<Point> points{
        {x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}};
    for (Point point : points)
    {
        if (0 > point.first || 0 > point.second || map[0].size() <= point.first || map.size() <= point.second)
            continue;
        else if (is_visited(visited, point))
            continue;
        else if (map[point.second][point.first] != (map[y][x] + 1) || '9' == map[point.second][point.first])
            continue;
        else
        {
            //disp[point.second][point.first] = 'x';
            visited.emplace_back(point);
            //print_disp(disp);
            //see_horizon(map, disp, visited, point.first, point.second);
            see_horizon(map, visited, point.first, point.second);
        }
    }
}

bool is_low_point(std::vector<std::string> const &map, unsigned int const x, unsigned int const y)
{
    std::vector<Point> points{
        {x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}};
    for (Point point : points)
    {
        if (0 > point.first || 0 > point.second || map[0].size() <= point.first || map.size() <= point.second)
            continue;
        if (map[y][x] >= map[point.second][point.first])
            return false;
    }
    return true;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{};
    std::vector<std::string> inputs{};
    while (std::getline(file, line))
        inputs.push_back(line);
    std::map<unsigned int, unsigned int, std::greater<int>> basins{};
    std::vector<Point> visited{};
    for (unsigned int y = 0, ey = inputs.size(); ey > y; ++y)
    {
        for (unsigned int x = 0, ex = inputs[y].size(); ex > x; ++x)
        {
            if (is_low_point(inputs, x, y))
            {
                visited.emplace_back(x, y);
                see_horizon(inputs, visited, x, y);
                if (basins.find(visited.size()) == basins.end())
                    basins.insert({visited.size(), 1});
                else
                    basins[visited.size()] += 1;
            }
        }
    }
    unsigned int total{1};
    unsigned int idx{0};
    for (std::pair<unsigned int, unsigned int> pair : basins)
    {
        for (unsigned int it = 0, et = pair.second; et > it; ++it)
        {
            ++idx;
            total *= pair.first;
            if (3 <= idx)
                break;
        }
        if (3 <= idx)
            break;
    }
    std::cout << total << std::endl;
}