#include <iostream>
#include <fstream>

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
    unsigned int total = 0;

    return total;
}

int main()
{
    std::cout << "part1: " << part1() << '\n';
    std::cout << "part2: " << part2() << '\n';

    return 0;
}
