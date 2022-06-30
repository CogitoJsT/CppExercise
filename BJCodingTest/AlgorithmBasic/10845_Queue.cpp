#include <iostream>
#include <string>

#define BUFSIZE 100000

class MyQueue
{
public:
    void push(int x)
    {
        buffer[end++] = x;
    }

    int pop()
    {
        return begin == end ? -1 : buffer[begin++];
    }

    int size()
    {
        return (end - begin);
    }

    int empty()
    {
        return begin == end ? 1 : 0;
    }

    int front()
    {
        return begin == end ? -1 : buffer[begin];
    }

    int back()
    {
        return begin == end ? -1 : buffer[end-1];
    }

private:
    int begin {0};
    int end {0};
    int buffer[BUFSIZE];
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

    int numOfCommands {0};
    std::cin >> numOfCommands;

    MyQueue queue;

    for(int i = 0; i < numOfCommands; ++i)
    {
        std::string command;
        std::cin >> command;
        if(command == "push")
        {
            std::cin >> command;
            queue.push(std::stoi(command));
        }
        else if(command == "pop")
        {
            std::cout << queue.pop() << "\n";
        }
        else if(command == "size")
        {
            std::cout << queue.size() << "\n";
        }
        else if(command == "empty")
        {
            std::cout << queue.empty() << "\n";
        }
        else if(command == "front")
        {
            std::cout << queue.front() << "\n";
        }
        else if(command == "back")
        {
            std::cout << queue.back() << "\n";
        }
    }


    return 0;
}