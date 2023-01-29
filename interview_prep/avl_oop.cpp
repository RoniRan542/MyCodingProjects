#include <cstddef>
#include <functional>
#include <cstdlib>
#include <iostream>

#define MAX(x, y) ((x) > (y) ? (x) : (y))

enum ChildrenSide
{
    LEFT,
    RIGHT
};

template <typename T>
struct node
{
    T val;
    size_t height;               // height
    struct node<T> *children[2]; // children
};

template <typename T>
using node_t = struct node;

void BalanceTree();
template <typename T>
void DeleteTree(node_t<T> *root);
template <typename T>
void Count(node_t<T> *root, std::size_t *counter);
template <typename T>
bool FindRec(node_t<T> *root, T val);
template <typename T>
bool InsertRecursively(node_t<T> **root, std::function<bool(T, T, T)> cmp, T param, T val);
template <typename T>
void RotateRight(node_t<T> *root);
template <typename T>
void RotateLeft(node_t<T> *root);
template <typename T>
void RotateLeftRight(node_t<T> *root);
template <typename T>
void RotateRightLeft(node_t<T> *root);

template <typename T>
class avl_tree
{
public:
    avl_tree(std::function<bool(T, T, T)> cmp, T param);
    ~avl_tree();
    bool Insert(T val);
    bool Remove(T val);
    std::size_t Size() const;
    bool IsEmpty() const;
    bool Find(T val) const;
    bool ForEach(std::function<bool> func, T param);

private:
    struct node<T> *m_root; // root node
    std::function<bool(T, T, T)> m_cmp;
    T m_param;
};

template <typename T>
avl_tree<T>::avl_tree(std::function<bool(T, T, T)> cmp, T param)
    : m_root(nullptr), m_cmp(cmp), m_param(param)
{
    // empty
}

template <typename T>
avl_tree<T>::~avl_tree()
{
    DeleteTree(m_root);
}

template <typename T>
bool avl_tree<T>::Insert(T val)
{
    return InsertRecursively(&m_root, m_cmp, m_param, val);
}

template <typename T>
bool InsertRecursively(node_t<T> **root, std::function<bool(T, T, T)> cmp, T param, T val)
{

    if (*root == nullptr)
    {
        (*root) = new node_t<T>;
        (*root)->val = val;
        (*root)->height = 1;
        return true;
    }

    bool retval = false;
    if (cmp(val, (*root)->val, param))
    {
        retval = InsertRecursively(&((*root)->children[RIGHT]), cmp, param, val);
    }
    else
    {
        retval = InsertRecursively(&((*root)->children[RIGHT]), cmp, param, val);
    }
    (*root)->height = MAX(GetHeight((*root)->children[RIGHT]), GetHeight((*root)->children[LEFT])) + 1;

    int balance = GetBalance(*root);
    if (balance > 1) // left heavy
    {
        if (GetBalance((*root)->children[LEFT]) >= 1)
        {
            RotateRight((*root)->children[LEFT]);
        }
        else
        {
            RotateLeftRight((*root)->children[LEFT]);
        }
    }
    else if (balance < -1) // right heavy
    {
        if (GetBalance((*root)->children[RIGHT]) <= 0)
        {
            RotateLeft((*root)->children[RIGHT]);
        }
        else
        {
            RotateRightLeft((*root)->children[RIGHT]);
        }
    }
    (*root)->height = MAX(GetHeight((*root)->children[RIGHT]), GetHeight((*root)->children[LEFT])) + 1;

    return retval;
}

template <typename T>
void RotateRight(node_t<T> *root)
{
    std::cout << "root " << root << std::endl;
    node_t<T> *new_root = root->children[LEFT];
    new_root->children[RIGHT] = root;
    root->children[LEFT] = nullptr;
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;
}

template <typename T>
void RotateLeft(node_t<T> *root)
{
    node_t<T> *new_root = root->children[RIGHT];
    new_root->children[LEFT] = root;
    root->children[RIGHT] = nullptr;
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;
}

template <typename T>
void RotateLeftRight(node_t<T> *root)
{
    RotateLeft(root->children[RIGHT]);
    RotateRight(root);
}

template <typename T>
void RotateRightLeft(node_t<T> *root)
{
    RotateRight(root->children[LEFT]);
    RotateLeft(root);
}

template <typename T>
int GetBalance(node_t<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return GetHeight(node->children[LEFT]) - GetHeight(node->children[RIGHT]);
}

template <typename T>
int GetHeight(node_t<T> *node)
{
    if (node == nullptr)
    {
        return 0;
    }

    return node->height;
}

template <typename T>
bool avl_tree<T>::Remove(T val)
{
    return true;
}

template <typename T>
std::size_t avl_tree<T>::Size() const
{
    std::size_t counter = 0;

    if (m_root == nullptr)
    {
        return 0;
    }

    Count(m_root, &counter);

    return counter;
}

template <typename T>
bool avl_tree<T>::IsEmpty() const
{
    return Size() == 0;
}

template <typename T>
bool avl_tree<T>::Find(T val) const
{
    return FindRec(m_root, val);
}

template <typename T>
bool FindRec(node_t<T> *root, T val)
{
    if (root == nullptr)
    {
        return false;
    }

    if (root->val == val)
    {
        return true;
    }

    return (FindRec(root->children[LEFT], val) || FindRec(root->children[LEFT], val));
}

template <typename T>
void Count(node_t<T> *root, std::size_t *counter)
{
    if (root == nullptr)
    {
        return;
    }

    (*counter)++;
    Count(root->children[LEFT], counter);
    Count(root->children[RIGHT], counter);
}

template <typename T>
void DeleteTree(node_t<T> *root)
{
    if (root)
    {
        node_t<T> *left_child = root->children[LEFT];
        node_t<T> *right_child = root->children[RIGHT];

        if (left_child)
        {
            DeleteTree(left_child);
        }
        if (right_child)
        {
            DeleteTree(right_child);
        }

        delete root;
        root = nullptr;
    }

    return;
}

bool func(int x, int y, int param)
{
    return x > y;
}

int main()
{
    avl_tree<int> avl(func, 10);
    std::cout << avl.IsEmpty() << std::endl;
    std::cout << avl.Size() << std::endl;
    avl.Insert(1);
    avl.Insert(2);
    avl.Insert(3);
    avl.Insert(4);
    avl.Insert(5);

    std::cout << avl.IsEmpty() << std::endl;
    std::cout << avl.Size() << std::endl;

    return 0;
}
