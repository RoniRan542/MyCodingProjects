/*
Given the head pointer of a linked list,
sort the linked list in ascending order using merge sort,
and return the new head pointer of sorted linked list.
 */

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

void SplitListInHalf(list_node_t *head, pair<list_node_t *, list_node_t *> &left_right)
{
    list_node_t *slow = nullptr;
    list_node_t *fast = nullptr;

    if (head == nullptr)
    {
        return;
    }

    if (head->next == nullptr)
    {
        left_right.first = head;
        left_right.second = nullptr;
    }
    else
    {

        slow = head;
        fast = head->next;

        while (fast != nullptr)
        {
            fast = fast->next;

            if (fast != nullptr)
            {
                fast = fast->next;
                slow = slow->next;
            }
        }

        left_right.first = head;
        left_right.second = slow->next;

        slow->next = nullptr;
    }
}

list_node_t *MergeSortedLists(list_node_t *first, list_node_t *second)
{
    if (first == nullptr)
    {
        return second;
    }
    else if (second == nullptr)
    {
        return first;
    }

    list_node_t *new_head;

    if (first->val <= second->val)
    {
        new_head = first;
        first = first->next;
    }
    else
    {
        new_head = second;
        second = second->next;
    }

    list_node_t *curr_node = new_head;
    while (first != nullptr && second != nullptr)
    {
        list_node_t *temp = nullptr;
        if (first->val <= second->val)
        {
            temp = first;
            first = first->next;
        }
        else
        {
            temp = second;
            second = second->next;
        }

        curr_node->next = temp;
        curr_node = temp;
    }

    if (first != nullptr)
    {
        curr_node->next = first;
    }
    else if (second != nullptr)
    {
        curr_node->next = second;
    }

    return new_head;
}

list_node_t *SortSllWithMerge(list_node_t *head)
{
    if (head == nullptr || head->next == nullptr)
    {
        return head;
    }

    pair<list_node_t *, list_node_t *> left_right;

    SplitListInHalf(head, left_right);

    left_right.first = SortSllWithMerge(left_right.first);
    left_right.second = SortSllWithMerge(left_right.second);

    return MergeSortedLists(left_right.first, left_right.second);
}

int main()
{
    list_node_t *new_head;
    list_node_t node4(1, nullptr);
    list_node_t node3(9, &node4);
    list_node_t node2(2, &node3);
    list_node_t node1(6, &node2);

    list_node_t *runner = &node1;
    while (runner != nullptr)
    {
        cout << runner->val << endl;
        runner = runner->next;
    }
    new_head = SortSllWithMerge(&node1);
    runner = new_head;
    while (runner != nullptr)
    {
        cout << runner->val << endl;
        runner = runner->next;
    }
    return 0;
}
