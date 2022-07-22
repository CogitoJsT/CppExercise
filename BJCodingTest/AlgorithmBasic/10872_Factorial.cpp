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
        unsigned int fact = inputNum;
        for(unsigned int i = inputNum - 1; i > 0; --i)
        {
            fact *= i;
        }
        std::cout << fact << "\n";
    }

    return 0;
}