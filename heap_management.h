/*
	Author: Tarun Jain
	Roll Number: MT2015120
	File: RTOS Assignment 1 - Question 1 -Header File
	Problem Statement: Implement the malloc, free, calloc, realloc Function using your own Heap(Static array of 10240 Bytes)
*/

// Macros
#define MEM_SIZE 1024				// Size of Heap (Static Array)
#define BLOCK_SIZE sizeof(struct block)		// Size of Meta Data Block

// Header Files
#include <stdio.h>
#include <stdlib.h>

// Global Variables
char *end_limit;				// Last Address of Heap
char *limit;					// Break Position of Heap
char memory[MEM_SIZE];				// Memory or Heap
extern void *base;				// Base Address of Heap Memory
struct block *traverse;				// To Traverse to End


// Structure of Meta-data
struct block
{
	size_t size;				// Size of Space Allocated to a Block
	struct block *next;			// Next Block Address
	struct block *prev;			// Previous Block Address
	int free;				// Free(1) or Occupied(0)
};

// Function Prototype
void* my_malloc(size_t);			// Malloc Function
void* my_calloc(size_t, size_t);		// Calloc Function
void init();					// Initialization Function
void* my_sbrk(size_t);				// sbrk Function
void demo_malloc();				// Demonstrating Malloc
struct block* find_block( size_t);		// Find Free Block
struct block* extend_heap( size_t);		// Extend Heap
void split_block( struct block*, size_t);	// Split Block
struct block* fusion(struct block *);		// Fusion of Two Free Blocks
int valid( void*);				// Valid Function
void free( void*);				// Free Memory
void* my_realloc( void *, size_t);		// Realloc Function
void copy_data (void *, void *);		// Copy Data
size_t free_space();				// Free Space
void defragment_my_heap();			// Defragment Heap
