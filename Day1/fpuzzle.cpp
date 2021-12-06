#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file{"input.txt"};
    std::vector<std::string> i{};
    std::string line{};
    while (std::getline(file, line))
        i.push_back(line);
    int p = std::stoi(i[0]);
    int c = 0;
    for (std::string s : i)
    {
        if (std::stoi(s) == std::stoi(i[0]))
            continue;
        if (p < std::stoi(s))
        {
            ++c;
        }
        p = std::stoi(s);
    }
    std::cout << c << std::endl;
}