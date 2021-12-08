#include <iostream>
#include <fstream>
#include <vector>
#include <string>

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
    std::vector<int> timers{};
    std::getline(file, line);
    std::vector<std::string> split{msplit(line, ",")};
    for (std::string s : split)
        timers.emplace_back(std::stoi(s));
    for (unsigned int i = 0; 80 > i; ++i)
    {
        unsigned int add{0};
        for (std::vector<int>::iterator it = timers.begin(), et = timers.end(); et != it; ++it)
            if (0 == *it)
            {
                ++add;
                *it = 6;
            }
            else
            {
                --(*it);
            }
        timers.insert(timers.end(), add, 8);
    }
    std::cout << timers.size() << std::endl;
}