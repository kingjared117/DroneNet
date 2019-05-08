#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define GRID_SIZE 100
#define FREQ_NUM 3
#define BROADCAST_RANGE 10
int numNodes=0;
pthread_mutex_t currentlyLooking;
unsigned int whichTurn[GRID_SIZE][GRID_SIZE];
unsigned int currTurn=0;

struct Node
{
  int currFreq;
  pthread_mutex_t currentlyLooking;
  int xcoord, ycoord;
};

struct ListNode
{
  char isHead;
  struct Node *currNode;
  struct ListNode *nextNode
};

struct Node nodeGrid[GRID_SIZE][GRID_SIZE];


void enqueue(struct Node* toEnqueue, struct NodeList* head){
  struct NodeList *tmpList = head;
  while(tmpList = tmpList->nextNode);
	
  tmpList->nextNode = (struct ListNode*)malloc(sizeof(struct ListNode));
  tmpList->nextNode->currNode = toEnqueue;
}

struct ListNode *dequeue(struct ListNode* nodeList){
  struct ListNode *next = nodeList->nextNode;
  
  int i;

  free(nodeList);
  return next;
}

void nodeOperation(struct Node *self){
  while(1){
    pthread_mutex_lock(currentlyLooking);
    int i, j;
    for(i=-BROADCAST_RANGE;i<BROADCAST_RANGE;i++){
      for(j=-BROADCAST_RANGE;j<BROADCAST_RANGE;j++){
	if(!(self->xcoord+i>BROADCAST_RANGE ||
             self->ycoord+j>BROADCAST_RANGE ||
	     self->xcoord+i<0 || self->ycoord<0)){
	    
	  if(whichTurn[i][j]>self->turn){
	    self->turn=whichTurn[i][j]+1;
	    whichTurn[self->xcoord][self->ycoord]=self->turn;
          }
	    
	}
      }
    }
    pthread_mutex_unlock(currentlyLooking);
    
    while(self->turn!=currTurn){
      pthread_cond_wait(); // wait on condition variable
    }
    //do stuff

    whichTurn[xcoord][ycoord]=0;
    
    int numLeft = 0;
    for(i=0;i<GRID_SIZE;i++){
      for(j=0;j<GRID_SIZE){
	if (whichTurn[i][j]==currTurn){
	  numLeft++;
	}
      }
    }
    if(!numLeft){
      currTurn=self->turn+1;
    }
    self->turn=0;
  }

  
    
}
