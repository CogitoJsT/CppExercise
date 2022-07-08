#include <iostream>
#include <string>
#include <list>
#include <memory>

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

    int numOfNumbers;
    std::cin >> numOfNumbers;

    int *nge = new int[numOfNumbers];
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
        auto ngeNum = nge[i] < 1 ? -1 : nge[i];
        if (hasSpace)
        {
            std::cout << " ";
        }
        else
        {
            hasSpace = true;
        }
        std::cout << ngeNum;
    }
    std::cout << "\n";

    delete[] nge;
    return 0;
}
