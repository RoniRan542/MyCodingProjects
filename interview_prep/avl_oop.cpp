#include <cstddef>
#include <functional>
#include <cstdlib>
#include <iostream>
#include <queue>

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
node_t<T> *InsertRecursively(node_t<T> *root, std::function<bool(T, T, T)> cmp, T param, T val);
template <typename T>
node_t<T> *RotateRight(node_t<T> *root);
template <typename T>
node_t<T> *RotateLeft(node_t<T> *root);
template <typename T>
node_t<T> *RotateLeftRight(node_t<T> *root);
template <typename T>
node_t<T> *RotateRightLeft(node_t<T> *root);

template <typename T>
class avl_tree
{
public:
    avl_tree(std::function<bool(T, T, T)> cmp, T param);
    ~avl_tree();
    node_t<T> *Insert(T val);
    node_t<T> *Remove(T val);
    std::size_t Size() const;
    bool IsEmpty() const;
    bool Find(T val) const;
    bool ForEach(std::function<bool> func, T param);
    node_t<T> *GetRoot()
    {
        return m_root;
    }

private:
    node_t<T> *m_root; // root node
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
node_t<T> *avl_tree<T>::Insert(T val)
{
    m_root = InsertRecursively(m_root, m_cmp, m_param, val);

    return m_root;
}

template <typename T>
node_t<T> *InsertRecursively(node_t<T> *root, std::function<bool(T, T, T)> cmp, T param, T val)
{

    if (root == nullptr)
    {
        root = new node_t<T>;
        root->val = val;
        root->height = 1;

        return root;
    }

    if (cmp(val, root->val, param))
    {
        root->children[RIGHT] = InsertRecursively(root->children[RIGHT], cmp, param, val);
    }
    else
    {
        root->children[LEFT] = InsertRecursively(root->children[LEFT], cmp, param, val);
    }
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;

    int balance = GetBalance(root);
    if (balance > 1) // left heavy
    {
        if (GetBalance(root->children[LEFT]) >= 1)
        {
            root = RotateRight(root);
        }
        else
        {
            root = RotateLeftRight(root->children[LEFT]);
        }
    }
    else if (balance < -1) // right heavy
    {
        if (GetBalance(root->children[RIGHT]) <= 0)
        {
            root = RotateLeft(root);
        }
        else
        {
            root = RotateRightLeft(root->children[RIGHT]);
        }
    }
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;

    return root;
}

template <typename T>
node_t<T> *avl_tree<T>::Remove(T val)
{
    bool is_found = false;
    m_root = RemoveRecursively(root, m_cmp, m_param, val, &is_found);

    return m_root;
}

template <typename T>
node_t<T> *RemoveRecursively(node_t<T> *root, std::function<bool(T, T, T)> cmp, T param, T val, bool *found)
{
    if (root->val == val)
    {
        if (GetNumOfChildren(root) == 0)
        {
            root nullptr;
        }
        else if (GetNumOfChildren(root) == 1)
        {
            RemoveSingleChildNode(root);
        }
        else
        {
        }

        return root;
    }

    if (cmp(val, root->val, param))
    {
        if (root->children[RIGHT] == nullptr)
        {
            return nullptr;
        }
        root->children[RIGHT] = RemoveRecursively(root->children[RIGHT], cmp, param, val);
    }
    else
    {
        if (root->children[LEFT] == nullptr)
        {
            return nullptr;
        }
        root->children[LEFT] = RemoveRecursively(root->children[LEFT], cmp, param, val);
    }

    return root;
}

template <typename T>
static short GetNumOfChildren(node_t<T> *node)
{
    short num_of_ch = 0;

    num_of_ch += (nullptr != node->children[RIGHT]);
    num_of_ch += (nullptr != node->children[LEFT]);

    return num_of_ch;
}

template <typename T>
node_t<T> *RotateRight(node_t<T> *root)
{
    node_t<T> *new_root = root->children[LEFT];
    root->children[LEFT] = new_root->children[RIGHT];
    new_root->children[RIGHT] = root;
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;

    return new_root;
}

template <typename T>
node_t<T> *RotateLeft(node_t<T> *root)
{
    node_t<T> *new_root = root->children[RIGHT];
    root->children[RIGHT] = new_root->children[LEFT];
    new_root->children[LEFT] = root;
    root->height = MAX(GetHeight(root->children[RIGHT]), GetHeight(root->children[LEFT])) + 1;

    return new_root;
}

template <typename T>
node_t<T> *RotateLeftRight(node_t<T> *root)
{
    root->children[RIGHT] = RotateLeft(root->children[RIGHT]);
    root = RotateRight(root);

    return root;
}

template <typename T>
node_t<T> *RotateRightLeft(node_t<T> *root)
{
    root->children[LEFT] = RotateRight(root->children[LEFT]);
    root = RotateLeft(root);
    return root;
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

template <typename T>
void print2DUtil(node_t<T> *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += 3;

    // Process right child first
    print2DUtil(root->children[RIGHT], space);

    // Print current node after space
    // count
    std::cout << std::endl;
    for (int i = 3; i < space; i++)
        std::cout << " ";
    std::cout << root->val << "\n";

    // Process left child
    print2DUtil(root->children[LEFT], space);
}

// Wrapper over print2DUtil()
template <typename T>
void print2D(node_t<T> *root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
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
    avl.Insert(6);
    avl.Insert(7);
    avl.Insert(8);
    avl.Insert(9);

    std::cout << avl.IsEmpty() << std::endl;
    std::cout << avl.Size() << std::endl;

    // PrintPreOrder(avl.GetRoot(), "center");
    print2D(avl.GetRoot());

    return 0;
}
