#include <iostream>
#include <fstream>
#include <vector>
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
            y += val;
        else if (!com.compare("down"))
            x += val;
        else
            x -= val;
    }
    std::cerr << "y: " << y << std::endl
              << "x: " << x << std::endl;
    std::cout << y * x << std::endl;
}