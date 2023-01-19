/*
create an infrastructure for allocation of memory. the api functions are myinit, my mymalloc, myfree.
my init will recieve a buff size per buff (fixed size), and number of buffers.
 */
#include <iostream>

using namespace std;

struct fsa_offset
{
    size_t offset;
};

template <typename T>
class fsaMemory
{
public:
    fsaMemory(size_t buffSize, size_t numBuffers);

    char *myMalloc(size_t bum_of_buffers)
    {
        return (char *)m_fsa_pool;
    }

    void myFree(void *to_free)
    {
    }
    ~fsaMemory();

private:
    char *m_fsa_pool;
    size_t m_nblocks;
    size_t m_block_size;
};

fsaMemory::fsaMemory(size_t buffSize, size_t numBuffers)
    : m_fsa_pool(new char(numBuffers * buffSize)), m_nblocks(numBuffers), m_block_size(buffSize)
{
    // empty
}

fsaMemory::~fsaMemory()
{
    delete[] m_fsa_pool;
}

int main()
{
    fsaMemory pool(8, 10);
    return 0;
}
