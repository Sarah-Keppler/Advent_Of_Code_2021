#include <fstream>
#include <vector>
#include <string>
#include <iostream>

int main()
{
    std::ifstream file{"input.txt"};
    std::vector<std::string> inputs{};
    std::string line{};
    while (std::getline(file, line))
        inputs.push_back(line);
    std::vector<int> sums{};
    for (unsigned int it = 0, et = inputs.size(); et > (it + 2); ++it)
        sums.emplace_back(std::stoi(inputs[it]) + std::stoi(inputs[it + 1]) + std::stoi(inputs[it + 2]));
    int p = sums[0], c = 0;
    bool begin = true;
    for (int sum : sums)
    {
        if (begin)
        {
            begin = false;
            continue;
        }
        if (p < sum)
            ++c;
        p = sum;
    }
    std::cout << c << std::endl;
}