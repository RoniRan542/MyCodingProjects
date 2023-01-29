#include <cstring>
#include "uid.hpp"

namespace ilrd
{
    u_int64_t UID::m_counter = 0;

    UID::UID()
    {
        std::lock_guard<std::mutex> lock(m_mutex);
        m_my_counter = m_counter;
        ++m_counter;
        m_time = std::chrono::system_clock::now();
    }

    UID::UID(const UID &other)
    {
        m_my_counter = other.m_my_counter;
        m_time = other.m_time;
    }

    UID &UID::operator=(const UID &other)
    {
        m_my_counter = other.m_my_counter;
        m_time = other.m_time;
        return (*this);
    }

    void UID::Serialize(char *buffer)
    {
        memcpy(buffer, (char *)&m_my_counter, sizeof(m_my_counter));
        buffer += sizeof(m_my_counter);
        memcpy(buffer, (char *)&m_time, sizeof(m_time));
        buffer += sizeof(m_time);
    }

    void UID::Deserialize(char *buffer)
    {
        memcpy((char *)&m_my_counter, buffer, sizeof(m_my_counter));
        buffer += sizeof(m_my_counter);
        memcpy((char *)&m_time, buffer, sizeof(m_time));
        buffer += sizeof(m_time);
    }

    u_int64_t UID::GetCounter() const
    {
        return (m_my_counter);
    }

    std::chrono::time_point<std::chrono::system_clock> UID::GetTime()
    {
        return (m_time);
    }

    bool operator<(UID uid1, UID uid2)
    {
        return ((uid1.m_my_counter < uid2.m_my_counter));
    }
}