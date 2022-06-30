#include <iostream>
#include <string>
#include <list>

int main()
{
    std::wcin.tie(nullptr);
    std::wcout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    std::wstring inputString;
    inputString.reserve(100000);
    std::wcin >> inputString;

    std::list<wchar_t> strList;
    strList.assign(inputString.begin(), inputString.end());

    int numOfCommands{0};
    std::wcin >> numOfCommands;

    auto curIt = strList.end();
    for(int i = 0; i < numOfCommands; ++i)
    {
        wchar_t com0;
        std::wcin >> com0;
        if(com0 == L'P')
        {
            wchar_t com1;
            std::wcin >> com1;
            curIt = strList.insert(curIt, com1);
            curIt++;
        }

        else if(com0 == L'L')
        {
            if(curIt != strList.begin())
            {
                curIt--;
            }
        }
        else if(com0 == L'D')
        {
            if(curIt != strList.end())
            {
                curIt++;
            }
        }
        else if(com0 == L'B')
        {
            if(curIt != strList.begin())
            {
                curIt = strList.erase(--curIt);
            }
        }
    }

    for(auto elem : strList)
    {
        std::wcout << elem;
    }
    std::wcout << L"\n";

    return 0;
}