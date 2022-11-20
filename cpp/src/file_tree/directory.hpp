#ifndef __ILRD_RD12123_DIRECTORY_HPP__
#define __ILRD_RD12123_DIRECTORY_HPP__

#include <string>
#include <list>

#include "file.hpp"

namespace ilrd
{
    class Directory : public File
    {
    public:
        Directory(const std::string &path); // constructor
        ~Directory() noexcept;              // destructor
        void print(size_t indents = 0);

    private:
        std::string m_name;
        std::list<File *> m_dir_files;
    };
}

#endif //__ILRD_RD12123_DIRECTORY_HPP__
