// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 1
// Description: Stores routines to initialize, add, rotate, and delete queues.
//		Also has function to create a new element in the queue and to free deleted elements.

#ifndef Q_H
#define Q_H

//---------------//
// Include Files //
//---------------//
#include <stdlib.h>
#include <unistd.h>
#include "tcb.h"

//----------------------------//
// Data Structure Declaration //
//----------------------------//
typedef struct queue {
	struct TCB_t *header; // Pointer to 1st Element in Queue
} queue;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void initQueue(struct queue*);	// creates an empty queue, pointed to by the variable head
void addQueue(struct queue*, struct TCB_t*);	// adds a queue item, pointed to by "item", to the queue pointed to by head
void rotateQ(struct queue*);	// Moves the header pointer to the next element in the queue
struct TCB_t* delQueue(struct queue*);	// deletes an item from head and returns a pointer to the deleted item
struct TCB_t* newItem();	// returns a pointer to a new q-element

//-------------------//
// Routine Functions //
//-------------------//

//------------------//
// initQueue Method //
//------------------//
void initQueue(struct queue *head) {
	// Allocate space for new Queue
	head->header = NULL;
	
	return;
}

//-----------------//
// addQueue Method //
//-----------------//
void addQueue(struct queue *head, struct TCB_t *item) {
	// Check for 0 elements in Queue
	if (head->header != NULL) {
		if (head->header->next != NULL) {
			// Queue is not empty, break chain and insert new item to end
			item->prev = head->header->prev; // Add new link at end of chain
			item->next = head->header; // Attach new link to beginning of chain
			head->header->prev->next = item; // Make link from last element
			head->header->prev = item; // Make link to end from head
		} else {
			// Queue has 1 element so create new chain
			head->header->next = item; // Add new link to new item
			head->header->prev = item; // Create chain linking to last element
			item->next = head->header; // Create chain linking to first element
			item->prev = head->header; // Add new link to old item
		}
	} else {
		// Queue is empty
		head->header = item; // Make header point to new item
		item->prev = NULL; // Make pointer to itself
		item->next = NULL; // Make pointer to itself
	}
	
	return;
}

//-----------------//
// rotQueue Method //
//-----------------//
void rotQueue(struct queue *head) {
	// Move head pointer to next Element
	// Put first element at end of Queue
	addQueue(head, delQueue(head));
	
	return;
}

//-----------------//
// delQueue Method //
//-----------------//
struct TCB_t* delQueue(struct queue *head) {
	// Grab the first element in the Queue
	struct TCB_t *item = head->header;

	// Check for empty Queue
	if (head->header != NULL) {
		// Check for single or multiple elements in Queue
		if (head->header->next != NULL) {
			// Grab the last element and next element
			// Assign next and prev to recreate chain
			head->header->prev->next = head->header->next;
			head->header->next->prev = head->header->prev;

			// Set the Queue header to next
			head->header = head->header->next;
		} else {
			// Remove single element from Queue
			head->header = NULL;
		}
	}
	
	return item;
}

//----------------//
// newItem Method //
//----------------//
struct TCB_t* newItem() {
	// Allocate memory for new Queue element
	struct TCB_t *item = (struct TCB_t*) malloc(sizeof(struct TCB_t));
	
	// Verify memory is allocated
	if (!item) {
		item->prev = NULL; // Initialize Previous Element
		item->next = NULL; // Initialize Next Element
	}

	return item;
}

#endif
