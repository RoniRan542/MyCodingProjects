/*********************************************************************
*Name : Ran Aharon Cohen	 							     		 *
*Reviewar: 🐕️  🤯️										             *
*Date:  03/22/22													 *												 
*Description : 	UID 										     	 *
**********************************************************************/
#include <sys/types.h>/* pid_t 	*/
#include <unistd.h>/* pid_t 	*/
#include <time.h>/* time_t */

#include "../include/uid.h"/* ilrd_uid_t */
#define NUM_OF_ELEMENTS 3
#define BAD_TIME -1

const ilrd_uid_t UIDBadUID = {0,0,0};


ilrd_uid_t UIDCreate(void)
{
	static size_t counter = 0;
	ilrd_uid_t uid;
	uid.pid = getpid();
	uid.time = time(0);
	if(BAD_TIME == uid.time)
	{
		return UIDBadUID;
	}
	
	uid.counter = __sync_add_and_fetch(&counter, 1);
	
	return uid;
}

int UIDIsSame(ilrd_uid_t uid1, ilrd_uid_t uid2)
{
	int result = 0;
	result += (uid1.pid == uid2.pid);
	result += (uid1.time == uid2.time);
	result += (uid1.counter == uid2.counter);
	
	return (result == NUM_OF_ELEMENTS);
}


