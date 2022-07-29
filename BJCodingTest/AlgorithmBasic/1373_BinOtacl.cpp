#include <iostream>
#include <string>
#include <cmath>


void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int binToDecim(std::string numStr)
{
    int sum {0};

    for(size_t i = 0; i < numStr.size(); ++i)
    {
        sum *= 2;
        if(numStr[i] == '1')
        {
            sum += 1;
        }
    }

    return sum;
}

void binToOct(std::string &binaryNum)
{
    int firstOct = binaryNum.size() % 3;
    int remainOct = binaryNum.size() / 3;
    std::string subStr;
    int decim{0};

    auto printOneOctal = [&](int pos) {
        subStr = binaryNum.substr(0, pos);
        decim = binToDecim(subStr);
        std::cout << decim;
        binaryNum = binaryNum.substr(pos);
    };

    if(firstOct)
    {
        printOneOctal(firstOct);
    }

    for(int i = 0; i < remainOct; ++i)
    {
        printOneOctal(3);
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