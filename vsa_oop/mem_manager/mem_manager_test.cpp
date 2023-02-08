#include "mem_manager.hpp"

int main()
{
    mem_manager poolManager(120, 8);
    std::cout << poolManager.CountFreeBlocks() << std::endl;
    char *ptr1 = poolManager.Alloc(20);
    char *ptr2 = poolManager.Alloc(20);
    char *ptr3 = poolManager.Alloc(20);
    char *ptr4 = poolManager.Alloc(20);
    char *ptr5 = poolManager.Alloc(20);
    std::cout << poolManager.CountFreeBlocks() << std::endl;
    std::cout << poolManager.Free(ptr1) << std::endl;
    std::cout << poolManager.Free(ptr2) << std::endl;
    std::cout << poolManager.Free(ptr3) << std::endl;
    std::cout << poolManager.CountFreeBlocks() << std::endl;
    std::cout << poolManager.Free(ptr4) << std::endl;
    std::cout << poolManager.Free(ptr5) << std::endl;
    std::cout << poolManager.CountFreeBlocks() << std::endl;

    return 0;
}
