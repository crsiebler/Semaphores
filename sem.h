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
	int value;
	struct queue *sleepQ;
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
	sem->sleepQ = (struct queue*) malloc(sizeof(struct queue));
	initQueue(sem->sleepQ);

	sem->value = value;

	return;
}

//----------//
// P Method //
//----------//
void P(semaphore *sem) {
	struct TCB_t *t; 

	sem->value--;

	if (sem->value < 0) {
		t = delQueue(runQ);
		addQueue(sem->sleepQ, t);
		swapcontext(&(t->context), &(runQ->header->context));
	}

	return;
}

//----------//
// V Method //
//----------//
void V(semaphore *sem) {
	struct TCB_t *t; 

	sem->value++;

	if (sem->value <= 0) {
		t = delQueue(sem->sleepQ);
		addQueue(runQ, t);
	}

	yield();

	return;
}

#endif
