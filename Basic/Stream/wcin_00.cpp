// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

int main()
{
    int numOfCmd{ 0 };
    std::wstring inputStr;

    std::wcout << L"Input number of commands : ";
    std::wcin >> numOfCmd;

    // flush input buffer to remove '\n'
    std::getline(std::wcin, inputStr);

    std::vector<std::wstring> cmdVec;
    cmdVec.reserve(numOfCmd);

    for (int i = 0; i < numOfCmd; ++i)
    {
        inputStr.clear();
        std::getline(std::wcin, inputStr);
        cmdVec.push_back(inputStr);
    }

    std::wcout << L"=== Output the input strings ===" << std::endl;
    std::for_each(cmdVec.begin(), cmdVec.end(), [](std::wstring str)
        {
            std::wcout << str << std::endl;
        });

    return 0;
}

