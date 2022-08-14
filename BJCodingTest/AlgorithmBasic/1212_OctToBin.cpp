#include <iostream>
#include <map>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}



int main()
{
    std::map<char, std::string> mapOctToBin = {
        {'0', "000"},
        {'1', "001"},
        {'2', "010"},
        {'3', "011"},
        {'4', "100"},
        {'5', "101"},
        {'6', "110"},
        {'7', "111"},
    };

    std::string inputNumStr;
    std::cin >> inputNumStr;

    for(int i = 0; i < inputNumStr.size(); ++i)
    {
        std::string binStr = mapOctToBin[inputNumStr[i]];
        std::cout << binStr;
    }
    std::cout << "\n";


    return 0;
}