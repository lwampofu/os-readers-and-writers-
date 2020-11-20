/*
 *Lwazilwenkosi Mpofu
 */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "tcb.h"
 

struct Queue {
	struct TCB_t* head; //points to first element
	struct TCB_t* tail;//points to last element
	
};

/*
 *newItem-pointer to a new q-element		
 */
struct TCB_t* newItem()
{
	struct TCB_t *element = (struct TCB_t*)malloc(sizeof(struct TCB_t));
	return element;
}

struct Queue* newQueue(){

	struct Queue* newQ = (struct Queue*) malloc(sizeof(struct Queue));
	return newQ;
}

	
void initQueue(struct Queue *queue) {
	queue->head=NULL;	// initialize head to NULL
	queue->tail=NULL;
}


/* freeItem
 *
 */
void freeItem(struct TCB_t *element)
{
	free(element);
}


void addQueue(struct Queue *queue, struct TCB_t *item) {
	// Case where queue is empty, queue->head is NULL
	if (queue->head == NULL) {
		/*Insert item as first element*/
		queue->head = item; /*head points to first element*/					
		queue->head->prev = item;
		queue->tail= item;	// next points to itself 
		queue->head->next = item;
	} else {
		queue->tail->next=item;
		item->prev=queue->tail;
		item->next=queue->head;
		queue->head->prev=item;
		queue->tail=item;
	}
}

/*
*Delete Queue
*/
struct TCB_t* delQueue(struct Queue *queue){
	struct TCB_t *temp = queue->head;
	
	
	if (queue->head==NULL){
		printf("The queue is empty!!!!");
	}
	
	else if(queue->head->next==queue->head){
		queue->head=NULL;
		queue->tail=NULL;
	}
	
	else{
		
		queue->head->next->prev=queue->head->prev;
		queue->tail->next = queue->head->next;
		queue->head=queue->head->next;
	}
	return temp;
}

/* RotateQueue
*
*/
void rotateQueue(struct Queue *queue) {
	addQueue(queue, delQueue(queue));
}


/*void display(struct Queue *queue){
 struct TCB_t *temp;
 temp = queue->head; 
 if(queue->head==0){
 printf("The queue is empty!");
}
 else{
 	while(temp!=queue->tail){
 	printf("\n");
 	printf("%d",temp->context);
 	temp=temp->next;
	}
	printf("\n");
	printf("%d",temp->context);
 	printf("\n");

 }
 }*/




