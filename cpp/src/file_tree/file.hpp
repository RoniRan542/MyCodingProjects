#ifndef __ILRD_RD12123_FILE_HPP__
#define __ILRD_RD12123_FILE_HPP__

#include <cstddef>

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

namespace ilrd
{
    class File
    {
    public:
        virtual ~File() noexcept;                   // destructor
        virtual void print(size_t indents = 0) = 0; // pure virtual print
    };
}

#endif //__ILRD_RD12123_FILE_HPP__
