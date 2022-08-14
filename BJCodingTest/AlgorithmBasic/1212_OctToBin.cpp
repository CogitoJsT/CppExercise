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

    if(inputNumStr == "0")
    {
        std::cout << "0\n";
        return 0;
    }

    for(int i = 0; i < inputNumStr.size(); ++i)
    {
        std::string binStr = mapOctToBin[inputNumStr[i]];
        if(i == 0)
        {
            for(auto iter = binStr.begin(); iter != binStr.end(); )
            {
                if(*iter == '1')
                {
                    break;
                }
                else
                {
                    iter = binStr.erase(iter);
                }
            }
        }
        std::cout << binStr;
    }
    std::cout << "\n";

    return 0;
}