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
	TCB_t *temp = newItem();
	void *stack = (void *) malloc(8192);
	init_TCB(temp, function, stack, 8192);
	addQueue(runQ, temp);

	return;
}

//------------//
// run Method //
//------------//
void run() {
	ucontext_t from, to;
	ucontext_t parent;
	from = parent;
	getcontext(&parent);
	to = (runQ->header->context);
	swapcontext(&parent, &(runQ->header->context));

	return;
}

//--------------//
// yield Method //
//--------------//
void yield() {
	ucontext_t from, to;	
	getcontext(&from);
	runQ->header->context = from;
	rotQueue(runQ);
	to = runQ->header->context;
	swapcontext(&from, &to);

	return;
}

#endif
