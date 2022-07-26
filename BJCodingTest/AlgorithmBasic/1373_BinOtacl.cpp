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

int decimToOctal(int num)
{
    if(num < 8)
    {
        return num;
    }

    int count{0};
    int sum{0};
    int q{num}, rem{0};
    do{
        rem = q % 8;
        q = q / 8;
        sum += rem * std::pow(10, count++);
    }while(q > 7);
    sum += q * std::pow(10, count);

    return sum;
}

int main()
{
    std::string numberStr;
    std::cin >> numberStr;

    std::cout << decimToOctal(binToDecim(numberStr)) << "\n";

    return 0;
}