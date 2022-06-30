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
    std::wcin.tie(nullptr);
    std::wcout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    int numOfCommands {0};
    std::wcin >> numOfCommands;

    MyQueue queue;

    for(int i = 0; i < numOfCommands; ++i)
    {
        std::wstring command;
        std::wcin >> command;
        if(command == L"push")
        {
            std::wcin >> command;
            queue.push(std::stoi(command));
        }
        else if(command == L"pop")
        {
            std::wcout << queue.pop() << L"\n";
        }
        else if(command == L"size")
        {
            std::wcout << queue.size() << L"\n";
        }
        else if(command == L"empty")
        {
            std::wcout << queue.empty() << L"\n";
        }
        else if(command == L"front")
        {
            std::wcout << queue.front() << L"\n";
        }
        else if(command == L"back")
        {
            std::wcout << queue.back() << L"\n";
        }
    }


    return 0;
}