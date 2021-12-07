#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <algorithm>

typedef std::vector<std::vector<std::pair<int, bool>>> BOARD;

static bool allCompleted(std::vector<bool> const &completed)
{
    for (bool b : completed)
        if (!b)
            return false;
    return true;
}

static unsigned int sumUnmarked(BOARD const &board)
{
    unsigned int sum{0};
    for (std::vector<std::pair<int, bool>> line : board)
        for (std::pair<int, bool> pair : line)
            if (!pair.second)
                sum += pair.first;
    return sum;
}

static bool win(BOARD const &board)
{
    for (unsigned int it = 0; 5 > it; ++it)
    {
        bool looking{true};
        for (unsigned int jt = 0; 5 > jt; ++jt)
            if (!board[it][jt].second)
            {
                looking = false;
                break;
            }
        if (looking)
            return true;
    }
    for (unsigned int it = 0; 5 > it; ++it)
    {
        bool looking{true};
        for (unsigned int jt = 0; 5 > jt; ++jt)
            if (!board[jt][it].second)
            {
                looking = false;
                break;
            }
        if (looking)
            return true;
    }
    return false;
}

static void mark(BOARD &board, unsigned int const num)
{
    for (BOARD::iterator vit = board.begin(), vet = board.end(); vet != vit; ++vit)
        for (std::vector<std::pair<int, bool>>::iterator it = vit->begin(), et = vit->end(); et != it; ++it)
            if (it->first == num)
                it->second = true;
}

static BOARD ctrBoard(std::vector<std::string> const &inputs, unsigned int &idx)
{
    BOARD board{};
    for (unsigned int y = 0; 5 > y; ++y)
    {
        std::vector<std::pair<int, bool>> nums{};
        for (unsigned int x = 0; 5 > x; ++x)
            nums.emplace_back(std::pair<int, bool>{std::stoi(std::string{inputs[idx].substr(x * 3, 2)}), false});
        board.emplace_back(nums);
        ++idx;
    }
    return board;
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
    std::vector<BOARD> boards;
    std::vector<std::string> inputs, split;
    std::vector<int> nums;
    while (std::getline(file, line))
        inputs.push_back(line);
    split = msplit(inputs[0], ",");
    for (std::string s : split)
        nums.emplace_back(std::stoi(s));
    for (unsigned int it = 2, et = inputs.size(); et > it; ++it)
        boards.emplace_back(ctrBoard(inputs, it));
    std::vector<bool> completed(boards.size());
    std::fill(completed.begin(), completed.end(), false);
    bool playing{true};
    unsigned int stop{0}, sum{0};
    for (std::vector<int>::const_iterator idx = nums.cbegin(), edx = nums.cend(); edx != idx; ++idx)
    {
        for (std::vector<BOARD>::iterator vit = boards.begin(), vet = boards.end(); vet != vit; ++vit)
        {
            long int dist{std::distance(boards.begin(), vit)};
            if (completed[dist])
                continue;
            mark(*vit, *idx);
            if (win(*vit))
            {
                stop = *idx;
                sum = sumUnmarked(*vit);
                completed[dist] = true;
                if (allCompleted(completed))
                {
                    playing = false;
                    break;
                }
            }
        }
        if (!playing)
            break;
    }
    std::cout << sum * stop << std::endl;
}