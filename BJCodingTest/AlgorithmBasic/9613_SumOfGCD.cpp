#include <iostream>
#include <vector>
#include <numeric>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int getSumOfGcd(std::vector<int> &numVec)
{
    int sum{0};
    for(int i = 0; i < numVec.size() - 1; ++i)
    {
        for(int j = i + 1; j < numVec.size(); ++j)
        {
            sum += std::gcd(numVec[i], numVec[j]);
        }
    }
    return sum;
}

int main()
{
    int numOfCase{0};
    std::cin >> numOfCase;

    for(int i = 0; i < numOfCase; ++i)
    {
        int numOfNums{0};
        std::cin >> numOfNums;

        std::vector<int> intVec;
        for(int j = 0; j < numOfNums; ++j)
        {
            int num{0};
            std::cin >> num;
            intVec.push_back(num);
        }

        std::cout << getSumOfGcd(intVec) << "\n";
    }

    return 0;
}