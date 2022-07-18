#include <iostream>

int main()
{
    int a{0}, b{0};
    std::cin >> a >> b;

    if(b > a)
    {
        std::swap(a, b);
    }

    auto mul = a * b;
    auto r = a % b;
    while(r != 0)
    {
        a = b;
        b = r;
        r = a % b;
    }

    std::cout << b << "\n" << mul/b << "\n";

    return 0;
}