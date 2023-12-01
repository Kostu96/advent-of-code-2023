#include <iostream>
#include <fstream>
#include <array>

unsigned int part1()
{
    std::ifstream fin("input.txt");
    std::string str{};

    unsigned int total = 0;

    while (std::getline(fin, str))
    {
        char c = str[str.find_first_of("123456789")];
        int a = (c - '0') * 10;
        c = str[str.find_last_of("123456789")];
        a += c - '0';
        total += a;
    }

    fin.close();
    return total;
}

unsigned int part2()
{
    std::array<const char*, 9> digitStrs{
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"
    };
    unsigned int total = 0;
    std::ifstream fin("input.txt");
    std::string str{};

    while (std::getline(fin, str))
    {
        unsigned int first_digit = 0, second_digit = 0;

        auto pos1 = str.size();
        for (auto i = 0; i < 9; i++)
        {
            auto new_pos = str.find(digitStrs[i]);
            if (new_pos != str.npos && new_pos < pos1)
            {
                pos1 = new_pos;
                first_digit = i + 1;
            }
        }

        auto pos2 = str.find_first_of("123456789");
        if (pos2 < pos1) {
            first_digit = str[pos2] - '0';
        }

        pos1 = 0;
        for (auto i = 0; i < 9; i++)
        {
            auto new_pos = str.rfind(digitStrs[i]);
            if (new_pos != str.npos && new_pos > pos1)
            {
                pos1 = new_pos;
                second_digit = i + 1;
            }
        }

        pos2 = str.find_last_of("123456789");
        if (pos2 >= pos1) {
            second_digit = str[pos2] - '0';
        }

        unsigned int number = first_digit * 10 + second_digit;
        total += number;
    }

    fin.close();
    return total;
}

int main()
{
    std::cout << "part1: " << part1() << '\n';
    std::cout << "part2: " << part2() << '\n';

    return 0;
}
