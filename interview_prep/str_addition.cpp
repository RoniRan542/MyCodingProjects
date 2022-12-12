#include <iostream>

std::string CreateStringZeros(size_t len)
{
    std::string result;

    while (len)
    {
        result += '0';
        --len;
    }

    return result;
}

std::string AddLargeNumbers(std::string num1, std::string num2)
{
    std::string result = "";
    int bigger = num1.length() > num2.length();
    if (bigger)
    {
        num2 = CreateStringZeros(num1.length() - num2.length()) + num2;
    }
    else
    {
        num1 = CreateStringZeros(num2.length() - num1.length()) + num1;
    }

    std::cout << num1 << std::endl;
    std::cout << num2 << std::endl;

    int carry = 0;
    for (int i = num1.length() - 1; i >= 0; --i)
    {
        int dig1 = num1[i] - '0';
        int dig2 = num2[i] - '0';
        int res = dig1 + dig2 + carry;
        if (10 <= res)
        {
            res %= 10;
            carry = 1;
        }
        else
        {
            carry = 0;
        }

        result.insert(result.begin(), res + '0');
    }

    return result;
}

int main()
{
    std::string n1 = "150";
    std::string n2 = "5450";

    std::cout << AddLargeNumbers(n1, n2) << std::endl;

    return 0;
}