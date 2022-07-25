#include <iostream>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    int numOfInput{0};
    std::cin >> numOfInput;

    auto isPrime = [](int num) {
        if(num == 1 || num == 0)
        {
            return false;
        }

        for(int i = 2; i < num; ++i)
        {
            if(num % i == 0)
            {
                return false;
            }
        }
        return true;
    };

    int count {0};
    for(int i = 0; i < numOfInput; ++i)
    {
        int num{0};
        std::cin >> num;

        if(isPrime(num))
        {
            ++count;
        }
    }

    std::cout << count << "\n";

    return 0;
}