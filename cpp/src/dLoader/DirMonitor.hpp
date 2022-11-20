/* -------------------------------------------------------------------------- *
 * FILENAME      -    dir_monitor.hpp
 * ---------------------------------------------------------------------------*
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    20/10/22
 * ---------------------------------------------------------------------------*/

#ifndef __RD_12123_DIR_MONITOR_HPP__
#define __RD_12123_DIR_MONITOR_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

/* -------------------------------------------------------------------------- *
 *                          Includes
 * ---------------------------------------------------------------------------*/
#include <functional>

#include "DynamicLoader.hpp"

namespace ilrd
{
    class DirMonitor
    {
    public:
        explicit DirMonitor(std::string dir_path,
                            std::function<void(std::string, DllLoader &dll)> add_callback, DllLoader *dll);
        ~DirMonitor();
        DirMonitor(const DirMonitor &) = delete;
        DirMonitor(DirMonitor &&) = delete;
        const DirMonitor &operator=(const DirMonitor &) = delete;
        const DirMonitor &operator=(DirMonitor &&) = delete;
        void Run();

    private:
        void MonitorThread();
        std::function<void(std::string, DllLoader &dll)> m_callback;
        std::string m_dir_path;
        DllLoader *m_user_dll;
        std::thread m_thread;
        int m_fd;
        int m_wd;
        bool m_run;
    };
} // namespace ilrd

#endif //__RD_12123_DIR_MONITOR_HPP__