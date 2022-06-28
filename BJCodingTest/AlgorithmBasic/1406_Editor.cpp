#include <iostream>
#include <string>


int main()
{
    std::wcin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::wstring inputString;
    inputString.reserve(100000);
    std::wcin >> inputString;

    int numOfCommands{0};
    std::wcin >> numOfCommands;

    auto cursorPos = inputString.length();
    for(int i = 0; i < numOfCommands; ++i)
    {
        wchar_t com0;
        std::wcin >> com0;
        if(com0 == L'P')
        {
            wchar_t com1;
            std::wcin >> com1;
            inputString.insert(cursorPos++, 1, com1);
        }

        if(com0 == L'L')
        {
            if(cursorPos > 0)
            {
                --cursorPos;
            }
        }
        else if(com0 == L'D')
        {
            if(cursorPos < inputString.length())
            {
                ++cursorPos;
            }
        }
        else if(com0 == L'B')
        {
            if(cursorPos > 0)
            {
                inputString.erase(cursorPos-1, 1);
                --cursorPos;
            }
        }
    }

    std::wcout << inputString + L"\n";

    return 0;
}