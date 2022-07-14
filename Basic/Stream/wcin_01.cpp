#include <iostream>

int main()
{
    // In console, ctrl + z inputs EOF
    while(!std::wcin.eof())
    {
        std::wstring inputStr;
        std::wcin >> inputStr;
        std::wcout << inputStr;
    }

    std::wcout << L"Terminated...\n";

    return 0;
}