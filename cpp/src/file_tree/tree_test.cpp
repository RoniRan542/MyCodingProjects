#include <iostream>
#include <cstring>

#include "file_tree.hpp"

using namespace std;
using namespace ilrd;

enum status
{
    SUCCESS,
    FAILURE
};

int main()
{
    int result = SUCCESS;
    Tree t("/home/rani/git/cpp/src/");
    t.Display();

    return result;
}
