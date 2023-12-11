#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <map>

class MapOfRanges
{
public:
    MapOfRanges() = default;
    
    void add(unsigned int srcStart, unsigned int dstStart, unsigned int length)
    {
        Range range{ srcStart, dstStart, length };
        if (m_ranges.empty()) m_ranges.push_back(range);
        else {
            auto it = m_ranges.begin();
            for (; it != m_ranges.end(); it++)
                if (it->srcStart > range.srcStart)
                    break;
            
            m_ranges.insert(it, range);
        }
    }

    unsigned int convert(unsigned int number)
    {
        for (auto &range : m_ranges) {
            if (number >= range.srcStart && number < range.srcStart + range.length)
                return range.dstStart + (number - range.srcStart);
        }

        return number;
    }

    void print()
    {
        for (auto &range : m_ranges) {
            std::cout << range.srcStart << '\n';
        }
    }

    MapOfRanges(const MapOfRanges &) = delete;
    MapOfRanges &operator=(const MapOfRanges &) = delete;
private:
    struct Range
    {
        unsigned int srcStart;
        unsigned int dstStart;
        unsigned int length;
    };

    std::vector<Range> m_ranges;
};

std::vector<unsigned int> seeds;
MapOfRanges seedToSoil;
MapOfRanges soilToFertilizer;
MapOfRanges fertilizerToWater;
MapOfRanges waterToLight;
MapOfRanges lightToTemperature;
MapOfRanges temperatureToHumidity;
MapOfRanges humidityToLocation;

unsigned int part1()
{
    std::ifstream fin("input.txt");
    std::stringstream stream;
    stream << fin.rdbuf();
    fin.close();
    auto inputStr = stream.str();
    unsigned int number;
    std::string str;    

    auto pos1 = inputStr.find_first_of(':');
    auto pos2 = inputStr.find_first_of('\n', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 2);
    stream.clear();
    stream.str(str);
    while (stream >> number)
        seeds.push_back(number);

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('s', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        seedToSoil.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('f', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        soilToFertilizer.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('w', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        fertilizerToWater.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('l', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        waterToLight.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('t', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        lightToTemperature.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    pos2 = inputStr.find_first_of('h', pos1);
    str = inputStr.substr(pos1 + 2, pos2 - pos1 - 4);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        temperatureToHumidity.add(src_start, dst_start, length);
    }

    pos1 = inputStr.find_first_of(':', pos2);
    str = inputStr.substr(pos1 + 2);
    stream.clear();
    stream.str(str);
    while(stream >> number) {
        unsigned int dst_start = number;
        unsigned int src_start, length;
        stream >> src_start >> length;
        humidityToLocation.add(src_start, dst_start, length);
    }

    unsigned int closest = (unsigned int)-1;
    for (auto seed : seeds) {
        auto soil = seedToSoil.convert(seed);
        auto fertilizer = soilToFertilizer.convert(soil);
        auto water = fertilizerToWater.convert(fertilizer);
        auto light = waterToLight.convert(water);
        auto temperature = lightToTemperature.convert(light);
        auto humidity = temperatureToHumidity.convert(temperature);
        auto location = humidityToLocation.convert(humidity);
        if (location < closest)
            closest = location;
    }
    return closest;
}

unsigned int part2()
{
    struct Range { unsigned int start, length; };
    std::vector<Range> seedRanges;

    for (size_t i = 0; i < seeds.size(); i += 2)
        seedRanges.push_back(Range{ seeds[i], seeds[i + 1] }); 

    // NOTE: This could run in parallel    
    unsigned int closest = (unsigned int)-1;
    for (auto &range : seedRanges)
    {
        for (auto seed = range.start; seed < range.start + range.length; seed++)
        {
            auto soil = seedToSoil.convert(seed);
            auto fertilizer = soilToFertilizer.convert(soil);
            auto water = fertilizerToWater.convert(fertilizer);
            auto light = waterToLight.convert(water);
            auto temperature = lightToTemperature.convert(light);
            auto humidity = temperatureToHumidity.convert(temperature);
            auto location = humidityToLocation.convert(humidity);
            if (location < closest)
                closest = location;
            }
    }

    return closest;
}

int main()
{
    std::cout << "part1: " << part1() << '\n';
    std::cout << "part2: " << part2() << '\n';
    return 0;
}
