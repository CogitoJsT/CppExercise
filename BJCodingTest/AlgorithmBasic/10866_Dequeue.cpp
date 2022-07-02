#include <iostream>

constexpr int BufSize = 20000;
constexpr int HalfBufSize = 20000/2;

class Dequeue
{
public:
    void push_front(int x)
    {
        if(count < 1)
        {
            buffer[frontIndex] = x;
        }
        else
        {
            buffer[--frontIndex] = x;
        }
        ++count;
    }
    void push_back(int x)
    {
        if(count < 1)
        {
            buffer[endIndex] = x;
        }
        else
        {
            buffer[++endIndex] = x;
        }
        ++count;
    }
    int pop_front()
    {
        if(count == 0)
        {
            return -1;
        }
        else
        {
            count--;
            auto ret = buffer[frontIndex];
            if(frontIndex != endIndex)
            {
                ++frontIndex;
            }
            return ret;
        }
    }
    int pop_back()
    {
        if(count == 0)
        {
            return -1;
        }
        else
        {
            count--;
            auto ret = buffer[endIndex];
            if(endIndex != frontIndex)
            {
                endIndex--;
            }
            return ret;
        }
    }
    int size()
    {
        return count;
    }
    int empty()
    {
        return count == 0 ? 1 : 0;
    }
    int front()
    {
        return count == 0 ? -1 : buffer[frontIndex];
    }
    int back()
    {
        return count == 0 ? -1 : buffer[endIndex];
    }

private:
    int buffer[BufSize]{};
    int frontIndex {HalfBufSize};
    int endIndex {HalfBufSize};
    int count {0};
};

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    int numOfCommands{0};
    std::cin >> numOfCommands;

    Dequeue dequeue;
    for(int i = 0; i < numOfCommands; ++i)
    {
        std::string cmd0;
        std::cin >> cmd0;

        if(cmd0 == "push_front")
        {
            int num;
            std::cin >> num;

            dequeue.push_front(num);
        }
        else if(cmd0 == "push_back")
        {
            int num;
            std::cin >> num;

            dequeue.push_back(num);
        }
        else if(cmd0 == "pop_front")
        {
            std::cout << dequeue.pop_front() << "\n";
        }
        else if(cmd0 == "pop_back")
        {
            std::cout << dequeue.pop_back() << "\n";
        }
        else if(cmd0 == "size")
        {
            std::cout << dequeue.size() << "\n";
        }
        else if(cmd0 == "empty")
        {
            std::cout << dequeue.empty() << "\n";
        }
        else if(cmd0 == "front")
        {
            std::cout << dequeue.front() << "\n";
        }
        else if(cmd0 == "back")
        {
            std::cout << dequeue.back() << "\n";
        }
    }

    return 0;
}