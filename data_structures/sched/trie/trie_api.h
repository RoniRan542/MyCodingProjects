typedef char* ip_t

trie_t *TrieCreate(ip_t ip_address, char *subnet_mask);
void TrieDestroy(trie_t *trie);
ip_t TrieAllocIP(trie_t *trie);
void TrieFreeIP(trie_t *trie, ip_t ip_address);
size_t CountFreeIPs(const trie_t *trie);

the user sends ip address as string and subnet mask

123.086.255.255

/
struct trie
{
	ip_t ip_root;
	sll *sll;
	size_t capacity;
};



7 - 111


			  r
		0		    1
	 0	    1 	  0		 1		
  0    1  0  1  1   0  0   1    
  

