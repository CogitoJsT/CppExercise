#include <iostream>
#include <string>
#include <cctype>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    std::string inputStr;
    std::getline(std::cin, inputStr);

    std::string retString;
    for(auto ch : inputStr)
    {
        constexpr char AlphabetOffset = 26;
        if(std::isalpha(ch))
        {
            auto newCh = ch + 13;
            if(std::isupper(ch))
            {
                if(newCh > 0x5A)
                {
                    newCh -= AlphabetOffset;
                }
            }
            else
            {
                if(newCh > 0x7A)
                {
                    newCh -= AlphabetOffset;
                }
            }
            ch = newCh;
        }
        retString += ch;
    }

    std::cout << retString << "\n";

    return 0;
}