/* -------------------------------------------------------------------------- *
 * FILENAME      -    uid.hpp
 * -------------------------------------------------------------------------- *
 * AUTHOR        -
 * STATUS        -    not tested
 * REVIEWER      -
 * DATE          -    25/12/22
 * -------------------------------------------------------------------------- */

#ifndef __UID_HPP__
#define __UID_HPP__

#if __cplusplus <= (199711L)
#define noexcept throw()
#define nullptr 0
#endif

#include <chrono>
#include <mutex>
#include <unistd.h>

namespace ilrd
{
    class UID
    {
    public:
        UID();
        UID(const UID &other);
        UID &operator=(const UID &other);
        // bool operator<(const UID & uid2) const;
        void Serialize(char *buffer);
        void Deserialize(char *buffer);
        u_int64_t GetCounter() const;
        std::chrono::time_point<std::chrono::high_resolution_clock> GetTime();
        friend bool operator<(UID uid1, UID uid2);

    private:
        static u_int64_t m_counter;
        u_int64_t m_my_counter;
        std::chrono::time_point<std::chrono::high_resolution_clock> m_time;
        std::mutex m_mutex;
    };
}

#endif //__UID_HPP__