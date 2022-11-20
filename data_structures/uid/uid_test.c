/********************************************************************************
Author:  Ran Aharon Cohen  
Date: 26/03/21
Reviewed By: 
********************************************************************************/
#include <stdio.h>/* printf */
#include <unistd.h> 	/* pid_t */
#include "uid.h"/* ilrd_uid_t */

void PrintUid(ilrd_uid_t uid);

int main()
{
	ilrd_uid_t uid1;
	ilrd_uid_t uid2;
	uid1 = UIDCreate();
	sleep(1);
	uid2 = UIDCreate();
	
	printf("%d\n", UIDIsSame(uid1, uid2));
	PrintUid(uid1);
	PrintUid(uid2);
	
	return 0;
}

void PrintUid(ilrd_uid_t uid)
{
    printf("pid: %d\n", uid.pid);
    printf("time: %ld\n", uid.time);
    printf("counter: %lu\n", uid.counter);
    printf("\n\n");
}
