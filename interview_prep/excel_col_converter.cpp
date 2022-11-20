#include <iostream>
#include <unordered_map>
#include <vector>
static const int base = 26;
void InitLut(std::unordered_map<int, char> &lut)
{
    char start = 'A';
    for (size_t i = 0; i < 26; i++)
    {
        lut[i + 1] = static_cast<char>(start + i);
    }
}

std::string convertToTitle(int columnNumber)
{
    std::unordered_map<int, char> lut;
    InitLut(lut);
    std::string output;
    std::vector<char> chars;
    if (columnNumber < base + 1)
    {
        return output += lut[columnNumber];
    }

    while (columnNumber > base)
    {
        chars.push_back(lut[columnNumber % base]);
        columnNumber /= base;
        chars.push_back(lut[columnNumber]);
    }

    for (int i = chars.size() - 1; i >= 0; --i)
    {
        output += chars[i];
    }

    return output;
}

std::string convertToTitle2(int columnNumber)
{
    char tmp;

    std::string res = "";

    while (columnNumber)
    {
        columnNumber -= 1;

        tmp = 'A' + columnNumber % 26;

        res = tmp + res;

        columnNumber /= 26;
    }

    return res;
}

int main()
{
    std::cout << convertToTitle(70) << std::endl;
    std::cout << convertToTitle(701) << std::endl;
    std::cout << convertToTitle(770) << std::endl;
    std::cout << convertToTitle(2147483647) << std::endl;

    std::cout << "\n"
              << std::endl;
    std::cout << convertToTitle2(701) << std::endl;
    std::cout << convertToTitle2(770) << std::endl;
    std::cout << convertToTitle2(2147483647) << std::endl;
    return 0;
}