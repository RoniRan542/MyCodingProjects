#include <iostream>
#include <vector>

std::string longestCommonPrefix(std::vector<std::string> &strs)
{
    std::string output;
    std::string temp = strs[0];
    size_t to_fit = temp.size();
    for (auto const str : strs)
    {
        size_t i = 0;
        for (; i < to_fit; ++i)
        {
            if (temp[i] == str[i])
            {
            }
            else
            {
                break;
            }
        }
        to_fit = i;
    }

    for (size_t i = 0; i < to_fit; ++i)
    {
        output += temp[i];
    }

    return output;
}

int main()
{
    std::vector<std::string> strs = {"abagada", "abagir", "abagggg", "abass"};

    std::cout << longestCommonPrefix(strs) << std::endl;
    return 0;
}