
#include <iostream>

using namespace std;

void ReverseWord(string &sentence, int begin, int end)
{
    while (begin < end)
    {
        swap(sentence[begin], sentence[end]);
        begin++;
        end--;
    }
}

void reverseWords(string &sentence)
{
    ReverseWord(sentence, 0, sentence.length() - 1);
    int begin = 0;
    for (int i = 0; i < sentence.length(); ++i)
    {
        if (sentence[i] == ' ')
        {
            ReverseWord(sentence, begin, i - 1);
            begin = i + 1;
        }
    }

    if (begin < sentence.length())
    {
        ReverseWord(sentence, begin, sentence.length() - 1);
    }
}

int main()
{
    string mystr = "my name  is Ran, I am 37 years old";

    reverseWords(mystr);

    cout << mystr << endl;

    return 0;
}
