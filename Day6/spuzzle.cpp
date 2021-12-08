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
    long long fday0{0}, fday1{0}, fday2{0}, fday3{0}, fday4{0}, fday5{0}, fday6{0}, fday7{0}, fday8{0};
    for (std::string s : split)
    {
        switch (std::stoi(s))
        {
        case 0:
            ++fday0;
            break;
        case 1:
            ++fday1;
            break;
        case 2:
            ++fday2;
            break;
        case 3:
            ++fday3;
            break;
        case 4:
            ++fday4;
            break;
        case 5:
            ++fday5;
            break;
        default:
            ++fday6;
            break;
        }
    }
    for (unsigned int i = 0; 256 > i; ++i)
    {
        long long save{fday0};
        fday0 = fday1;
        fday1 = fday2;
        fday2 = fday3;
        fday3 = fday4;
        fday4 = fday5;
        fday5 = fday6;
        fday6 = fday7 + save;
        fday7 = fday8;
        fday8 = save;
    }
    long long sum{fday0 + fday1 + fday2 + fday3 + fday4 + fday5 + fday6 + fday7 + fday8};
    std::cout << sum << std::endl;
}