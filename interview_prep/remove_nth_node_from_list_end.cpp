
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

list_node_t *removeNthFromEnd(list_node_t *head, int n)
{
    list_node_t *runner = head;
    list_node_t *prev = head;
    int counter = 0;

    while (runner->next != nullptr)
    {
        counter++;
        runner = runner->next;
    }

    cout << "counter = " << counter << endl;
    counter = counter - n;
    runner = head;

    if (counter == 0)
    {
        head = head->next;
        runner->next = nullptr;
        runner->val = 0;
        return head;
    }

    for (int i = 0; i < counter; i++)
    {
        prev = runner;
        runner = runner->next;
    }
    prev->next = runner->next;

    return head;
}

int main()
{
    list_node_t end;
    list_node_t node4(4, &end);
    list_node_t node3(3, &node4);
    list_node_t node2(2, &node3);
    list_node_t node1(1, &node2);
    list_node_t head(0, &node1);

    list_node_t *runner = &head;
    while (runner->next != nullptr)
    {
        cout << runner->val << endl;
        runner = runner->next;
    }

    cout << "\n\n";
    list_node_t *new_head = removeNthFromEnd(&head, 2);
    runner = new_head;
    while (runner->next != nullptr)
    {
        cout << runner->val << endl;
        runner = runner->next;
    }

    return 0;
}