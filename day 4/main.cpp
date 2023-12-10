#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

unsigned int part1()
{
    unsigned int total = 0;

    std::ifstream fin("input.txt");
    std::string str{};
    while (std::getline(fin, str))
    {
        auto colonPos = str.find_first_of(':');
        auto pipePos = str.find_first_of('|', colonPos + 1);
        auto str1 = str.substr(colonPos + 1, pipePos - colonPos - 2);
        auto str2 = str.substr(pipePos + 1);

        std::vector<unsigned int> winning;
        std::stringstream winStream(str1);
        unsigned int number;
        while (winStream >> number) winning.push_back(number);

        unsigned int points = 0;
        std::stringstream numStream(str2);
        while (numStream >> number)
        {
            if (std::find(winning.begin(), winning.end(), number) != winning.end()) {
                if (points == 0) points = 1;
                else points *= 2;
            }
        }

        total += points;
    }

    return total;
}

unsigned int sum_points(const std::vector<unsigned int>& matches, size_t start, size_t count)
{
    unsigned int total = 0;
    for (size_t i = start; i < start + count && i < matches.size(); i++)
    {
        total += 1 + sum_points(matches, i + 1, matches[i]);
    }
    return total;
}

unsigned int part2()
{
    std::ifstream fin("input.txt");
    std::string str{};
    std::vector<unsigned int> matches;
    while (std::getline(fin, str))
    {
        auto colonPos = str.find_first_of(':');
        auto pipePos = str.find_first_of('|', colonPos + 1);
        auto str1 = str.substr(colonPos + 1, pipePos - colonPos - 2);
        auto str2 = str.substr(pipePos + 1);

        std::vector<unsigned int> winning;
        std::stringstream winStream(str1);
        unsigned int number;
        while (winStream >> number) winning.push_back(number);

        std::stringstream numStream(str2);
        matches.push_back(0);
        while (numStream >> number)
        {
            if (std::find(winning.begin(), winning.end(), number) != winning.end()) {
                matches.back()++;
            }
        }
    }

    return sum_points(matches, 0, matches.size());
}

int main()
{
    std::cout << "part1: " << part1() << '\n';
    std::cout << "part2: " << part2() << '\n';
    return 0;
}
