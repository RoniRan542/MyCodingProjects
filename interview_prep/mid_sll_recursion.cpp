/*
find the middle node in singley linked list using recursion.

pseudo code:
======================
1. recurse till head == null while counting nodes.
2. when finished divide the counter by 2 and go back
3. going back, reduce counter by one
4. check if counter == 0
5. if yes: put node in result node

 */

#include <stdio.h>

struct node
{
    int data;
    node *next;
};

void FindMidSll(struct node *head, int *count, struct node **mid)
{
    if (head == nullptr)
    {
        *count = (*count) / 2;

        return;
    }

    ++(*count);
    FindMidSll(head->next, count, mid);

    if (*count == 0)
    {
        *mid = head;
    }
    --(*count);
}

int main()
{
    /* struct node node5 = {5, nullptr};
    struct node node4 = {4, &node5}; */
    struct node node4 = {4, nullptr};
    struct node node3 = {3, &node4};
    struct node node2 = {2, &node3};
    struct node node1 = {1, &node2};

    struct node *mid;
    int counter = 0;

    FindMidSll(&node1, &counter, &mid);

    printf("the date of the middle node is: %d \n", mid->data);

    return 0;
}
