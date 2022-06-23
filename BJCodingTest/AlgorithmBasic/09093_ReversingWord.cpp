
#include <iostream>
#include <string>
#include <stack>
#include <cstdio>

void reversingWord(std::wstring str)
{
    std::stack<wchar_t> charStack;
    bool hasSpace = false;

    for (auto ch : str)
    {
        if (ch != L' ')
        {
            charStack.push(ch);
        }
        else
        {
            if (hasSpace)
                std::wcout << L" ";
            while (!charStack.empty())
            {
                std::wcout << charStack.top();
                charStack.pop();
            }
            hasSpace = true;
        }
    }
    std::wcout << L"\n";

}

int main()
{
    std::wcin.tie(NULL);
    std::ios_base::sync_with_stdio(false);

    int numOfStrings{ 0 };
    std::wstring temp;
    std::wcin >> numOfStrings;
    std::getline(std::wcin, temp);

    for (int i = 0; i < numOfStrings; ++i)
    {
        std::wstring inputString;
        std::getline(std::wcin, inputString);

        inputString += L" ";
        reversingWord(inputString);
    }

    return 0;
}
