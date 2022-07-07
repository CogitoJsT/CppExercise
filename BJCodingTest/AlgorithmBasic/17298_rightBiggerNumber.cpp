#include <iostream>
#include <string>
#include <stack>

constexpr size_t BufferSize = 1000000;
int nge[BufferSize]{};

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

    std::stack<PairData> intSt0;
    std::stack<PairData> intSt1;

    int num;
    std::cin >> num;
    intSt0.push(PairData(0, num));
    auto isIntSt0Source = true;
    for (int i = 1; i < numOfNumbers; ++i)
    {
        auto& refSourceStack = isIntSt0Source ? intSt0 : intSt1;
        auto& refDestStack = isIntSt0Source ? intSt1 : intSt0;

        std::cin >> num;

        while (!refSourceStack.empty())
        {
            auto pastNum = refSourceStack.top();
            refSourceStack.pop();

            if (pastNum.second < num)
            {
                nge[pastNum.first] = num;
            }
            else
            {
                refDestStack.push(pastNum);
            }
            refDestStack.push(PairData(i, num));
        }
        isIntSt0Source = isIntSt0Source ? false : true;
    }

    auto hasSpace{ false };
    for(int i = 0; i < numOfNumbers; ++i)
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

    return 0;
}
