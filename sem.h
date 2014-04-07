// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 3
// Description: Holds the functions to create and modify Semaphores. InitSem(semaphore, value) initializes
//		a new Semaphore with the value equal to the parameter. P(semaphore) will decrement the value
//		and block the process if the value is less than zero. V(semaphore) will increment the value
//		and call the aprocess in the PCB and puts in the RunQ if the value is 0 or negative.

#ifndef SEM_H
#define SEM_H

//---------------//
// Include Files //
//---------------//
#include "threads.h"

//----------------------------//
// Data Structure Declaration //
//----------------------------//
typedef struct semaphore {
	int value;	// Holds the Semaphore value that is incremented & decremented
	struct queue *sleepQ;	// Stores the Queue to hold the blocked processes
} semaphore;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void initSem(semaphore*, int);
void P(semaphore*);
void V(semaphore*);

//----------------//
// initSem Method //
//----------------//
void initSem(semaphore *sem, int value) {
	// Allocate memory for the Sleep Queue
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));
	
	// Initialize the Head of the Sleep Queue
	initQueue(sem->sleepQ);

	// Initialize the value of the Semaphore
	sem->value = value;

	return;
}

//----------//
// P Method //
//----------//
void P(semaphore *sem) {
	// Declare a temporary TCB to hold the popped process
	struct TCB_t *t; 

	// Decrement the Semaphore value
	sem->value--;

	// Check if the Semaphore value is zero or negative
	if (sem->value < 0) {
		// Take the current process from the Run Queue
		t = delQueue(runQ);
		
		// Block the process
		addQueue(sem->sleepQ, t);
		
		// Swap to the next process in the Run Queue
		swapcontext(&(t->context), &(runQ->header->context));
	}

	return;
}

//----------//
// V Method //
//----------//
void V(semaphore *sem) {
	// Declare a temporary TCB to hold the popped process
	struct TCB_t *t; 

	// Increment the Semaphore Value
	sem->value++;

	// Check if the Semaphore value is positive
	if (sem->value <= 0) {
		// Take a process from the Semaphore's Sleep Queue
		t = delQueue(sem->sleepQ);
		
		// Put the process in the Run Queue
		addQueue(runQ, t);
	}

	// Call the next process to eliminate bounded waiting
	yield();

	return;
}

#endif
