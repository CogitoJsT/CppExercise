#include <iostream>
#include <numeric>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    int numOfCases {0};
    std::cin >> numOfCases;

    for(int i = 0; i < numOfCases; ++i)
    {
        int a{0}, b{0};
        std::cin >> a >> b;

        std::cout << std::lcm(a, b) << "\n";
    }


    return 0;
}