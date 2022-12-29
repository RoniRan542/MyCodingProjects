
#include <iostream>

using namespace std;

typedef struct ListNode
{
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
} list_node_t;

ListNode *swapPairs(ListNode *head)
{
    ListNode *next = head;
    if (head->next == nullptr)
    {
        return head;
    }
    else if (head->next->next == nullptr)
    {
        head = head->next;
        head->next = next;
        next->next = nullptr;

        return head;
    }

    ListNode *retval = swapPairs(head->next->next);
    head = head->next;
    head->next = next;
    next->next = retval;

    return head;
}

int main()
{
    list_node_t *new_head;
    list_node_t node4(4, nullptr);
    list_node_t node3(3, &node4);
    list_node_t node2(2, &node3);
    list_node_t node1(1, &node2);

    new_head = swapPairs(&node1);

    list_node_t *runner = new_head;
    while (runner != nullptr)
    {
        cout << runner->val << endl;
        runner = runner->next;
    }

    return 0;
}