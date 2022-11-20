#ifndef __ILRD_RD12123_TREE_HPP__
#define __ILRD_RD12123_TREE_HPP__

#include "directory.hpp"

namespace ilrd
{
    class Tree
    {
    public:
        Tree(const std::string &path); // constructor
        ~Tree() noexcept;              // destructor
        void Display();

    private:
        Directory *const m_root;
    };
}

#endif //__ILRD_RD12123_TREE_HPP__
