#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file{"input.txt"};
    std::vector<std::string> input{};
    std::string line{};
    while (std::getline(file, line))
        input.push_back(line);
    int pre{std::stoi(input[0])};
    int count{0};
    for (std::string s : input)
    {
        if (std::stoi(s) == std::stoi(input[0]))
            continue;
        if (pre < std::stoi(s))
            ++count;
        pre = std::stoi(s);
    }
    std::cout << count << std::endl;
}