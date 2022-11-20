/*********************************************************
 * author: Ran Aharon Cohen                              *
 * reviewer:                                         *
 * date: 19.09.22                                        *
 * file: logger impl'                                    *
 *********************************************************/
#include <ctime> // time_t

#include "logger.hpp" // logger api

namespace ilrd
{
    const std::string currentDateTime()
    {
        time_t now = time(0);
        struct tm tstruct;
        char buf[80];
        tstruct = *localtime(&now);
        strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);

        return buf;
    }

    class LogTask : public Task
    {
    public:
        LogTask(std::string path, const std::string log);
        void virtual operator()()
        {
            std::ofstream m_file;
            m_file.open(m_path.c_str(), std::fstream::in | std::fstream::app);
            m_file << m_log << std::endl;
            m_file.close();
        }
        virtual ~LogTask();

    private:
        std::string m_path;

        const std::string m_log;
    };

    LogTask::LogTask(std::string path, const std::string log) : m_path(path), m_log(log)
    {
        // empty
    }
    LogTask::~LogTask()
    {
        // empty
    }

    Logger::Logger(const std::string &path) : m_path(path), tp_log(1)
    {
        tp_log.Run();
    }

    void Logger::SetPath(const std::string &path)
    {
        std::rename(m_path.c_str(), path.c_str());
        m_path = path;
    }

    void Logger::Log(const std::string &log)
    {
        std::shared_ptr<Task> task(new LogTask(m_path, currentDateTime() + " " + log));
        tp_log.Add(task, PRIORITY::HIGH);
    }

}