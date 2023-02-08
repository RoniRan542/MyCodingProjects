#include "mem_manager.hpp"

mem_manager::mem_manager(size_t total_bytes, size_t block_size)
    : m_pool(new char[(total_bytes / block_size) * block_size]),
      m_total_bytes((total_bytes / block_size) * block_size),
      m_block_size(block_size),
      m_is_free(std::vector<bool>(total_bytes / block_size))
{
    m_largest_free_space = {0, (m_total_bytes / block_size)};
}

char *mem_manager::Alloc(size_t bytes)
{
    size_t blocks = ceil(bytes / (double)m_block_size);

    if (m_largest_free_space.second >= blocks)
    {
        size_t index = 0;
        size_t counter = 0;

        while (index < m_is_free.size())
        {
            if (m_is_free[index] == false)
            {
                counter++;

                if (counter == blocks)
                {
                    break;
                }
            }
            else
            {
                counter = 0;
            }
            index++;
        }
        size_t start = index - (blocks - 1);
        for (size_t i = start; i < start + blocks; ++i)
        {
            m_is_free[i] = true;
        }
        m_index_size_map[start] = blocks;
        UpdateLargestChunk();

        return m_pool + (start * m_block_size);
    }

    throw std::runtime_error("not enaugh space\n");
}

void mem_manager::UpdateLargestChunk()
{
    size_t max = 0;
    size_t max_index = 0;
    size_t counter = 0;

    for (size_t i = 0; i < m_is_free.size(); ++i)
    {

        if (m_is_free[i] == false)
        {
            counter++;
        }

        if (m_is_free[i] == true || i == m_is_free.size() - 1)
        {
            if (counter > max)
            {
                max = counter;
                max_index = i - (counter - 1);
            }
            counter = 0;
        }
    }

    m_largest_free_space = {max_index, max};
}

size_t mem_manager::CountFreeBlocks()
{
    size_t counter = 0;

    for (size_t i = 0; i < m_is_free.size(); ++i)
    {
        counter += m_is_free[i] == false;
    }

    return counter;
}

bool mem_manager::Free(char *ptr)
{
    size_t index = ((size_t)ptr - (size_t)m_pool) / m_block_size;

    if (m_index_size_map.find(index) != m_index_size_map.end())
    {
        for (size_t i = index; i < index + m_index_size_map[index]; ++i)
        {
            m_is_free[i] = false;
        }

        m_index_size_map.erase(index);
        UpdateLargestChunk();

        return true;
    }
    else
    {
        return false;
    }
}

mem_manager::~mem_manager()
{
    delete[] m_pool;
}
