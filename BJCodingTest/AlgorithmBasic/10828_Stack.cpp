#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class MyStack
{
public:

    void push(int x)
    {
        stackBuffer.push_back(x);
    }

    int pop()
    {
        if(stackBuffer.size() < 1)
        {
            return -1;
        }
        else
        {
            auto elem = stackBuffer.back();
            stackBuffer.pop_back();
            return elem;
        }
    }

    int size()
    {
        return stackBuffer.size();
    }

    int empty()
    {
        return stackBuffer.size() < 1 ? 1 : 0;
    }

    int top()
    {
        if(stackBuffer.size() < 1)
        {
            return -1;
        }
        else
        {
            auto elem = stackBuffer.back();
            return elem;
        }
    }

private:
    std::vector<int> stackBuffer;
};

bool readCommands(std::vector<std::wstring> &cmdVec)
{
    int numOfCmd{ 0 };
    std::wstring inputStr;

    //std::wcout << L"Input number of commands : ";
    std::wcin >> numOfCmd;

    // flush input buffer to remove '\n'
    std::getline(std::wcin, inputStr);

    if(numOfCmd < 1 || numOfCmd > 10000)
    {
        return false;
    }

    cmdVec.reserve(numOfCmd);

    for (int i = 0; i < numOfCmd; ++i)
    {
        inputStr.clear();
        std::getline(std::wcin, inputStr);
        cmdVec.push_back(inputStr);
    }

    return true;
}

void executeOneCommand(MyStack& stack, std::vector<std::wstring> command)
{
    auto stackCmd = command[0];
    if(stackCmd.compare(L"push") == 0)
    {
        auto stackData = std::stoi(command[1]);
        stack.push(stackData);
    }
    else if(stackCmd.compare(L"pop") == 0)
    {
        std::wcout << stack.pop() << std::endl;
    }
    else if(stackCmd.compare(L"size") == 0)
    {
        std::wcout << stack.size() << std::endl;
    }
    else if(stackCmd.compare(L"empty") == 0)
    {
        std::wcout << stack.empty() << std::endl;
    }
    else if(stackCmd.compare(L"top") == 0)
    {
        std::wcout << stack.top() << std::endl;
    }
}



int main()
{
    std::vector<std::wstring> cmdVec;
    const auto readRet = readCommands(cmdVec);
    if(!readRet)
    {
        return 0;
    }

    MyStack stack;
    
    auto executeCommnds = [&stack](std::wstring cmdStr)
    {
        std::vector<std::wstring> splitCmd;
        auto commandStr = cmdStr.substr(0, 4);
        if(commandStr.compare(L"push") == 0)
        {
            auto dataStr = cmdStr.substr(5);
            splitCmd.push_back(commandStr);
            splitCmd.push_back(dataStr);
        }
        else
        {
            splitCmd.push_back(cmdStr);
        }

        executeOneCommand(stack, splitCmd);
    };

    for_each(cmdVec.begin(), cmdVec.end(), executeCommnds);

    return 0;
}