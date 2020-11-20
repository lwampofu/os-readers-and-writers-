/*
Lwazilwenkosi Mpofu
*/
#include "threads.h"
//#include "tcb.h"
//Semaphore data structure: A value field and a queue of TCBs

typedef struct Semaphore{
	int value;
	struct Queue *sQ;
} Semaphore;

//InitSem(semaphore, value): Initializes the value field with the specified value

void initSem(struct Semaphore *S,int x){
	
	// S=(struct Semaphore*)malloc(sizeof(struct Semaphore));
	S->sQ =(struct Queue*)malloc(sizeof(struct Queue));	
	initQueue(S->sQ);
	S->value = x;
}

/*P(semaphore): The P routine decrements the semaphore, and if the value is 0 or less than zero then blocks the process in the queue associated with the semaphore.*/
void P(struct Semaphore* S, int thread_id){
	while (1){
		//block when S<=0
		if(S->value<=0){
			/*if(thread_id>0){
				printf("\n Producer %d is waiting \n", thread_id);
			}

			else
			{
				printf("\n Consumer %d is waiting \n", -thread_id);
			}*/
			//create a new queue
			//delete the TCB of the thread from the ReadyQ
			TCB_t *tcb = delQueue(&RunQ);
			// printf("%d\n", S->sQ == NULL);
			addQueue(S->sQ, tcb);
			
			// if(&RunQ == NULL){
			if(RunQ.head == NULL){
				exit(0);
			}
			swapcontext(&(S->sQ->tail->context), &(RunQ.head->context));
		}
		else{ 
			//decrement value if S>0
			//decrement semaphore value
			S->value--;
			return;
		}
	}
}


/*V(semaphore): The V routine increments the semaphore, and if the value is 0 or negative,then takes a PCB out of the semaphore queue and puts it into the run queue. Note: The V routine also "yields" to the next runnable process. //this is important.*/
void V(struct Semaphore *S){
	//increment S
	
	// if (S->value <=0){
	if(S->sQ->head != NULL){
		/*unblock one process delete the head of semQ*/
		//add at the end of the RunQ
		
		struct TCB_t *tcb = delQueue(S->sQ);
		addQueue(&RunQ,tcb);
	}
	S->value++;
	//"yields" to the next runnable process
	//yield(&RunQ);

}


