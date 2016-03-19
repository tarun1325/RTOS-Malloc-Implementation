/*
	Author: Tarun Jain
	Roll Number: MT2015120
	File: RTOS Assignment 1 - Question 1 -Memory Creation and sbrk/brk function implementation (on My own Memory)
	Problem Statement: Implement the malloc, free, calloc, realloc Function using your own Heap(Static array of 10240 Bytes)
*/

// Header Files
#include "heap_management.h"

// Defragment Heap
void defragment_my_heap()
{
	char temp_memory[ MEM_SIZE];						// Temporary Storage
	struct block *tally = (struct block*) base;
	struct block *tmp;
	size_t s1;
	while(tally)								// Traverse All Blocks
	{
		if( tally->free) 						// Free Block Found
		{
			if(tally->next )					// Check for Consecutive 2 Free Blocks
			{	
				if( tally->next->free)				// Two Consecutive Blocks Found Free
					tally = fusion(tally);
			
				else						// Merge Free Block and Next Block 
				{
					s1 = tally -> next -> size;
				
					char *h1 = (char *) tally->next;
					h1 = h1 + BLOCK_SIZE;
					void *t1 = (void*) h1;
					
					void *t2 = (void*) temp_memory; 
					
					copy_data(t1, t2);
					tmp = fusion(tally);
					split_block(tmp, s1 );
			
					char *h2 = (char *) tmp;
					h2 = h2 + BLOCK_SIZE;
					t1 = (void *) h2;
			
					copy_data(t2, t1);
					tmp -> free =0;
				}
			}
		}
		tally = tally->next;
	}
}

// Free Space in Heap
size_t free_space()
{
	size_t sizeHeap = 0;					// Count Size
	struct block *tally = (struct block*)base;
	while(tally)						// Checking Mapped Region of Heap
	{
		if(tally -> free)				// Free Block Found
			sizeHeap += tally -> size;		// Update Size Count
		tally = tally -> next;				// Go to Next Block
	}
	sizeHeap += (end_limit - limit);			// Added Unmapped Region of Heap
	printf("\n");
	return sizeHeap;
}

// Copy Data
void copy_data ( void *src , void *dst)
{
	char	*sdata ,* ddata ;
	size_t	i;
	sdata = (char *)src ;
	ddata = (char *)dst ;
	
	// Just for Address Computation
	char *h1 = (char *) src;
	h1 = h1 - BLOCK_SIZE;
	struct block *m1 = (struct block*) h1;
	
	char *h2 = (char *) dst;
	h2 = h2 - BLOCK_SIZE;
	struct block *m2 = (struct block*) h2;
	
	// Copying
	for (i=0; i*4<m1 ->size && i*4< m2 ->size; i++)
		ddata [i] = sdata [i];
}

// Fusion of Two Free Blocks
struct block* fusion(struct block *b)
{
	b->size += BLOCK_SIZE + b->next->size;			// Update Size of Block
	b->next = b->next->next;				// Setting New Next of Block
	if(b->next)
		b->next->prev = b;				// Setting New Previous of Neighbour Node
	return b;
}

// Valid Address
int valid( void *x)
{
	// Just for Address Computation
	char *a = (char *) x;
	a = a - BLOCK_SIZE;
	struct block *b = (struct block *)a;
	struct block *temp = base;
	
	// Checking all Block Start Address
	while(temp)
	{
		if( temp == b)					// If Found, Return True
			return 1;
		temp = temp -> next;
	}
	return 0;
}

// Find Free Block
struct block* find_block( size_t s)
{
	struct block *b = (struct block *)base;
	while( b && !( b -> free && (b -> size >= s)))		// Stops where the appropriate free block is found
	{
		traverse = b;					// Update Traverse Pointer
		b = b -> next;
	}
	return b;
}

// Extend Heap
struct block* extend_heap( size_t s)
{
	struct block *b;
	b = my_sbrk(0);						// Getting Base Address
	if( my_sbrk( BLOCK_SIZE + s) == NULL)			// Space Not Available
	{
		printf("\nHeap Extension Failed.\n");
		return NULL;
	}
	// If Space Available, Set it's Meta Data Parameters
	b -> size = s;
	b -> next = NULL;
	b -> prev = traverse;
	if(traverse)
		traverse -> next = b;
	b -> free = 0;
	return b;
}

// Allocating Space in Heap
void* my_sbrk( size_t s)
{
	if( s == 0)						// Break Address is Requested
		return limit;
		
	// If Space not Available
	if(((size_t)( end_limit - limit )) < s)
		return NULL;
		
	void *ptr = (void *)limit;
	limit = limit + BLOCK_SIZE + s;				// Increment the Break/Limit Position
	return ptr;
}
// Split Block
void split_block( struct block *b, size_t s)
{
	struct block *new;					// Just Update Meta Data of both the blocks
	new = (struct block *)(&( b -> free) + (sizeof( b->free)) + s);
	new -> size = b -> size - s - BLOCK_SIZE;
	new -> next = b -> next;
	new -> prev = b;
	new -> free = 1;
	b -> next = new;
	b -> size = s;
	if( new -> next)
		new -> next -> prev = new;
}
