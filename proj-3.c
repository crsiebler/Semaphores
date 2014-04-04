// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 3
// Description: Main file which holds the threads for Producer-Consumer.

//---------------//
// Include Files //
//---------------//
#include "sem.h"

//---------------------//
// Global Declarations //
//---------------------//
struct semaphore *sem;
int global = 0;

//--------------------//
// Threaded Functions //
//--------------------//
void f1();
void f2();

void f1(){
	int local = 0;
	while(1){
		P(sem);
		//crit section
		printf("thread 1:\tg_%d l_%d", global, local);
		global++;
		local++;
		V(sem);

	}
}

void f2(){
	int local = 0;
	while(1){
		P(sem);
		//crit section
		printf("thread 2:\tg_%d l_%d", global, local);
		global++;
		local++;
		V(sem);
	}
}

//-------------//
// main Method //
//-------------//
int main() {
	sem = (struct semaphore*) malloc(sizeof(struct semaphore));
	initSem(sem, 1);
	startThread(f1);
	startThread(f2);
	run();

	return 0;
}
