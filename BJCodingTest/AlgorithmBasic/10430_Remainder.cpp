#include <iostream>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    int a{0}, b{0}, c{0};
    std::cin >> a >> b >> c;

    auto A = (a + b)%c;
    auto B = ((a%c) + (b%c))%c;
    auto C = (a*b)%c;
    auto D = ((a%c) * (b%c))%c;

    std::cout << A << "\n" << B << "\n" << C << "\n" << D << "\n";

    return 0;
}