#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

static unsigned int getLessval(std::vector<std::string> const &arr, unsigned int const idx)
{
    unsigned int one{0}, zero{0};
    for (std::string s : arr)
        if ('1' == s[idx])
            ++one;
        else
            ++zero;
    if (zero <= one)
        return '0';
    else
        return '1';
}

static char getMostval(std::vector<std::string> const &arr, unsigned int const idx)
{
    unsigned int one{0}, zero{0};
    for (std::string s : arr)
        if ('1' == s[idx])
            ++one;
        else
            ++zero;
    if (one >= zero)
        return '1';
    else
        return '0';
}

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
    std::string line{};
    std::vector<std::string> ox{}, scrub{};
    while (std::getline(file, line))
    {
        ox.emplace_back(line);
        scrub.emplace_back(line);
    }
    char val{getMostval(ox, 0)};
    long unsigned int size{ox.size()};
    for (unsigned int idx = 0; size > idx; ++idx)
    {
        std::vector<std::string> save{};
        for (std::vector<std::string>::iterator it = ox.begin(), et = ox.end(); et != it && 1 != ox.size(); ++it)
            if (val == (*it)[idx])
                save.emplace_back(*it);
        ox = save;
        if (size > (idx + 1))
            val = getMostval(ox, idx + 1);
    }
    val = getLessval(scrub, 0);
    for (unsigned int idx = 0, edx = size; edx > idx; ++idx)
    {
        std::vector<std::string> save{};
        for (std::vector<std::string>::iterator it = scrub.begin(), et = scrub.end(); et != it && 1 != scrub.size(); ++it)
            if (val == (*it)[idx])
                save.emplace_back(*it);
        scrub = save;
        if (size > (idx + 1))
            val = getLessval(scrub, idx + 1);
    }
    long iox{convert(std::stol(ox[0]))}, iscrub{convert(std::stol(scrub[0]))};
    std::cout << iox * iscrub << std::endl;
}