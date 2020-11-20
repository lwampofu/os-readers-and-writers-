/*
* Lwazilwenkosi Mpofu
*/
#include "sem.h"

struct Semaphore W_Sem;
struct Semaphore R_Sem;
int i = 0;
int rwc = 0;
int wwc = 0;
int rc = 0;
int wc = 0;
int r_num,w_num,num_readers_writers,ID;

//writer
void writer(int writerID){
	if(rc>0||wc>0||rwc>0||wwc>0){
		wwc++;
		P(&W_Sem,writerID);
		wwc--;
	}
	wc++;
	i = -writerID;
	printf("\n This is the %d th writer writing value i = %d \n", -writerID, i );
	yield(&RunQ);
	printf("\n This is the %d th writer verifying value i = %d \n", -writerID, i );
	//writer exit
	wc--;	
	if(rwc>0){
		for(int x = 0; x<rwc;x++){
			V(&R_Sem);
		}

	}
	else if(wwc>0){
		V(&W_Sem);
	}
	TCB_t *tcb = delQueue(&RunQ);
	swapcontext(&(tcb->context),&(RunQ.head->context));

}

//Reader Entry
void reader(int readerID){
	if(wwc>0||wc>0){
		rwc++;
		P(&R_Sem,readerID);
		rwc--;
	}
	rc++;
	printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i );
	yield(&RunQ);
	//display(&RunQ);
	printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i );


	//Reader Exit
	rc--;
	if(rc==0 && wwc>0){
		V(&W_Sem);
	}
	TCB_t *tcb = delQueue(&RunQ);
	swapcontext(&(tcb->context),&(RunQ.head->context));
}

int main(){
	
	int local = 0;
	
	scanf("%d,%d\n",&r_num,&w_num);
	int num_readers_writers = r_num+w_num;
    	initSem(&W_Sem,0);
    	initSem(&R_Sem,0);
	initQueue(&RunQ);

	//run thread
	while(local < num_readers_writers){
		scanf("%d\n",&ID);
		if(ID>0){
			start_thread(reader, ID, &RunQ);
		}
		else
		{
			start_thread(writer,ID,&RunQ);
		}		
		local++;	
		}
	run(&RunQ);
}




