// Write a program to implement heap management scheme (use a doubly linked list and the first fit allocation strategy). 
// Implement the ‘allocate’ and ‘free’ functions. Ensure that adjacent free blocks are merged together.
#include <stdio.h>
#include<stdlib.h>

int g = 0, k = 0; // Two global counters

// Structure for free node list
typedef struct free_nodes
{
    int tag;
    int size;
    struct free_nodes *next;
}F_Nodes;

F_Nodes *free_head = NULL, *prev_free = NULL;

// Structure for allocated list
typedef struct allocated_nodes
{
    int block_id;
    int tag;
    int size;
    struct allocated_nodes *next;
}A_Nodes;
A_Nodes *alloc_head = NULL, *prev_alloc = NULL;

// Creating free list with given sizes
void creating_free_list(int c)
{
    F_Nodes *p = (F_Nodes *)malloc(sizeof(F_Nodes));
    p->size = c;
    p->tag = g;
    p->next = NULL;
    if (free_head == NULL)
    {
        free_head = p;
    }
    else
    {
        prev_free->next = p;
    }
    prev_free = p;
    g++;
}

// Printing free list which prints free blocks of given sizes
void printing_free_list()
{
    F_Nodes *p = free_head;
    printf("Unique ID\tProcess Size\n");
    while (p != NULL)
    {
    	printf("%d\t%d\n",p->tag,p->size);
        //cout << p->tag << "\t"<< p->size << "\n";
        p = p->next;
    }
}

// Printing allocated list which prints allocated blocks and their block ids
void printing_allocated_list()
{
    A_Nodes *p = alloc_head;
    printf("Unique ID\tBlock ID\tProcess Size\n");
    while (p != NULL)
    {
    	printf("%d\t\t%d\t\t%d\n",p->tag,p->block_id,p->size);
        //cout << p->tag << "\t "<< p->block_id << "\t\t"<< p->size << "\n";
        p = p->next;
    }
}

// Allocating memory to blocks as per First fit algorithm
void creating_allocated_list(int c)
{
    // create node for process of given size
    A_Nodes *q = (A_Nodes *)malloc(sizeof(A_Nodes));
    q->size = c;
    q->tag = k;
    q->next = NULL;
    F_Nodes *p = free_head;

    // Iterate to find first memory
    // block with appropriate size
    while (p != NULL)
    {
        if (q->size <= p->size)
            break;
        p = p->next;
    }

    // Node found to allocate
    if (p != NULL)
    {
        // Adding node to allocated list
        q->block_id = p->tag;
        p->size -= q->size;
        if (alloc_head == NULL)
            alloc_head = q;
        else
        {
            prev_alloc = alloc_head;
            while (prev_alloc->next != NULL)
                prev_alloc = prev_alloc->next;
            prev_alloc->next = q;
        }
        k++;
    }
    else // Node found to allocate space from
        printf("Block of size %d cannot be allocated\n",c);
        //cout << "Block of size " << c << " can't be allocated\n";
}

// Deleting node from allocated list to free some space
void deleting_allocated_list(int t)
{
    // Standard delete function
    // of a linked list node
    A_Nodes *p = alloc_head, *q = NULL;

    // First, find the node according
    // to given tag id
    while (p != NULL)
    {
        if (p->tag == t)
            break;
        q = p;
        p = p->next;
    }
    if (p == NULL)
        printf("Unique ID doesn't exist\n");
    else if (p == alloc_head)
        alloc_head = alloc_head->next;
    else
        q->next = p->next;
    F_Nodes *temp = free_head;
    while (temp != NULL)
    {
        if (temp->tag == p->block_id)
        {
            temp->size += p->size;
            break;
        }
        temp = temp->next;
    }
}

int main()
{
    int i;
    printf("enter the number of block sizes of the memory : \n");
    int bs;
    scanf("%d",&bs);
    int blockSize[bs];
    printf("enter the block sizes of the memory : \n");
    for ( i = 0; i < bs; i++)
    {
        scanf("%d",&blockSize[i]);
    }

    printf("enter the number of processes sizes of the memory :\n");
    int ps;
    scanf("%d", &ps);
    int processSize[ps];
    printf("enter the processes sizes of the memory :\n");
    for (i = 0; i < ps; i++)
    {
        scanf("%d", &processSize[i]);
    }

    //int m = sizeof(blockSize) / sizeof(blockSize[0]);
    //int n = sizeof(processSize) / sizeof(processSize[0]);
	
    for (i = 0; i < bs; i++)
        creating_free_list(blockSize[i]);

    for (i = 0; i < ps; i++)
        creating_allocated_list(processSize[i]);

    printing_allocated_list();

    // Block of tag id 0 deleted
    // to free space for block of size 426
    // deleting_allocated_list(0);

    // creating_allocated_list(426);
    // printf("After deleting block with tag id 0.\n");
    // printing_allocated_list();
}
