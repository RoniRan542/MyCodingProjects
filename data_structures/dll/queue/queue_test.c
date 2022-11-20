#include <stdio.h> /* printf */
#include <stdlib.h>/* free */
#include "queue.h"
#include "slinked.h"

int main()
{
	queue_t *queue = NULL;
	queue_t *dest = NULL;
	queue_t *src = NULL;
	int Ints[5] = {0,1,2,3,4};
	int Ints2[5] = {5,6,7,8,9};
	printf("\n\n-------Test Create and Destroy queue---------\n\n");
	
	queue = QueueCreate();
	printf("IsEmpty? yes = 1, no = 0. %d\n",QueueIsEmpty(queue));
	printf("GetSize %ld\n",QueueGetSize(queue));
	QueueDestroy(queue);
	
	
	printf("\n\n-------Test Insert(Enqueue) and peek queue---------\n\n");
	
	dest = QueueCreate();
	
	printf("success is 0 = %d\n",QueueEnqueue(dest, &Ints[0]));
	printf("Ints[0]: %d\n",*(int *)QueuePeek(dest));
	printf("success is 0 = %d\n",QueueEnqueue(dest, &Ints[1]));
	printf("Ints[1]: %d\n",*(int *)QueuePeek(dest));
	printf("success is 0 = %d\n",QueueEnqueue(dest, &Ints[2]));
	printf("Ints[2]: %d\n",*(int *)QueuePeek(dest));
	printf("success is 0 = %d\n",QueueEnqueue(dest, &Ints[3]));
	printf("Ints[3]: %d\n",*(int *)QueuePeek(dest));
	printf("success is 0 = %d\n",QueueEnqueue(dest, &Ints[4]));
	printf("Ints[4]: %d\n",*(int *)QueuePeek(dest));
	printf("IsEmpty? yes = 1, no = 0: %d\n",QueueIsEmpty(dest));
	printf("GetSize %ld\n",QueueGetSize(dest));
	PrintQueue(dest);
	
	printf("\n\n-------Test Remove(Dequeue) queue---------\n\n");
	printf("first element = %d\n",*(int *)QueuePeek(dest));
	QueueDequeue(dest);
	
	printf("first element after dequeue = %d\n",*(int *)QueuePeek(dest));
	QueueDequeue(dest);
	printf("first element after dequeue = %d\n",*(int *)QueuePeek(dest));
	QueueDequeue(dest);
	printf("first element after dequeue = %d\n",*(int *)QueuePeek(dest));
	QueueDequeue(dest);
	printf("first element after dequeue = %d\n",*(int *)QueuePeek(dest));
	QueueDequeue(dest);
	printf("first element after dequeue = %d\n",*(int *)QueuePeek(dest));
	
	printf("\n\n-------APPEND queue---------\n\n");
	printf("\n\n-------create second queue---------\n\n");
	src = QueueCreate();
	printf("success is 0 = %d\n",QueueEnqueue(src, &Ints2[0]));
	printf("Ints[5]: %d\n",*(int *)QueuePeek(src));
	printf("success is 0 = %d\n",QueueEnqueue(src, &Ints2[1]));
	printf("Ints[6]: %d\n",*(int *)QueuePeek(src));
	printf("success is 0 = %d\n",QueueEnqueue(src, &Ints2[2]));
	printf("Ints[7]: %d\n",*(int *)QueuePeek(src));
	printf("success is 0 = %d\n",QueueEnqueue(src, &Ints2[3]));
	printf("Ints[8]: %d\n",*(int *)QueuePeek(src));
	printf("success is 0 = %d\n",QueueEnqueue(src, &Ints2[4]));
	printf("Ints[9]: %d\n",*(int *)QueuePeek(src));
	printf("IsEmpty? yes = 1, no = 0: %d\n",QueueIsEmpty(src));
	printf("GetSize %ld\n",QueueGetSize(src));
	printf("\n\n------- check APPEND queue---------\n\n");
	dest = QueueAppend(dest ,src);
	PrintQueue(dest);
	QueueDestroy(dest);
	
	return 0;
}
