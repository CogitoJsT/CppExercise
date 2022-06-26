#include <cstdio>
#include <string>
#include <stack>

int main()
{
    //std::wcin.tie(nullptr);
    //std::ios_base::sync_with_stdio(false);

    int numOfSequence {0};
    //std::wcin >> numOfSequence;
    scanf("%d", &numOfSequence);

    std::stack<int> seqStack;
    std::string ans;
    ans.reserve(numOfSequence);
    for(int i = 1, j = 1; i <= numOfSequence; ++i)
    {
        int number {0};
        //std::wcin >> number;
        scanf("%d", &number);

        int count {0};
        if(number >= j)
        {
            while(number >= j)
            {
                seqStack.push(j++);
                ans.append("+\n");
            }
        }

        auto popNum = seqStack.top();
        if(popNum != number)
        {
            //std::wcout << L"NO\n";
            printf("NO\n");
            return 0;
        }
        seqStack.pop();
        ans.append("-\n");
    }

    //std::wcout << ans;
    printf("%s", ans.c_str());

    return 0;
}