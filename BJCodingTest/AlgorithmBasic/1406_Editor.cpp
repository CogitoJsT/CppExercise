#include <iostream>
#include <string>
#include <vector>


int main()
{
    std::wcin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::wstring inputString;
    inputString.reserve(100000);
    std::wcin >> inputString;

    std::vector<wchar_t> stringVector;
    stringVector.reserve(100000);
    for(auto ch : inputString)
    {
        stringVector.push_back(ch);
    }

    int numOfCommands{0};
    std::wcin >> numOfCommands;

    //auto cursorPos = inputString.length();
    auto cursorPos = stringVector.size();
    for(int i = 0; i < numOfCommands; ++i)
    {
        wchar_t com0;
        std::wcin >> com0;
        if(com0 == L'P')
        {
            wchar_t com1;
            std::wcin >> com1;
            //inputString.insert(cursorPos++, 1, com1);
            stringVector.insert(stringVector.begin() + cursorPos++, com1);
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
            //if(cursorPos < inputString.length())
            if(cursorPos < stringVector.size())
            {
                ++cursorPos;
            }
        }
        else if(com0 == L'B')
        {
            if(cursorPos > 0)
            {
                //inputString.erase(cursorPos-1, 1);
                stringVector.erase(stringVector.begin() + cursorPos-1);
                --cursorPos;
            }
        }
    }

    //std::wcout << inputString + L"\n";
    for(auto elem : stringVector)
    {
        std::wcout << elem;
    }
    std::wcout << L"\n";

    return 0;
}