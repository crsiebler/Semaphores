// Name: Cory Siebler & Marcus Finney
// Class: CSE430 #12109
// Assignment: Project 3
// Description: Main file which holds the threads for Producer-Consumer.

//---------------//
// Include Files //
//---------------//
#include "sem.h"

//--------------------//
// Global Definitions //
//--------------------//
#define SHELF_SIZE 5

//---------------------//
// Global Declarations //
//---------------------//
int in = 0;
int out = 0;
int global = 0;
int shelf[SHELF_SIZE];
struct semaphore *sem;
struct semaphore *empty;
struct semaphore *full;

//----------------------------//
// Method Forward Declaration //
//----------------------------//
void printShelf();
void initShelf();

//--------------------//
// Threaded Functions //
//--------------------//
void f1();
void f2();
void producer1();
void producer2();
void consumer1();
void consumer2();

//-----------//
// f1 Method //
//-----------//
void f1() {
	int local = 0;

	if (DEBUG) printf("THREAD 1: STARTED!!!\n");

	while (1) {
		P(sem);
		// Critical Section
		printf("THREAD 1:\tGLOBAL: %d\tLOCAL: %d\n", global, local);
		sleep(1);
		global++;
		local++;
		// End Critical Section
		V(sem);
	}

	return;
}

//-----------//
// f2 Method //
//-----------//
void f2() {
	int local = 0;

	if (DEBUG) printf("THREAD 2: STARTED!!!\n");

	while (1) {
		P(sem);
		// Critical Section
		printf("THREAD 2:\tGLOBAL: %d\tLOCAL: %d\n", global, local);
		sleep(1);
		global++;
		local++;
		// End Critical Section
		V(sem);
	}

	return;
}

//------------------//
// producer1 Method //
//------------------//
void producer1() {
	while (1) {
		P(empty);
		// Critical Section
		shelf[in] = 1;	
		in = (in + 1) % SHELF_SIZE;
		printShelf("PRODUCER 1");
		// End Critical Section
		V(full);
	}

	return;
}

//------------------//
// producer2 Method //
//------------------//
void producer2() {
	while (1) {
		P(empty);
		// Critical Section
		shelf[in] = 1;	
		in = (in + 1) % SHELF_SIZE;
		printShelf("PRODUCER 2");
		// End Critical Section
		V(full);
	}

	return;
}

//------------------//
// consumer1 Method //
//------------------//
void consumer1() {
	while (1) {
		P(full);
		// Critical Section
		shelf[out] = 0;
		out = (out + 1) % SHELF_SIZE;
		printShelf("CONSUMER 1");
		// End Critical Section
		V(empty);
	}

	return;
}

//------------------//
// consumer2 Method //
//------------------//
void consumer2() {
	while (1) {
		P(full);
		// Critical Section
		shelf[out] = 0;
		out = (out + 1) % SHELF_SIZE;
		printShelf("CONSUMER 2");
		// End Critical Section
		V(empty);
	}

	return;
}

//-------------------//
// printShelf Method //
//-------------------//
void printShelf(char *functionName) {
	printf("%s\t-\t1: %d\t2: %d\t3: %d\t4: %d\t5: %d\n", functionName, shelf[0], shelf[1], shelf[2], shelf[3], shelf[4]);
	sleep(1);

	return;
}

//------------------//
// initShelf Method //
//------------------//
void initShelf() {
	int i;

	for (i = 0; i < SHELF_SIZE; i++) {
		shelf[i] = 0;
	}

	return;
}

//-------------//
// main Method //
//-------------//
/*
This is Main for Method 1 Testing

int main() {
	sem = (struct semaphore*) malloc(sizeof(struct semaphore));
	runQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(runQ);
	initSem(sem, 1);

	startThread(f1);
	startThread(f2);
	run();

	return 0;
}
*/
int main() {
	empty = (struct semaphore*) malloc(sizeof(struct semaphore));
	full = (struct semaphore*) malloc(sizeof(struct semaphore));

	runQ = (struct queue*) malloc(sizeof(struct queue));

	initQueue(runQ);

	initSem(empty, SHELF_SIZE);
	initSem(full, 0);

	startThread(consumer1);
	startThread(consumer2);
	startThread(producer1);
	startThread(producer2);

	run();

	return 0;
}
