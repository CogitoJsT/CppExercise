#include <iostream>
#include <cmath>

int calcFactorial(int n)
{
    auto nf = n;
    for(int i = n - 1; i > 0; --i)
    {
        nf *= i;
    }

    return nf;
}

int main()
{
    for(int num = 1; num < 13; ++num)
    {
        auto tgamm = std::tgamma(num) * num;
        auto myFact = calcFactorial(num);

        std::cout << "tgamma : " << tgamm << "(" << static_cast<int>(tgamm) << ")" << " || myFactorial : " << myFact << "\n";
    }

    return 0;
}