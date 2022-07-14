#include <iostream>
#include <string>
#include <vector>

void init()
{
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::ios_base::sync_with_stdio(false);
}

decltype(auto) split(std::string str)
{
    std::vector<std::string> strVec;

    while(true)
    {
        auto pos = str.find_first_of(' ');
        if(pos == std::string::npos)
        {
            strVec.push_back(str);
            break;
        }
        strVec.push_back(str.substr(0, pos));
        str = str.substr(pos+1); // + 1 to skip the space
    }

    return strVec;
}

int main()
{
    init();

    std::string inputStr;
    std::getline(std::cin, inputStr);

    auto splitStr = split(inputStr);

    auto num0 = splitStr[0] + splitStr[1];
    auto num1 = splitStr[2] + splitStr[3];

    auto sum = std::stoi(num0) + std::stoi(num1);
    std::cout << sum << "\n";

    return 0;
}