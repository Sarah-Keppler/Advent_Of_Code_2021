#include <iostream>
#include <fstream>
#include <vector>
#include <string>

bool is_low_point(std::vector<std::string> const &map, unsigned int const x, unsigned int const y)
{
    std::vector<std::pair<unsigned int, unsigned int>> points{
        {x, y - 1}, {x + 1, y}, {x, y + 1}, {x - 1, y}};
    for (std::pair<unsigned int, unsigned int> point : points)
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
    unsigned int sum{0};
    for (unsigned int y = 0, ey = inputs.size(); ey > y; ++y)
    {
        for (unsigned int x = 0, ex = inputs[y].size(); ex > x; ++x)
        {
            if (is_low_point(inputs, x, y))
                sum += std::stoi(std::string{inputs[y][x]}) + 1;
        }
    }
    std::cout << sum << std::endl;
}