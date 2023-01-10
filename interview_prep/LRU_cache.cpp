#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

typedef struct data
{
    list<string>::iterator it;
    int value;
} data_t;

class LRUCache
{
public:
    LRUCache(size_t capacity);
    void Put(const string &key, int value);
    int GetLRU(const string &key);

private:
    list<string>::iterator MoveFront(list<string>::iterator it);
    size_t capacity_;
    unordered_map<string, data_t> hash_;
    list<string> cache_;
    size_t size_;
};

LRUCache::LRUCache(size_t capacity) : capacity_(capacity), size_(0)
{
    // empty
}

list<string>::iterator LRUCache::MoveFront(list<string>::iterator it)
{
    string tmp = *it;
    cache_.erase(it);

    return cache_.insert(cache_.begin(), tmp);
}

int LRUCache::GetLRU(const string &key)
{
    if (hash_.find(key) == hash_.end())
    {
        return -1;
    }
    MoveFront(hash_[key].it);

    return hash_[key].value;
}

void LRUCache::Put(const string &key, int value)
{

    if (hash_.find(key) != hash_.end())
    {
        hash_[key].value = value;
        MoveFront(hash_[key].it);
    }
    else if (size_ < capacity_)
    {
        ++size_;
        hash_[key] = {cache_.insert(cache_.begin(), key), value};
    }
    else
    {
        hash_.erase(cache_.back());
        cache_.pop_back();
        hash_[key] = {cache_.insert(cache_.begin(), key), value};
    }
}

int main()
{
    LRUCache cache(5);
    cache.Put("test1", 1);
    cache.Put("test2", 2);
    cache.Put("test3", 3);
    cache.Put("test4", 4);
    cache.Put("test5", 5);

    cache.GetLRU("test1");
    cache.GetLRU("test2");
    cache.GetLRU("test3");
    cache.GetLRU("test4");
    cache.Put("test6", 6);

    cout << cache.GetLRU("test1") << endl;
    cout << cache.GetLRU("test2") << endl;
    cout << cache.GetLRU("test3") << endl;
    cout << cache.GetLRU("test4") << endl;
    cout << cache.GetLRU("test5") << endl;
    cout << cache.GetLRU("test6") << endl;

    return 0;
}
