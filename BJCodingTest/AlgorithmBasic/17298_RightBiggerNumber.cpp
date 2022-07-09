#include <iostream>
#include <string>
#include <stack>
#include <memory>

constexpr int BufferSize = 1000000;
int nge[BufferSize];
int inNumBuf[BufferSize];

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    int numOfNumbers;
    std::cin >> numOfNumbers;

    for (int i = 0; i < numOfNumbers; ++i)
    {
        std::cin >> inNumBuf[i];
    }

    std::stack<int> intStack;

    intStack.push(inNumBuf[numOfNumbers - 1]);
    for (int i = numOfNumbers - 2; i >= 0; --i)
    {
        auto currentNum = inNumBuf[i];
        auto stackTop = intStack.top();
        if(currentNum < stackTop)
        {
            nge[i] = stackTop;
        }
        else
        {
            intStack.pop();
            auto top = -1L;
            while(!intStack.empty())
            {
                top = intStack.top();
                if(currentNum < top)
                {
                    break;
                }
                else
                {
                    intStack.pop();
                }
            }
            nge[i] = intStack.empty() ? -1 : top;
        }

        intStack.push(currentNum);
    }

    nge[numOfNumbers-1] = -1;

    std::cout << nge[0];
    for (int i = 1; i < numOfNumbers; ++i)
    {
        std::cout << " " << nge[i];
    }
    std::cout << "\n";

    return 0;
}