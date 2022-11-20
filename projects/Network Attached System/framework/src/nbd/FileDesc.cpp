
#include <climits>
#include "FileDesc.hpp"

namespace ilrd
{
    static void DeleteRef(int *p_fd, size_t *p_cref);

    FileDesc::FileDesc(int fd) : m_fd(fd), m_cref(new size_t(1))
    {
        // empry
    }

    FileDesc::FileDesc(const FileDesc &other) noexcept
    {
        m_fd = other.m_fd;
        m_cref = other.m_cref;

        *m_cref += 1;
    }

    const FileDesc &FileDesc::operator=(const FileDesc &other) noexcept
    {
        DeleteRef(&m_fd, m_cref);

        m_fd = other.m_fd;
        m_cref = other.m_cref;

        *m_cref += 1;

        return *this;
    }

    int FileDesc::GetFd() const noexcept
    {
        return m_fd;
    }

    FileDesc::~FileDesc() noexcept
    {
        DeleteRef(&m_fd, m_cref);
    }

    static void DeleteRef(int *p_fd, size_t *p_cref)
    {
        if (*p_cref == 1)
        {
            close(*p_fd);
            *p_fd = INT32_MAX;
            delete p_cref;
            p_cref = 0;
        }
        else
        {
            *p_cref -= 1;
        }
    }
}