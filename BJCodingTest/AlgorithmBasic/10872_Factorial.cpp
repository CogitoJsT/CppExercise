#include <iostream>
#include <cmath>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}


int main()
{
    int inputNum;
    std::cin >> inputNum;


    if(inputNum == 0)
    {
        std::cout << "1\n";
    }
    else
    {
        auto ret = std::tgamma(inputNum) * inputNum;
        std::cout << static_cast<unsigned int>(ret) << "\n";
    }

    return 0;
}