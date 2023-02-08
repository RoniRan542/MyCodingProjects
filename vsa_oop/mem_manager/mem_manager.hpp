#ifndef __MEM_MANAGER__
#define __MEM_MANAGER__
#include <string>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <exception>
#include <cmath>

class mem_manager
{
public:
    explicit mem_manager(size_t total_bytes, size_t block_size);
    char *Alloc(size_t bytes);
    bool Free(char *ptr);
    void UpdateLargestChunk();
    size_t CountFreeBlocks();
    ~mem_manager();

private:
    char *m_pool;
    size_t m_total_bytes;
    size_t m_block_size;
    std::pair<size_t, size_t> m_largest_free_space;
    std::unordered_map<size_t, size_t> m_index_size_map;
    std::vector<bool> m_is_free;
};

#endif //__MEM_MANAGER__