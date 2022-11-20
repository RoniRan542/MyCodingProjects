#include <iostream>
#include "handleton.hpp"
#include "base.hpp"

using namespace ilrd;

void foo()
{

    Base *b = Handleton<Base>::GetInstance();

    std::cout << "shared: " << b << std::endl;
}
