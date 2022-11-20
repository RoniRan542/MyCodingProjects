#include <boost/thread/mutex.hpp>
#include "scopelock.hpp"

using namespace ilrd;

int main()
{
    boost::mutex mutex;
    ilrd::ScopeLock<boost::mutex> Slock(mutex);
    Slock.~ScopeLock();
    return 0;
}
