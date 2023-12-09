#include <iostream>
#include <fstream>
#include <vector>

unsigned int part1(const std::vector<std::string> &schematic)
{
    unsigned int total = 0;

    for (size_t row = 0; row < schematic.size(); row++)
    {
        const auto& rowStr = schematic[row];
        const auto rowNpos = rowStr.npos;
        
        size_t pos1 = 0, pos2 = 0;
        while(pos1 != rowNpos) {
            pos1 = rowStr.find_first_of("1234567890", pos2);
            pos2 = rowStr.find_first_not_of("1234567890", pos1);

            if (pos1 != rowNpos) {
                unsigned int number = std::atoi(rowStr.substr(pos1, pos2 - pos1).c_str());

                std::vector<std::pair<size_t, size_t>> neighbours{};
                for (auto i = (pos1 > 0 ? pos1 - 1 : pos1); i <= (pos2 == rowNpos ? rowStr.size() - 1: pos2); i++)
                {
                    if (row > 0)
                        neighbours.push_back({ i, row - 1 });

                    if (row < schematic.size() - 1)
                        neighbours.push_back({ i, row + 1});
                }
                if (pos1 > 0)
                    neighbours.push_back({ pos1 - 1, row });

                if (pos2 != rowNpos)
                    neighbours.push_back({ pos2, row });

                bool legit = false;
                for (auto& n : neighbours) {
                    if (schematic[n.second][n.first] != '.')
                        legit = true;
                }

                if (legit) total += number;
            }
        }
    }

    return total;
}

struct Number
{
    unsigned int value = 0;
    size_t row = 0;
    size_t pos = 0;
    size_t size = 0;
};

unsigned int part2(const std::vector<std::string> &schematic)
{
    unsigned int total = 0;

    std::vector<Number> numbers;

    for (size_t row = 0; row < schematic.size(); row++)
    {
        const auto& rowStr = schematic[row];
        const auto rowNpos = rowStr.npos;
        
        size_t pos1 = 0, pos2 = 0;
        while(pos1 != rowNpos) {
            pos1 = rowStr.find_first_of("1234567890", pos2);
            pos2 = rowStr.find_first_not_of("1234567890", pos1);

            if (pos1 != rowNpos) {
                Number number{};
                number.value = std::atoi(rowStr.substr(pos1, pos2 - pos1).c_str());
                number.row = row;
                number.pos = pos1;
                number.size = pos2 - pos1;

                numbers.push_back(number);
            }
        }
    }

    for (size_t row = 0; row < schematic.size(); row++)
    {
        const auto& rowStr = schematic[row];
        const auto rowNpos = rowStr.npos;

        size_t pos = 0;
        while(pos != rowNpos) {
            pos = rowStr.find_first_of('*', pos + 1);

            if (pos != rowNpos) {
                unsigned int count = 0;
                unsigned int neightbours[2];
                for (const auto& number : numbers) {
                    if (number.row < row - 1 || number.row > row + 1) continue;
                    if (number.pos + number.size < pos || number.pos > pos + 1) continue;

                    if (count < 2) neightbours[count] = number.value;
                    count++;
                }
            
                if (count == 2) {
                   total += neightbours[0] * neightbours[1];
                }
            }
        }
    }

    return total;
}

int main()
{
    std::ifstream fin("input.txt");

    std::string str{};
    std::vector<std::string> schematic{};
    while(std::getline(fin, str)) schematic.push_back(str);

    std::cout << "part1: " << part1(schematic) << '\n';
    std::cout << "part2: " << part2(schematic) << '\n';

    fin.close();
    return 0;
}
