#include <iostream>
#include <string>
#include <list>
#include <memory>

constexpr int BufferSize = 1000000;
int nge[BufferSize];

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    using PairData = std::pair<int, int>;

    init();

    std::fill_n(nge, BufferSize, -1);

    int numOfNumbers;
    std::cin >> numOfNumbers;

    std::list<PairData> intList;

    int num;
    std::cin >> num;
    intList.push_back(PairData(0, num));
    for (int i = 1; i < numOfNumbers; ++i)
    {
        std::cin >> num;

        for(auto it = intList.begin(); it != intList.end();)
        {
            if (it->second < num)
            {
                nge[it->first] = num;
                it = intList.erase(it);
                if (intList.empty())
                {
                    break;
                }
            }
            else
            {
                ++it;
            }
        }

        intList.push_back(PairData(i, num));
    }

    auto hasSpace{ false };
    for (int i = 0; i < numOfNumbers; ++i)
    {
        if (hasSpace)
        {
            std::cout << " ";
        }
        else
        {
            hasSpace = true;
        }
        std::cout << nge[i];
    }
    std::cout << "\n";

    return 0;
}