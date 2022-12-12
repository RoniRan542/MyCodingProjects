#include <iostream>
#include <list>

using namespace std;

string ReverseWords(string str)
{
    string res;
    size_t word_start = 0;
    list<string> word_box;
    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
        {
            string temp_str = str.substr(word_start, (i - word_start));
            word_box.push_front(temp_str);
            word_start = i + 1;
        }

        if (i == str.length() - 1)
        {
            string temp_str = str.substr(word_start, (i + 1 - word_start));
            word_box.push_front(temp_str);
        }
    }

    list<string>::iterator word_box_it = word_box.begin();
    res += *word_box_it;
    ++word_box_it;
    for (; word_box_it != word_box.end(); ++word_box_it)
    {
        res += ',';
        res += *word_box_it;
    }

    return res;
}

int main()
{
    string intro = "my name is ran";
    cout << ReverseWords(intro) << endl;

    return 0;
}