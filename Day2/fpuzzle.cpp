#include <iostream>
#include <fstream>
#include <string>

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{};
    unsigned int y{0}, x{0};
    while (std::getline(file, line))
    {
        std::string com{line.substr(0, line.find(" "))};
        int val{std::stoi(line.substr(line.find(" ") + 1))};
        if (!com.compare("forward"))
            x += val;
        else if (!com.compare("down"))
            y += val;
        else
            y -= val;
    }
    std::cout << y * x << std::endl;
}