#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <cctype>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    for(int i = 0; i < 100; ++i)
    {
        std::string inputStr;
        std::getline(std::cin, inputStr);

        std::array<int, 4> countArr{};

        for (auto ch : inputStr)
        {
            if (std::islower(ch))
            {
                countArr[0]++;
            }
            else if (std::isupper(ch))
            {
                countArr[1]++;
            }
            else if (std::isdigit(ch))
            {
                countArr[2]++;
            }
            else if (ch == ' ')
            {
                countArr[3]++;
            }
        }

        auto hasSpace{ false };
        std::for_each(std::begin(countArr), std::end(countArr), [&hasSpace](auto elem) {
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

    }
   
    return 0;
}