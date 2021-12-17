#include <iostream>
#include <fstream>
#include <vector>
#include <string>

typedef std::vector<std::string> LSTR;

static bool compare(std::string const &pat, std::string const &s)
{
    std::string found{};
    if (pat.size() != s.size())
        return false;
    for (char c : s)
        if (std::string::npos != found.find(c))
            return false;
        else if (std::string::npos == pat.find(c))
            return false;
        else
            found.push_back(c);
    return true;
}

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
    std::vector<std::string> pats{4}, digits{};
    unsigned int count{0};
    while (std::getline(file, line))
    {
        std::size_t found{line.find(" | ")};
        std::vector<std::string> tmp{msplit(line.substr(0, found), " ")};
        for (std::string s : tmp)
        {
            switch (s.size())
            {
            case 2:
                pats[0] = s;
                break;
            case 4:
                pats[1] = s;
                break;
            case 3:
                pats[2] = s;
                break;
            case 7:
                pats[3] = s;
                break;
            default:
                break;
            }
        }
        digits = msplit(line.substr(found + 3), " ");

        for (std::string s : digits)
        {
            switch (s.size())
            {
            case 2:
                if (compare(pats[0], s))
                    ++count;
                break;
            case 4:
                if (compare(pats[1], s))
                    ++count;
                break;
            case 3:
                if (compare(pats[2], s))
                    ++count;
                break;
            case 7:
                if (compare(pats[3], s))
                    ++count;
                break;
            default:
                break;
            }
        }
    }
    std::cout << count << std::endl;
}