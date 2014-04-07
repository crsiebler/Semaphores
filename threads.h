// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 2
// Description: Holds routines to start threads, yield, and run

#ifndef THREADS_H
#define THREADS_H

//---------------//
// Include Files //
//---------------//
#include "q.h"

//-----------------------------//
// Global Variable Declaration //
//-----------------------------//
struct queue *runQ;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void startThread(void (*function)(void));
void run();
void yield();

//---------------------//
// start_thread Method //
//---------------------//
void startThread(void (*function)(void)) {
	TCB_t *temp = newItem();	// Create a new TCB to store process
	void *stack = (void *) malloc(8192);	// Allocate the stack memory
	init_TCB(temp, function, stack, 8192);	// Initialize the new TCB
	addQueue(runQ, temp);	// Put the new TCB into the Run Queue

	return;
}

//------------//
// run Method //
//------------//
void run() {
	// Declare the context of the first TCB
	ucontext_t parent;
	
	// Grab the original conext
	getcontext(&parent);
	
	// Swap to the first TCB in Run Queue
	swapcontext(&parent, &(runQ->header->context));

	return;
}

//--------------//
// yield Method //
//--------------//
void yield() {
	// Declare the context of the threaded TCBs
	ucontext_t from, to;
	
	// Grab the running processes context
	getcontext(&from);
	
	// Update the context of the current process
	runQ->header->context = from;
	
	// Move the process to the end of the Queue
	rotQueue(runQ);
	
	// Grab the next process in the Run Queue
	to = runQ->header->context;
	
	// Swap the currently running process to the next process in the Queue
	swapcontext(&from, &to);

	return;
}

#endif
