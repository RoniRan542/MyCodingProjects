#include <iostream>
#include <dlfcn.h>
#include "base.hpp"
#include "handleton.hpp"

using namespace ilrd;
using func = void (*)(void);
using func2 = Base *(*)(void);

int main()
{
    void *handle = dlopen("./libshared.so", RTLD_NOW);
    char *errstr;

    errstr = dlerror();
    if (errstr != NULL)
    {
        printf("A dynamic linking error occurred: (%s)\n", errstr);
    }
    func f = (func)dlsym(handle, "_Z3foov");
    func2 f2 = (func2)dlsym(handle, "_ZN4ilrd9HandletonI4BaseE11GetInstanceEv");

    f();
    std::cout << f2() << std::endl;

    return 0;
}
