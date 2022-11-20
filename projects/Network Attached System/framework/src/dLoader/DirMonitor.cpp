#include <sys/inotify.h> //inotify
#include <exception>     //exception
#include <iostream>      // std API
#include <unistd.h>      //read
#include <cstring>       //memcpy
#include <thread>        // thread API
#include <poll.h>        //poll

#include "DirMonitor.hpp"

static const size_t event_size = sizeof(struct inotify_event);
static const size_t event_buf_len = 1024 * (event_size + 16);

namespace ilrd
{
    bool pollIn(int fd)
    {
        bool returnValue{false};
        struct pollfd pfd;
        pfd.fd = fd;
        pfd.events = POLLIN;

        int pollReturn{-1};
        pollReturn = poll(&pfd, 1, 0);

        if (pollReturn > 0)
        {
            if (pfd.revents & POLLIN)
            {
                returnValue = true;
            }
        }
        return (returnValue);
    }

    DirMonitor::DirMonitor(std::string dir_path,
                           std::function<void(std::string, DllLoader &dll)> add_callback, DllLoader *dll_loader)
        : m_callback(add_callback),
          m_dir_path(dir_path),
          m_user_dll(dll_loader),
          m_fd(0),
          m_wd(0),
          m_run(false)
    {
        m_fd = inotify_init();
        if (m_fd < 0)
        {
            std::cerr << "error init" << '\n';
        }
    }

    void DirMonitor::Run()
    {
        m_wd = inotify_add_watch(m_fd, m_dir_path.c_str(), IN_MOVED_TO);
        m_thread = std::thread(&DirMonitor::MonitorThread, this);
    }

    void DirMonitor::MonitorThread()
    {
        char buffer[event_buf_len];
        m_run = true;
        while (m_run == true)
        {
            int length, i = 0;
            std::this_thread::sleep_for(std::chrono::seconds(1));
            if (pollIn(m_fd))
            {
                length = read(m_fd, buffer, event_buf_len);
                if (length < 0)
                {
                    std::cerr << "error read" << '\n';
                }

                while (i < length)
                {
                    struct inotify_event *event = (struct inotify_event *)&buffer[i];
                    if (event->len)
                    {
                        if (event->mask & IN_MOVED_TO)
                        {
                            std::string so_path(m_dir_path);
                            // so_path += "/";
                            so_path += event->name;
                            m_callback(std::string(so_path), *m_user_dll);
                        }
                    }
                    i += event_size + event->len;
                }
            }
        }
    }

    DirMonitor::~DirMonitor()
    {
        m_run = false;
        m_thread.join();
        inotify_rm_watch(m_fd, m_wd);
        close(m_fd);
    }
}