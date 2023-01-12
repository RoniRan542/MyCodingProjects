#include <iostream>
#include <vector>

using namespace std;

// Data structure to store a XOR linked list node
struct Node
{
    int data;
    struct Node *link;
};

using node_t = struct Node *;

node_t XOR(node_t prev, node_t next)
{
    return (node_t)((size_t)prev ^ (size_t)next);
}

node_t push(node_t head, int data)
{
    // create the new node:
    node_t new_node = new Node();
    new_node->data = data;

    // find the xor link by xoring the prev(null) and next addresses
    new_node->link = XOR(nullptr, head);

    if (head != nullptr)
    {
        // find the new xor link of head by xoring the new head and next node address
        head->link = XOR(new_node, head->link);
    }

    return new_node;
}

void traverse(node_t head)
{
    node_t next = nullptr;
    node_t prev = nullptr;

    while (head != nullptr)
    {
        cout << head->data << "->";
        // convert the link and prev to the address of next
        next = XOR(prev, head->link);
        // move next
        prev = head;
        head = next;
    }
    cout << "nullptr\n";
}

void traverse_back(node_t last)
{
    node_t next = nullptr;
    node_t prev = nullptr;

    while (last != nullptr)
    {
        cout << last->data << "->";
        // convert the link and prev to the address of next
        next = XOR(prev, last->link);
        // move next
        prev = last;
        last = next;
    }
    cout << "nullptr\n";
}

int main(void)
{
    // input keys
    vector<int> mykeys = {1, 2, 3, 4, 5};
    struct Node *head = NULL;

    for (int i = mykeys.size() - 1; i >= 0; i--)
    {
        head = push(head, mykeys[i]);
    }

    traverse(head);
    traverse_back(head->link->link->link);

    return 0;
}
