/*
*Lwazilwenkosi Mpofu
*/
#include "q.h"
#include <stdio.h>

struct Queue RunQ;

void start_thread(void (*function)(int),int a,struct Queue *queue) { 
	void *stackP = (void*) malloc(8192); 
	//allocate stack
	struct TCB_t *tcb =(struct TCB_t*) malloc(sizeof(struct TCB_t)); //allocate a TCB
	init_TCB(tcb, function, stackP, 8192,a); //initialize TCB
	addQueue(queue, tcb);
}


void run(struct Queue *queue) { 
	// real code
	ucontext_t parent; // get a place to store the main context, for faking
	getcontext(&parent); // magic sauce
	swapcontext(&parent, &(queue->head->context));// start the first thread 
}


void yield(struct Queue *queue) {
	
	rotateQueue(&RunQ); //rotate queue
	swapcontext(&(queue->tail->context), &(queue->head->context));
}


