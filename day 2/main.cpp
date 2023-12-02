#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

bool isSetPossible(unsigned int red, unsigned int green, unsigned int blue)
{
    constexpr unsigned int RED_COUNT = 12;
    constexpr unsigned int GREEN_COUNT = 13;
    constexpr unsigned int BLUE_COUNT = 14;

    if (red > RED_COUNT) return false;
    if (green > GREEN_COUNT) return false;
    if (blue > BLUE_COUNT) return false;

    return true;
}

std::vector<std::string> parseGame(std::string &game)
{
    std::vector<std::string> sets{};

    auto semicolonPos = game.find_first_of(";");
    while (semicolonPos != game.npos)
    {
        std::string set{};
        set = game.substr(0, semicolonPos);
        game = game.substr(semicolonPos + 1);
        semicolonPos = game.find_first_of(";");
        sets.push_back(std::move(set));
    }

    sets.push_back(std::move(game));
    return sets;
}

int part1()
{
    unsigned int total = 0;
    std::ifstream fin("input.txt");
    std::string str{};
    while (std::getline(fin, str))
    {
        auto colonPos = str.find_first_of(':');
        auto str1 = str.substr(0, colonPos);
        auto str2 = str.substr(colonPos + 1);

        std::stringstream ss(str1);
        std::string temp;
        unsigned int gameID;
        ss >> temp;
        ss >> gameID;
        
        auto sets = parseGame(str2);

        bool possible = true;
        for (auto& set : sets)
        {
            unsigned int current_red = 0, current_green = 0, current_blue = 0;
            unsigned int number;
            char ch;
            std::stringstream ss(set);
            do {
                ss >> number;
                ss >> temp;
                ch = temp[temp.size() - 1];
                if (ch == ',') temp = temp.substr(0, temp.size() - 1);

                if (temp == "red") current_red = number;
                else if (temp == "green") current_green = number;
                else if (temp == "blue") current_blue = number;
            } while (ch == ',');

            if (!isSetPossible(current_red, current_green, current_blue))
            {
                possible = false;
                break;
            }
        }

        if (possible) {
            total += gameID;
        }
    }

    fin.close();
    return total;
}

int part2()
{
    unsigned int total = 0;
    std::ifstream fin("input.txt");
    std::string str{};
    while (std::getline(fin, str))
    {
        auto colonPos = str.find_first_of(':');
        auto str1 = str.substr(0, colonPos);
        auto str2 = str.substr(colonPos + 1);

        std::stringstream ss(str1);
        std::string temp;
        unsigned int gameID;
        ss >> temp;
        ss >> gameID;
        
        auto sets = parseGame(str2);
        unsigned int min_red = 0, min_green = 0, min_blue = 0;
        for (auto& set : sets)
        {
            unsigned int current_red = 0, current_green = 0, current_blue = 0;
            unsigned int number;
            char ch;
            std::stringstream ss(set);
            do {
                ss >> number;
                ss >> temp;
                ch = temp[temp.size() - 1];
                if (ch == ',') temp = temp.substr(0, temp.size() - 1);

                if (temp == "red") current_red = number;
                else if (temp == "green") current_green = number;
                else if (temp == "blue") current_blue = number;
            } while (ch == ',');

            if (current_red > min_red) min_red = current_red;
            if (current_green > min_green) min_green = current_green;
            if (current_blue > min_blue) min_blue = current_blue;
        }

        total += min_red * min_green * min_blue;
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
