/*
	Author: Tarun Jain
	Roll Number: MT2015120
	File: RTOS Assignment 1 - Question 1 -Allocation/Deallocation Functions
	Problem Statement: Implement the malloc, free, calloc, realloc Function using your own Heap(Static array of 10240 Bytes)
*/

// Header Files
#include "heap_management.h"

// Realloc Function
void* my_realloc( void *p, size_t s)
{
	// If NULL , Treat as Malloc Call
	if( !p)
		return (my_malloc(s));
	
	// If Valid Address
	if( valid(p))
	{
		void *xyz = my_malloc(s);		// Getting Requested Space
		if(!xyz)				// If Space not available
			return NULL;
		copy_data(p , xyz);			// Copy data of old block to new block
		free(p);				// Free Up the Old Block
		return xyz;				// Return New Block's address
	}
	return NULL;					// If Invalid Address, return NULL
}

// Malloc Function
void* my_malloc( size_t s)
{
	if( s == 0)					// If Requested Size is Zero, Return NULL
		return NULL;
	struct block *b;
	if( base)					// If Heap is Already Created
	{
		traverse = (struct block *)base;	// Set Traverse Pointer
		b = find_block( s);			// Find Appropriate Free Block
		if(!b)					// No Appropriate Free Block Found
		{
			b = extend_heap( s);		// Extend Heap Because Free block not Found
			if(!b)				// Space Not Available
				return NULL;
		}
		else					// Appropriate Free Block Found
		{
			// Get Required Size for Your Block, Create Another Free block of Remaining size
			if(( b->size - s) >= BLOCK_SIZE + 4)
				split_block( b, s);	
			b -> free = 0;			// Set Block as Occupied
		}
	}
	else						// First Time Malloc is Called. Heap is Created
	{
		b = extend_heap( s);			
		if(!b)
			return NULL;
		base = (void *)b;			// Set Base
	}
	char *temp = (char *)b;
	temp += BLOCK_SIZE;
	return temp;
}

// Free Function
void free (void *x)
{
	struct block *temp;				// Just to Do Computation on Pointers
	temp = (struct block*)x;
	char *a = (char *)x;
	a = a - BLOCK_SIZE;
	temp = (struct block *)a;
	if(!valid(x))					// If Invalid Address
	{
		printf("Invalid Free Operation");
		return;
	}
	temp -> free = 1;				// Free up the Block
	// Merge Blocks
	if( temp->prev && temp-> prev-> free)		
		temp = fusion(temp->prev);
	if( temp->next)
	{
		if(temp->next->free)
			fusion(temp);
	}
	else
	{
		if(temp->prev)				// Last Node
			temp->prev ->next = NULL;
		else					// Single Node Left
			base = NULL;
		limit = (void *)temp;			// Update Break
	}
}

// Calloc Implementation
void * my_calloc ( size_t number , size_t size )
{
	size_t	*new;
	int	s4 ,i;
	new = my_malloc ( number * size );
	if (new) 
	{
		s4 = ( int) number;
		for ( i = 0; i < s4 ; i++)
			new[i] = 0;
	}
	return (new);
}
