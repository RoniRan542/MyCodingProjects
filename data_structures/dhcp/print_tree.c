
/*******************************************************************************
								PRINT TREE
*******************************************************************************/

#include <stdio.h>
#include <string.h>

#define MAX_HEIGHT 1000
int lprofile[MAX_HEIGHT];
int rprofile[MAX_HEIGHT];
#define INFINITY (1<<20)


typedef struct asciinode_struct asciinode_t;

struct asciinode_struct
{
  asciinode_t * left, * right;

  /*length of the edge from this node to its children*/
  int edge_length; 
    
  int height;      

  int lablen;

  /*-1=I am left, 0=I am root, 1=right  */ 
  int parent_dir;   
                         
  /*max supported unit32 in dec, 10 digits max*/
  char label[11];  
};



void PrintTree(dhcp_t *dhcp);
static void PrintAsciiTree(node_t *t);
static void PrintLevel(asciinode_t *node, int x, int level);
static void computeEdgeLengths(asciinode_t *node);
static void ComputeLprofile(asciinode_t *node, int x, int y);
static void ComputeRprofile(asciinode_t *node, int x, int y);
static void FreeAsciiTree(asciinode_t *node);
static asciinode_t * BuildAsciiTree(node_t *t);


/*adjust gap between left and right nodes*/
int gap = 3;  

/*used for printing next node in the same level, */
/*this is the x coordinate of the next char printed*/
int print_next;    

int MIN (int X, int Y)  
{
  return ((X) < (Y)) ? (X) : (Y);
}

int MAX (int X, int Y)  
{
  return ((X) > (Y)) ? (X) : (Y);
}

static asciinode_t * BuildAsciiTreeRecursive(node_t *t) 
{
  asciinode_t * node;
  
  if (t == NULL) return NULL;

  node = malloc(sizeof(asciinode_t));
  node->left = BuildAsciiTreeRecursive(t->children[LEFT]);
  node->right = BuildAsciiTreeRecursive(t->children[RIGHT]);
  
  if (node->left != NULL) 
  {
    node->left->parent_dir = -1;
  }

  if (node->right != NULL) 
  {
    node->right->parent_dir = 1;
  }

  sprintf(node->label, "%d", t->state);
  node->lablen = strlen(node->label);

  return node;
}


/*Copy the tree into the ascii node structre*/
static asciinode_t * BuildAsciiTree(node_t *t) 
{
  asciinode_t *node;
  if (t == NULL) return NULL;
  node = BuildAsciiTreeRecursive(t);
  node->parent_dir = 0;
  return node;
}

/*Free all the nodes of the given tree*/
static void FreeAsciiTree(asciinode_t *node) 
{
  if (node == NULL) return;
  FreeAsciiTree(node->left);
  FreeAsciiTree(node->right);
  free(node);
}

/*The following function fills in the lprofile array for the given tree.
//It assumes that the center of the label of the root of this tree
//is located at a position (x,y).  It assumes that the edge_length
/fields have been computed for this tree.*/
static void ComputeLprofile(asciinode_t *node, int x, int y) 
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  lprofile[y] = MIN(lprofile[y], x-((node->lablen-isleft)/2));
  if (node->left != NULL) 
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
	    lprofile[y+i] = MIN(lprofile[y+i], x-i);
    }
  }
  ComputeLprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  ComputeLprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

static void ComputeRprofile(asciinode_t *node, int x, int y) 
{
  int i, notleft;
  if (node == NULL) return;
  notleft = (node->parent_dir != -1);
  rprofile[y] = MAX(rprofile[y], x+((node->lablen-notleft)/2));
  if (node->right != NULL) 
  {
	  for (i=1; i <= node->edge_length && y+i < MAX_HEIGHT; i++) 
    {
	    rprofile[y+i] = MAX(rprofile[y+i], x+i);
    }
  }
  ComputeRprofile(node->left, x-node->edge_length-1, y+node->edge_length+1);
  ComputeRprofile(node->right, x+node->edge_length+1, y+node->edge_length+1);
}

/*This function fills in the edge_length and 
height fields of the specified tree*/
static void computeEdgeLengths(asciinode_t *node) 
{
  int h, hmin, i, delta;
  if (node == NULL) return;
  computeEdgeLengths(node->left);
  computeEdgeLengths(node->right);

  /* first fill in the edge_length of node */
  if (node->right == NULL && node->left == NULL) 
  {
	  node->edge_length = 0;
  } 
  else 
  {
    if (node->left != NULL) 
    {
	    for (i=0; i<node->left->height && i < MAX_HEIGHT; i++) 
      {
		    rprofile[i] = -INFINITY;
	    }
	    ComputeRprofile(node->left, 0, 0);
	    hmin = node->left->height;
    } 
    else 
    {
	    hmin = 0;
    }
	  if (node->right != NULL) 
    {
	    for (i=0; i<node->right->height && i < MAX_HEIGHT; i++) 
      {
		    lprofile[i] = INFINITY;
	    }
	    ComputeLprofile(node->right, 0, 0);
	    hmin = MIN(node->right->height, hmin);
    } 
    else 
    {
	    hmin = 0;
    }
	  delta = 4;
	  for (i=0; i<hmin; i++) 
    {
	    delta = MAX(delta, gap + 1 + rprofile[i] - lprofile[i]);
    }
	  
    /*If the node has two children of height 1, then we allow the
    two leaves to be within 1, instead of 2 */
	  if (((node->left != NULL && node->left->height == 1) ||
	      (node->right != NULL && node->right->height == 1))&&delta>4) 
    {
      delta--;
    }
	    
    node->edge_length = ((delta+1)/2) - 1;
  }

  /*now fill in the height of node*/
  h = 1;
  if (node->left != NULL) 
  {
	  h = MAX(node->left->height + node->edge_length + 1, h);
  }
  if (node->right != NULL) 
  {
	  h = MAX(node->right->height + node->edge_length + 1, h);
  }
  node->height = h;
}

/*This function prints the given level of the given tree, assuming
that the node has the given x cordinate.*/
static void PrintLevel(asciinode_t *node, int x, int level) 
{
  int i, isleft;
  if (node == NULL) return;
  isleft = (node->parent_dir == -1);
  if (level == 0) 
  {
	  for (i=0; i<(x-print_next-((node->lablen-isleft)/2)); i++) 
    {
	    printf(" ");
    }
	  print_next += i;
	  printf("%s", node->label);
	  print_next += node->lablen;
  } 
  else if (node->edge_length >= level) 
  {
	  if (node->left != NULL) 
    {
	    for (i=0; i<(x-print_next-(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("/");
	    print_next++;
    }
	  if (node->right != NULL) 
    {
	    for (i=0; i<(x-print_next+(level)); i++) 
      {
		    printf(" ");
	    }
	    print_next += i;
	    printf("\\");
	    print_next++;
    }
  } 
  else 
  {
	  PrintLevel(node->left, 
                x-node->edge_length-1, 
                level-node->edge_length-1);
	  PrintLevel(node->right, 
                x+node->edge_length+1, 
                level-node->edge_length-1);
  }
}

/*prints ascii tree for given Tree structure*/
static void PrintAsciiTree(node_t *t) 
{
  asciinode_t *proot;
  int xmin, i;
  if (t == NULL) return;
  proot = BuildAsciiTree(t);
  computeEdgeLengths(proot);
  for (i=0; i<proot->height && i < MAX_HEIGHT; i++) 
  {
	  lprofile[i] = INFINITY;
  }
  ComputeLprofile(proot, 0, 0);
  xmin = 0;
  for (i = 0; i < proot->height && i < MAX_HEIGHT; i++) 
  {
	  xmin = MIN(xmin, lprofile[i]);
  }
  for (i = 0; i < proot->height; i++) 
  {
	  print_next = 0;
	  PrintLevel(proot, -xmin, i);
	  printf("\n");
  }
  if (proot->height >= MAX_HEIGHT) 
  {
	  printf("(This tree is taller than %d, and may be drawn incorrectly.)\n", MAX_HEIGHT);
  }
  FreeAsciiTree(proot); 
}

void PrintTree(dhcp_t *dhcp)
{
	PrintAsciiTree(dhcp->root);
}
