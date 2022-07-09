#include <iostream>
#include <string>
#include <stack>
#include <memory>

constexpr int BufferSize = 1000000;
int nge[BufferSize];
int inNumberBuf[BufferSize];

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
        std::cin >> inNumberBuf[i];
    }

    for (int i = 0; i < numOfNumbers - 1; ++i)
    {
        int j = i + 1;
        for(; j < numOfNumbers; ++j)
        {
            if(inNumberBuf[i] < inNumberBuf[j])
            {
                nge[i] = inNumberBuf[j];
                break;
            }
        }

        if(j == numOfNumbers)
        {
            nge[i] = -1;
        }

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