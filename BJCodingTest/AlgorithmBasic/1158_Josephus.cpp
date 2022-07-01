#include <iostream>
#include <vector>
#include <queue>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    int N{0}, K{0};

    std::cin >> N >> K;

    std::vector<int> intVec;
    std::queue<int> yosephus;
    for(int i = 0; i < N; ++i)
    {
        intVec.push_back(i+1);
    }

    int count {1};
    auto it = intVec.begin();
    while(intVec.size() != 0)
    {
        if(count == K)
        {
            count = 1;
            yosephus.push(*it);
            it = intVec.erase(it);
        }
        else
        {
            ++count;
            it++;
        }

        if(it == intVec.end())
        {
            it = intVec.begin();
        }
    }

    std::cout << "<";
    bool hasComma {false};
    while(yosephus.size() != 0)
    {
        if(hasComma)
            std::cout << ", ";
        else
            hasComma = true;
        std::cout << yosephus.front();
        yosephus.pop();
    }
    std::cout << ">\n";

    return 0;
}