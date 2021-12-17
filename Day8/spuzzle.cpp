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
    std::vector<std::string> pats{10}, digits{}, ssixs{}, sfives{};
    unsigned int sum{0};
    while (std::getline(file, line))
    {
        std::size_t found{line.find(" | ")};
        std::vector<std::string> pats{10}, digits{msplit(line.substr(found + 3), " ")}, ssixs{}, sfives{};
        std::vector<std::string> tmp{msplit(line.substr(0, found), " ")};
        for (std::string s : tmp)
        {
            switch (s.size())
            {
            case 2:
                pats[1] = s;
                break;
            case 4:
                pats[4] = s;
                break;
            case 3:
                pats[7] = s;
                break;
            case 7:
                pats[8] = s;
                break;
            case 6:
                ssixs.emplace_back(s);
                break;
            default:
                sfives.emplace_back(s);
                break;
            }
        }
        char lc{}, lf{};
        unsigned int idx{0};
        for (std::vector<std::string>::const_iterator it = ssixs.cbegin(), et = ssixs.cend(); et != it; ++it)
            if (std::string::npos == it->find(pats[1][0]) || std::string::npos == it->find(pats[1][1]))
            {
                pats[6] = *it;
                idx = std::distance(ssixs.cbegin(), it);
                if (std::string::npos == it->find(pats[1][0]))
                {
                    lc = pats[1][0];
                    lf = pats[1][1];
                }
                else
                {
                    lc = pats[1][1];
                    lf = pats[1][0];
                }
            }
        for (std::string s : sfives)
            if (std::string::npos != s.find(lc) && std::string::npos != s.find(lf))
                pats[3] = s;
            else if (std::string::npos != s.find(lc))
                pats[2] = s;
            else
                pats[5] = s;
        unsigned int t{}, left{};
        if (idx == 0)
        {
            t = 1;
            left = 2;
        }
        else
        {
            t = 0;
            left = (1 == idx) ? 2 : 1;
        }
        char unknown{};
        for (char c : pats[8])
            if (std::string::npos == ssixs[t].find(c))
                unknown = c;
        if (std::string::npos == pats[3].find(unknown))
        {
            pats[9] = ssixs[t];
            pats[0] = ssixs[left];
        }
        else
        {
            pats[0] = ssixs[t];
            pats[9] = ssixs[left];
        }
        std::string num{};
        for (std::string digit : digits)
            for (std::vector<std::string>::const_iterator it = pats.cbegin(), et = pats.cend(); et != it; ++it)
                if (compare(*it, digit))
                    num.push_back(std::to_string(std::distance(pats.cbegin(), it))[0]);
        sum += std::stoi(num);
    }
    std::cout << sum << std::endl;
}