#include <iostream>
#include <cstring>

using namespace std;

class TrieNode
{
public:
    TrieNode(bool is_word = false) : m_is_word(is_word)
    {
        memset(m_next, nullptr, sizeof(m_next));
    }

    TrieNode *m_next[26];
    bool m_is_word;
};

class Trie
{
public:
    Trie()
    {
        root = new TrieNode();
    }

    void insert(string word)
    {
        TrieNode *node = root;

        for (size_t i = 0; i < word.size(); ++i)
        {
            if (node->m_next[word[i] - 'a'] == nullptr)
            {
                node->m_next[word[i] - 'a'] = new TrieNode();
                node = node->m_next[word[i] - 'a'];
            }
        }
        node->m_is_word = true;
    }

    bool Sreach(string key)
    {
        TrieNode *node = find(key);

        return (node != nullptr) && (node->m_is_word == true);
    }

    bool StartsWith(string prefix)
    {
        return find(prefix) != nullptr;
    }

private:
    TrieNode *find(string key)
    {
        TrieNode *node = root;
        for (size_t i = 0; i < key.size() && node != nullptr; ++i)
        {
            node = node->m_next[key[i] - 'a'];
        }

        return node;
    }
    TrieNode *root;
};
