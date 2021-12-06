#include <iostream>
#include <fstream>
#include <vector>
#include <string>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{};
    unsigned int y{0}, x{0}, aim{0};
    while (std::getline(file, line))
    {
        std::string com{line.substr(0, line.find(" "))};
        int val{std::stoi(line.substr(line.find(" ") + 1))};
        if (!com.compare("forward"))
        {
            x += val;
            y += val * aim;
        }
        else if (!com.compare("down"))
        {
            aim += val;
        }
        else
        {
            aim -= val;
        }
    }
    std::cerr << "y: " << y << std::endl
              << "x: " << x << std::endl
              << "aim: " << aim << std::endl
              << "---------" << std::endl;
    std::cout << y * x << std::endl;
}