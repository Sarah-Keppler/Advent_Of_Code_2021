#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <algorithm>

// Triangular number
static int calcCost(unsigned int n)
{
    return ((n * (n + 1)) / 2);
}

static std::vector<std::string> msplit(std::string s, std::string const &delimiter)
{
    std::vector<std::string> arr{};
    std::size_t pos{0};
    std::string token{};
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        token = s.substr(0, pos);
        arr.emplace_back(token);
        s.erase(0, pos + delimiter.length());
    }
    arr.emplace_back(s);
    return arr;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{};
    std::getline(file, line);
    std::vector<std::string> split{msplit(line, ",")};
    std::vector<int> fuels;
    for (int it = 0, et = split.size(); et > it; ++it)
    {
        unsigned int sum{0};
        for (int mit = 0; et > mit; ++mit)
            sum += calcCost(std::abs(it - std::stoi(split[mit])));
        fuels.emplace_back(sum);
    }
    std::cout << *std::min_element(fuels.cbegin(), fuels.cend()) << std::endl;
}