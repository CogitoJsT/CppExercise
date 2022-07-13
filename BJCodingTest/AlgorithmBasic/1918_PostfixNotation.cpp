#include <iostream>
#include <string>
#include <stack>
#include <cctype>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

int main()
{
    init();

    std::string inputStr;
    std::cin >> inputStr;

    std::string retString;
    std::stack<char> st;
    for (auto ch : inputStr)
    {
        if (std::isalpha(static_cast<int>(ch)))
        {
            retString += ch;
        }
        else
        {
            if (ch == '(')
            {
                st.push(ch);
            }
            else if (ch == ')')
            {
                while (true)
                {
                    auto top = st.top();
                    st.pop();
                    if (top == '(')
                    {
                        break;
                    }
                    else
                    {
                        retString += top;
                    }
                }
            }
            else
            {
                auto isOperator = [](char ch, char op0, char op1) { return ch == op0 || ch == op1; };
                char top;
                while (true)
                {
                    if (st.empty())
                    {
                        break;
                    }
                    top = st.top();
                    if ((isOperator(ch, '*', '/') && isOperator(top, '+', '-')) || top == '(')
                    {
                        break;
                    }
                    st.pop();
                    retString += top;
                }
                st.push(ch);
            }
        }
    }

    while (!st.empty())
    {
        retString += st.top();
        st.pop();
    }

    std::cout << retString << "\n";

    return 0;
}
