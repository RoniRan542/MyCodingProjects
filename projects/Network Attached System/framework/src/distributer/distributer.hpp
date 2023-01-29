/* -------------------------------------------------------------------------- *
 * FILENAME      -    distributer.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    27/11/22
 * -------------------------------------------------------------------------- */

#ifndef __DISTRIBUTER_HPP__
#define __DISTRIBUTER_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <iostream>

namespace ilrd
{
    class Distributer
    {
    public:
        Distributer(std::size_t (*func)(char *str));
        std::size_t GetUid(char *path);
        ~Distributer();

    private:
        std::size_t (*GetHashUid)(char *path);
    };

}

#endif /* __DISTRIBUTER_HPP__*/