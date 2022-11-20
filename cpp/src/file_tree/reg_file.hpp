#ifndef __ILRD_RD12123_REG_FILE_HPP__
#define __ILRD_RD12123_REG_FILE_HPP__

#include <string>

#include "file.hpp"

namespace ilrd
{
    class Reg_File : public File
    {
    public:
        Reg_File(const std::string &name); // constructor
        ~Reg_File() noexcept;              // destructor
        void print(size_t indents = 0);

    private:
        std::string m_name;
    };
}

#endif //__ILRD_RD12123_REG_FILE_HPP__
