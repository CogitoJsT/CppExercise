#include <iostream>
#include <string>
#include <stack>

constexpr int BraceStart = 0;

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
    std::cin >> inputString;

    std::stack<int> st;
    auto totalSum{ 0L };
    auto prev_ch{ '(' };
    for (auto ch : inputString)
    {
        if (ch == '(')
        {
            st.push(BraceStart);
        }
        else if (ch == ')')
        {
            if (prev_ch == '(')
            {
                st.pop();
                st.push(1);
            }
            else
            {
                auto sum{ 0 };
                while (true)
                {
                    auto data = st.top();
                    st.pop();
                    if (data == BraceStart)
                    {
                        st.push(sum);
                        break;
                    }
                    sum += data;
                }
                totalSum += (sum + 1);
            }
        }
        prev_ch = ch;
    }

    std::cout << totalSum << "\n";

    return 0;
}