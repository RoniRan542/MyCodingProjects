/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer: Roee                                        *
 * date: 19.09.22                                        *
 * file: logger API                                      *
 *********************************************************/
#ifndef __RD12123_LOGGER_HPP__
#define __RD12123_LOGGER_HPP__

#include <iostream> // for string
#include <fstream>  // for file handling

#include "handleton.hpp"   // Handleton API
#include "thread_pool.hpp" // thread-pool API

namespace ilrd
{
    class Logger
    {
    public:
        void SetPath(const std::string &path);
        void Log(const std::string &log);

    private:
        Logger(const std::string &path = "./logger.txt");
        friend class Handleton<Logger>;

        std::string m_path;
        ThreadPool tp_log;
        // std::mutex m_mutex;
    };

}

#endif //__RD12123_LOGGER_HPP__