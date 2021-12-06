#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

static int convert(long n)
{
    int dec{0}, i{0}, rem{0};
    while (n != 0)
    {
        rem = n % 10;
        n /= 10;
        dec += rem * pow(2, i);
        ++i;
    }
    return dec;
}

int main()
{
    std::ifstream file{"input.txt"};
    std::string line{}, gamma{}, epsilon{};
    std::vector<int> ones, zeros;
    bool begin{true};
    while (std::getline(file, line))
    {
        if (begin)
        {
            for (unsigned int it = 0, et = line.size(); et > it; ++it)
            {
                zeros.emplace_back(0);
                ones.emplace_back(0);
            }
            begin = false;
        }
        for (unsigned int it = 0, et = line.size(); et > it; ++it)
            if ('0' == line[it])
                ++ones[it];
            else
                ++zeros[it];
    }
    for (unsigned int it = 0, et = ones.size(); et > it; ++it)
        if (ones[it] > zeros[it])
        {
            gamma.push_back('1');
            epsilon.push_back('0');
        }
        else
        {
            gamma.push_back('0');
            epsilon.push_back('1');
        }
    long igamma{convert(std::stol(gamma))}, iepsilon{convert(std::stol(epsilon))};
    std::cout << igamma * iepsilon << std::endl;
}