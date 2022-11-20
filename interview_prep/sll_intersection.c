
#include <stdlib.h>
#include <stdio.h>

typedef struct ListNode node_t;

struct ListNode
{
    int val;
    node_t *next;
};

node_t *getIntersectionNode(node_t *headA, node_t *headB)
{
    int countA = 0;
    int countB = 0;
    node_t *Arunner = headA;
    node_t *Brunner = headB;

    while (countA < 2 && countB < 2)
    {
        if (Arunner == Brunner)
        {
            return Arunner;
        }

        Arunner = Arunner->next;
        Brunner = Brunner->next;

        if (NULL == Arunner)
        {
            ++countA;
            Arunner = headB;
        }

        if (NULL == Brunner)
        {
            ++countB;
            Brunner = headA;
        }
    }

    return NULL;
}

int main()
{
    node_t Aend = {0, NULL};
    node_t Anode1 = {1, &Aend};
    node_t Anode2 = {2, &Anode1};
    node_t Anode3 = {3, &Anode2};
    node_t Anode4 = {4, &Anode3};
    node_t Anode5 = {5, &Anode4};
    node_t Anode6 = {6, &Anode5};
    node_t Anode7 = {7, &Anode6};
    node_t Ahead = {8, &Anode7};

    /* node_t *Bend = {0, NULL};
    node_t *Bnode1 = {1, Bend};
    node_t *Bnode2 = {2, Bnode1}; */
    node_t Bnode3 = {3, &Anode3};
    node_t Bnode4 = {4, &Bnode3};
    node_t Bnode5 = {5, &Bnode4};
    node_t Bnode6 = {5, &Bnode5};
    node_t Bnode7 = {5, &Bnode6};
    node_t Bhead = {5, &Bnode7};

    printf("val: = %d\n", getIntersectionNode(&Ahead, &Bhead)->val);
    return 0;
}
