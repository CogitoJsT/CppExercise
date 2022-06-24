#include <iostream>

int main()
{
    std::wcin.tie(nullptr);
    std::ios_base::sync_with_stdio(false);

    int numOfCases{0};
    std::wcin >> numOfCases;

    for(int i = 0; i < numOfCases; ++i)
    {
        std::wstring inputStr;
        std::wcin >> inputStr;

        int count = 0;
        bool badPair = false;
        for(auto ch : inputStr)
        {
            if(ch == '(')
            {
                ++count;
            }
            else if(ch == ')')
            {
                --count;
            }

            // Check bad order, ")("
            if(count < 0)
            {
                badPair = true;
                break;
            }
        }

        if(count == 0 && !badPair)
        {
            std::wcout << L"YES\n";
        }
        else
        {
            std::wcout << L"NO\n";
        }
    }

    return 0;
}