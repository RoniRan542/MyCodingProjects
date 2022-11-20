#include <iostream>
#include <dlfcn.h>
#include <exception>

#include "DynamicLoader.hpp"

namespace ilrd
{
    DllLoader::DllLoader()
    {
        // empty
    }

    void DllLoader::AddDll(std::string dll_name)
    {

        void *handle = dlopen(dll_name.c_str(), RTLD_NOW);
        char *errstr;

        errstr = dlerror();
        if (errstr != NULL)
        {
            printf("A dynamic linking error occurred: (%s)\n", errstr);
        }

        if (NULL == handle)
        {
            throw new std::runtime_error(std::string("dlopen error\n"));
        }

        m_handles.push_back(handle);
    }

    DllLoader::~DllLoader()
    {
        while (!m_handles.empty())
        {
            dlclose(m_handles.back());
            m_handles.pop_back();
        }
    }
}