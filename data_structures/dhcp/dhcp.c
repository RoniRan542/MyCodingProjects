/*****************************************************************************
*Author: Ran Aharon Cohen													 *
*Reviewer: Karen 		         											 *
*Date: 25/05/2022															 *
*Description: dhcp.c																		 *
******************************************************************************/

#include <assert.h> /* for assert */
#include <arpa/inet.h>/* for conveting IP into bits */
#include <stdlib.h>/* malloc, free */
#include <string.h>/* memcpy */

#include "dhcp.h" /* implementing these functions */

#define IP_NUM_OF_BITS (32)
#define REQUAIRED_BUFFER_SIZE (16)
#define BYTE_SIZE (8)
#define INT_SIZE (4)

typedef struct node node_t; 

static unsigned int InitNetworkAddress(unsigned int network, size_t rev_subnet);
static int InitDhcp(dhcp_t *dhcp, size_t subnet);
static void RecDestroy(node_t *root);
static void MakeFirstAndTwoLastIPsUnavailable(node_t *root);
static node_t *CreateFullBinaryTrie(size_t depth);
static int GetBitByIndex(unsigned int num, size_t index);
static void TurnOnBitByIndex(unsigned int *num, size_t index);
static unsigned int TurnOffBitsRight(unsigned int network, size_t mask);
static unsigned int TurnOffBitsLeft(unsigned int network, size_t mask);
static size_t AvailableIPs(node_t *node);
static unsigned int ReverseFourBytes(unsigned int num);
static unsigned int ExtracteBitsPathFromNum(unsigned int number,unsigned int num_bits);
									   
static int AllocAvailableIP(unsigned int *available_ip, 
											unsigned int rev_subnet, node_t *root);
static int CheckIsNetworkMatch(unsigned int network, 
												unsigned int ip, size_t rev_subnet);
static void ActualFreeIP(unsigned int requested_ip, 
										unsigned int rev_subnet, node_t *root);
static int AllocIpHelper(unsigned int requested_ip, 
								unsigned int rev_subnet, node_t *root);
static int AllocMinimumIP(char *buffer, unsigned int *decimal_ip, 
			  unsigned int rev_subnet, unsigned int *available_ip, node_t *root);
			  
enum used_status
{
    NOT_USED = 0,
    USED = 1
};

enum return_status
{
    SUCCESS = 0,
    SUCCESS_PTON = 1,
    FAILURE = 1
};

enum Children
{
    LEFT = 0,
    RIGHT = 1,
    NUM_OF_CHILDREN
};

struct DHCP
{
    node_t *root;
    unsigned int network;
    size_t rev_subnet;
};

struct node
{
    node_t *children[NUM_OF_CHILDREN];
    int state;
};

dhcp_t *DHCPCreate(const char *network, size_t subnet)
{
	dhcp_t *dhcp = NULL;
	
	assert(NULL != network);
	assert(30 > subnet && 23 < subnet );
	
	dhcp = (dhcp_t *)malloc(sizeof(dhcp_t));
	if(NULL == dhcp)
	{
		return NULL;
	}
	
	if(SUCCESS_PTON != inet_pton(AF_INET, network, &dhcp->network))
	{
		free(dhcp);
		dhcp = NULL;
		
		return NULL;
	}
	
	if(FAILURE == InitDhcp(dhcp, subnet))
	{
		return NULL;
	}
	
	return dhcp;
}

static int InitDhcp(dhcp_t *dhcp, size_t subnet)
{
	dhcp->rev_subnet = IP_NUM_OF_BITS - subnet;
	dhcp->network = InitNetworkAddress(dhcp->network, dhcp->rev_subnet);
	
	dhcp->root = CreateFullBinaryTrie(dhcp->rev_subnet + 1);
	if(NULL == dhcp->root)
	{
		free(dhcp);
		dhcp = NULL;
		
		return FAILURE;
	}
	
	MakeFirstAndTwoLastIPsUnavailable(dhcp->root);
	
	return SUCCESS;
}

static unsigned int InitNetworkAddress(unsigned int network, size_t rev_subnet)
{
	network = ReverseFourBytes(network);
	network = TurnOffBitsRight(network, rev_subnet);
	
	return network;
}
static node_t *CreateFullBinaryTrie(size_t depth)
{
    node_t *node = NULL;

	assert(0 != depth);

	node = (node_t *)calloc(1LU, sizeof(node_t));
	if(NULL == node)
	{
		return NULL;
	}
	
    if(1LU == depth)
    {
    	return node;
    }

	node->children[LEFT] = CreateFullBinaryTrie(depth - 1);
	node->children[RIGHT] = CreateFullBinaryTrie(depth - 1);
    
    if(NULL == node->children[LEFT] || NULL == node->children[RIGHT]) 
    {
    	return NULL;
    }
    
    return node;
}

static void MakeFirstAndTwoLastIPsUnavailable(node_t *root)
{
	node_t *runner = NULL;
	
	assert(NULL != root);
	
	runner = root;
	while(NULL != runner->children[LEFT])
	{
		runner = runner->children[LEFT];
	}
	
	runner->state = USED;
	
	runner = root;
	while(NULL != (runner->children[RIGHT])->children[RIGHT])
	{
		runner = runner->children[RIGHT];
	}
	
	(runner->children[RIGHT])->state = USED;
	(runner->children[LEFT])->state = USED;
}

void DHCPDestroy(dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	RecDestroy(dhcp->root);
	dhcp->root = NULL;
	
	free(dhcp);
	dhcp = NULL;
}

static void RecDestroy(node_t *root)
{
	if(NULL == root)
	{
		return;
	}
	RecDestroy(root->children[LEFT]);
	RecDestroy(root->children[RIGHT]);
	
	free(root);
	root = NULL;
}

int DHCPAllocIP(dhcp_t *dhcp ,const char *requested_ip, char *buffer)
{
	unsigned int decimal_ip = 0;
	unsigned int available_ip = 0;
    
	assert(NULL != dhcp);
	assert(NULL != buffer);
	
	if(NULL == requested_ip)
    { 
         decimal_ip = dhcp->network;
         return AllocMinimumIP(buffer, &decimal_ip, 
                                    dhcp->rev_subnet, &available_ip, dhcp->root);  
    }
    
	if(SUCCESS_PTON != inet_pton(AF_INET, requested_ip, &decimal_ip))
	{
		return FAILURE;
	}
	if(!CheckIsNetworkMatch(dhcp->network, decimal_ip, dhcp->rev_subnet))
	{
		return FAILURE;
	}
    
	decimal_ip = TurnOffBitsLeft(decimal_ip, IP_NUM_OF_BITS - dhcp->rev_subnet);
	
	if(SUCCESS != AllocIpHelper(decimal_ip, dhcp->rev_subnet, dhcp->root))
	{
		decimal_ip = dhcp->network;
		return AllocMinimumIP(buffer, &decimal_ip, 
                                    dhcp->rev_subnet, &available_ip, dhcp->root);  
	}
	memcpy(buffer, requested_ip, REQUAIRED_BUFFER_SIZE);  

	return SUCCESS;
}

static int AllocMinimumIP(char *buffer, unsigned int *decimal_ip, 
			  unsigned int rev_subnet, unsigned int *available_ip, node_t *root)
{
	struct in_addr ip_addr;

	assert(NULL != buffer);
	assert(NULL != decimal_ip);
	assert(NULL != available_ip);
	assert(NULL != root);

	*decimal_ip = TurnOffBitsRight(*decimal_ip, rev_subnet);
	if(SUCCESS != AllocAvailableIP(available_ip, rev_subnet, root))
	{
		return FAILURE;
	}
	
	*decimal_ip += *available_ip;	
	*decimal_ip = ReverseFourBytes(*decimal_ip);
	ip_addr.s_addr = *decimal_ip;
	memcpy(buffer, inet_ntoa(ip_addr), REQUAIRED_BUFFER_SIZE);
	
	return SUCCESS;
}

static int AllocAvailableIP(unsigned int *available_ip, unsigned int rev_subnet, node_t *root)
{	
	int status = SUCCESS;
	
	assert(NULL != available_ip);
	
	if(rev_subnet == 0)
	{
		if (NOT_USED == root->state)
		{
			root->state = USED;
			
			return SUCCESS;
		}
		
		return FAILURE;
	}
	
	if(NOT_USED == root->children[LEFT]->state)
	{
		status = AllocAvailableIP(available_ip, rev_subnet - 1, root->children[LEFT]);		
	}	
	else if(NOT_USED == root->children[RIGHT]->state)
	{	
		TurnOnBitByIndex(available_ip, rev_subnet);
		status = AllocAvailableIP(available_ip, rev_subnet - 1, root->children[RIGHT]);
	}

	if(USED == (root->children[RIGHT])->state && USED == (root->children[LEFT])->state)
	{
		root->state = USED;
	}
	
	return status;
}
	
static int AllocIpHelper(unsigned int requested_ip, 
								unsigned int rev_subnet, node_t *root)
{
	int direction = LEFT;
	int status = SUCCESS;
	
	assert(NULL != root);
	
	if(0 == rev_subnet) 
	{
		if(USED == root->state)
		{
			return FAILURE;
		}
		
		root->state = USED;
		
		return SUCCESS;	
	}
	
	direction = GetBitByIndex(requested_ip, rev_subnet);
	status = AllocIpHelper(requested_ip, rev_subnet - 1, root->children[direction]);
	
	if(USED == (root->children[RIGHT])->state &&
								 USED == (root->children[LEFT])->state)
	{
		root->state = USED;
	}
	
	return status;
}	

void DHCPFreeIP(dhcp_t *dhcp, char *ip)
{
	unsigned int decimal_ip = 0;
	unsigned int ip_path = 0;
	
	assert(NULL != dhcp);
	assert(NULL != ip);

	if(SUCCESS_PTON != inet_pton(AF_INET, ip, &decimal_ip))
	{
		return;
	}

	if(!CheckIsNetworkMatch(dhcp->network, decimal_ip, dhcp->rev_subnet))
	{
		return;
	}
	
	decimal_ip = ReverseFourBytes(decimal_ip);
	ip_path = ExtracteBitsPathFromNum(decimal_ip, dhcp->rev_subnet);
	
	ActualFreeIP(ip_path, dhcp->rev_subnet, dhcp->root);										 
}

static void ActualFreeIP(unsigned int requested_ip, unsigned int rev_subnet, node_t *root)
{
	int direction = LEFT;
	
	assert(NULL != root);
	
	if(0 == rev_subnet) 
	{
		root->state = NOT_USED;	
	}
	else
	{
		direction = GetBitByIndex(requested_ip, rev_subnet);
		ActualFreeIP(requested_ip, rev_subnet - 1, root->children[direction]);
		
		if((root->children[RIGHT])->state == NOT_USED || (root->children[LEFT])->state == NOT_USED)
		{
			root->state = NOT_USED;
		}
	}
}	

size_t DHCPAvailableIPs(const dhcp_t *dhcp)
{
	assert(NULL != dhcp);
	
	return AvailableIPs(dhcp->root);
}

static size_t AvailableIPs(node_t *node)
{
	size_t count = 0;
	
	if(NULL == node)
	{
		return 0;
	}
	
	if(USED == node->state)
	{
		return 0;
	}
	
	if(NULL == node->children[RIGHT] && NULL == node->children[LEFT])
	{
		return !(node->state);
	}
	count += AvailableIPs(node->children[LEFT]);
	count += AvailableIPs(node->children[RIGHT]);
	
	return count;
}

static int CheckIsNetworkMatch(unsigned int network, unsigned int ip, size_t rev_subnet)
{
	ip = ReverseFourBytes(ip);
	ip = TurnOffBitsRight(ip, rev_subnet);
	
	return ip == network;
}

static int GetBitByIndex(unsigned int num, size_t index)
{
	return ((num >> (index - 1)) & 1);
}

static void TurnOnBitByIndex(unsigned int *num, size_t index)
{
	unsigned int mask = (1 << (index - 1));

	*num |= (mask);
}

static unsigned int ExtracteBitsPathFromNum(unsigned int number, 
									   unsigned int num_bits)
{
    return (((1 << num_bits) - 1) & (number));
}

static unsigned int TurnOffBitsRight(unsigned int network, size_t mask)
{
	return ((network >> mask) << mask);
}

static unsigned int TurnOffBitsLeft(unsigned int network, size_t mask)
{
	return ((network >> mask));
}

static unsigned int ReverseFourBytes(unsigned int num)
{
	unsigned int reversed = 0;
	int mask = 0xFF;
	int i = 0;
	
	for(i = 0; i < INT_SIZE; ++i)
	{
		reversed = reversed << BYTE_SIZE;
		reversed |= (num & mask);
		num = num >> BYTE_SIZE;
	}
	
	return reversed;
}

