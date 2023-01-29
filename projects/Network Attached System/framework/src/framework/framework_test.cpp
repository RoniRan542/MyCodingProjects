#include <iostream>

#include "framework.hpp"
#include "fw_io.hpp"

using namespace std;
using namespace ilrd;

int main()
{
    Framework<InputMaster, OutputMaster> fw;
    fw.Run();

    return 0;
}
