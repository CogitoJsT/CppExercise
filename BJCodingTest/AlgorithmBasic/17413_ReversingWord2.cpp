#include <iostream>
#include <string>
#include <stack>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    std::string inputString;
    std::getline(std::cin, inputString);

    auto getStringFromStack = [](std::stack<char> &st)
    {
        std::string result;
        while(!st.empty())
        {
            result += st.top();
            st.pop();
        }
        return result;
    };

    bool isTagWord{ false };
    std::stack<char> revWord;
    std::string resultString;

    for(auto ch : inputString)
    {
        if ((ch == ' ' || ch == '<') && isTagWord == false)
        {
            resultString += getStringFromStack(revWord);
            if( ch == '<')
            {
                isTagWord = true;
            }
            resultString += ch;
        }
        else if (ch == '>')
        {
            isTagWord = false;
            resultString += ch;
        }
        else
        {
            if (isTagWord)
            {
                resultString += ch;
            }
            else
            {
                revWord.push(ch);
            }
        }
    }

    if(!revWord.empty())
    {
        resultString += getStringFromStack(revWord);
    }

    std::cout << resultString << "\n";

    return 0;
}