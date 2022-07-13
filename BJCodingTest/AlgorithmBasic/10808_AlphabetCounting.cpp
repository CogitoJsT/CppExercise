#include <iostream>
#include <string>
#include <array>
#include <algorithm>

constexpr int AlphabetSize = 26;

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    std::string inputStr;
    std::cin >> inputStr;

    std::array<int, AlphabetSize> alphabetCntBuffer{};

    for (auto ch : inputStr)
    {
        alphabetCntBuffer[(ch & 0x1F) - 1]++;
    }

    auto hasSpace{ false };
    std::for_each(std::begin(alphabetCntBuffer), std::end(alphabetCntBuffer), [&hasSpace](auto elem) {
        if (hasSpace)
        {
            std::cout << " ";
        }
        else
        {
            hasSpace = true;
        }
        std::cout << elem;
    });
    std::cout << "\n";

   
    return 0;
}