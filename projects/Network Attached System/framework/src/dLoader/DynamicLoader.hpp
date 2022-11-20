/* -------------------------------------------------------------------------- *
 * FILENAME      -    dll_loader.hpp
 * ---------------------------------------------------------------------------*
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    20/10/22
 * ---------------------------------------------------------------------------*/

#ifndef __RD_12123_DLL_LOADER_HPP__
#define __RD_12123_DLL_LOADER_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

/* -------------------------------------------------------------------------- *
 *                          Includes
 * ---------------------------------------------------------------------------*/
#include <string>
#include <vector>
#include <memory>

namespace ilrd
{
    class DllLoader
    {
    public:
        explicit DllLoader();
        ~DllLoader();

        DllLoader(const DllLoader &) = delete;
        DllLoader(DllLoader &&) = delete;
        const DllLoader &operator=(const DllLoader &) = delete;
        const DllLoader &operator=(DllLoader &&) = delete;

        void AddDll(std::string dll_name);

    private:
        std::vector<void *> m_handles;
    };
} // namespace ilrd

#endif //__RD_12123_DLL_LOADER_HPP__