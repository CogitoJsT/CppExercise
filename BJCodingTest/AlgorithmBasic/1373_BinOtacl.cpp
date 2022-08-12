#include <iostream>
#include <string>
#include <cmath>
#include <map>


void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

void binToOct(std::string &binaryNum)
{
    int emptyDigit = 3 - binaryNum.size() % 3;
    int remainOct = binaryNum.size() / 3 + (emptyDigit < 3 ? 1 : 0);

    std::map<std::string, std::string> binToOctalMap = {
        {"000", "0"},
        {"001", "1"},
        {"010", "2"},
        {"011", "3"},
        {"100", "4"},
        {"101", "5"},
        {"110", "6"},
        {"111", "7"},
    };

    for(int i = 0; i < emptyDigit; ++i)
    {
        binaryNum = "0" + binaryNum;
    }

    for(int i = 0; i < remainOct; ++i)
    {
        std::string subStr = binaryNum.substr(3*i, 3);
        std::cout << binToOctalMap[subStr];
    }

    std::cout << "\n";
}

int main()
{
    std::string numberStr;
    numberStr.reserve(1000000);
    std::cin >> numberStr;

    binToOct(numberStr);

    return 0;
}