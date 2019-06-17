//------------------------------------------------------------------------------
//	Donald Lee Beadle
//	CS 420
//	Scheduler 
//	Round Robin (RR) (NOT CURRENTLY FUNCTIONAL)
//	This program implements the RR scheduling algorithm. 
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#define MAX (100) // Global definition for MAX number of jobs
//------------------------------------------------------------------------------
// Data Structures
//------------------------------------------------------------------------------
struct Record
{
	char* jobName;
	int arrivalTime;
	int estRunTime;
	int priority;
	int serviceTime;
	int waitTime;
};
//------------------------------------------------------------------------------
struct List
{
	// Record of job
	struct Record rJob[MAX];  
	int size;
};
//------------------------------------------------------------------------------
struct ListNode
{
	struct Record aRec;
	struct ListNode* nextRec;
};
//------------------------------------------------------------------------------
struct Queue
{
	int queueSize;
	struct ListNode* head;
	struct ListNode* currentJob;
};
//------------------------------------------------------------------------------
// Function Declarations
//------------------------------------------------------------------------------
// Struct List Functions:
bool isListEmpty(struct List jobList);
int getNextTime(struct List* jobList);
void reduceList(int position, struct List* targetList);
// Struct ListNode Functions
struct ListNode* getNextPointer(struct ListNode* aNode);
struct ListNode* getHeadPointer(struct Queue* aQueue);
void setNullPointer(struct ListNode* aNode);
// Struct Queue Functions:
bool isQueueEmpty(struct Queue waitQ);
void enqueue(struct List* jobList, struct Queue* wQ);
void dequeue(struct Queue* wQ);
//void sortQueue(const int q, struct Queue* wQ);
// Misc. Functions
void showOutput(struct Queue q, int CP);
void readInputFile(FILE* fp, struct List* jobList);
void writeToFile(int CP, FILE* fp, struct Queue q);
void clockLoop(FILE* fp, struct List listObj, struct ListNode* nodeObj, 
                struct Queue qObj);
//------------------------------------------------------------------------------
// Main Driver:
int main() 
{
	int numberOfJobsProcessed = 0;
	struct List allJobs;
	struct ListNode* currentNode;
	struct Queue waitQ;
	FILE* fp;
	
	allJobs.size = 0;
	waitQ.queueSize = 0;
	
	setNullPointer(currentNode);
	setNullPointer(waitQ.head);
	
	waitQ.currentJob = getHeadPointer(&waitQ); 
	readInputFile(fp, &allJobs);
	numberOfJobsProcessed = allJobs.size;
	
	fp = fopen("fcfs_outFile.txt", "w+");
	
	if(fp == NULL)
    {
        printf("CANNOT BUILD RESULTS FILE!!!\n");
        exit(1); // Error code exit
    }
    
    else
    {
    	printf("fcfs_outFile.txt open for writng\n");
    }
	
	clockLoop(fp, allJobs, currentNode, waitQ);
	fclose(fp);
	
	printf("numberOfJobsProcessed: %d\n", numberOfJobsProcessed);
	
	return 0;
}
//------------------------------------------------------------------------------
// List Functions
//------------------------------------------------------------------------------
// Is List Empty Function: Returns TRUE if the size of the List is 0.
bool isListEmpty(struct List jobList)
{
	if(jobList.size == 0)
	{
		return true;
	}
	
	else
	{
		return false;	
	}		
}
//------------------------------------------------------------------------------
// Get Next Time Function: Returns the arrival time of the List item. If the List
// size is zero, returns a negative 1. 
int getNextTime(struct List* jobList)
{
	int headOfQIndex = 0;
	int nextTime = 0;
	int emptyListTime = -1; // Attain a value below zero
	int numOfJobs = jobList->size;
	
	if (numOfJobs == 0)
	{
		return emptyListTime;
	}
	
	else
	{
		nextTime = jobList->rJob[headOfQIndex].arrivalTime;
		return nextTime;
	}
}
//------------------------------------------------------------------------------
// Reduce List Function: Removes instance of Record from the List of records and 
// reduces the size of the List. 
void reduceList(int position, struct List* targetList)
{
	int index = 0;
	int nextIndex = index;
	int totalSize = targetList->size - 1;
	
	index = position;
	while(index < totalSize)
	{
		nextIndex++;
		targetList->rJob[index] = targetList->rJob[nextIndex];
		index++;
	}
	
   targetList->size--;
}
//------------------------------------------------------------------------------
// ListNode Functions
//------------------------------------------------------------------------------
// Get Next Pointer Function
// Return a ListNode* for the next record.
struct ListNode* getNextPointer(struct ListNode* aNode)
{
	aNode = aNode->nextRec;
	
	return aNode;
}
//------------------------------------------------------------------------------
// Get Head Pointer Function: Returns a ListNode* for the head of a queue 
// object. 
struct ListNode* getHeadPointer(struct Queue* aQueue)
{
	struct ListNode* aNode;
	aNode = aQueue->head;
	
	return aNode;
}
//------------------------------------------------------------------------------
// Set Null Pointer Function: Sets the passed Listnode* to NULL.
void setNullPointer(struct ListNode* aNode)
{
	aNode = NULL;
}
//------------------------------------------------------------------------------
// Queue Functions
//------------------------------------------------------------------------------
// Is Queue Empty Function: Returns TRUE of the head of the queue is NULL.
bool isQueueEmpty(struct Queue waitQ)
{
	if(waitQ.head == NULL || waitQ.queueSize == 0)
	{
		return true;
	}
	
	else
	{
		return false;
	}		
}
//------------------------------------------------------------------------------
// Enqueue Function: Adds a job to the waiting queue and resets size of List.
void enqueue(struct List* jobList, struct Queue* wQ)
{
	int resetIndex = 0; // Index of head node
	struct ListNode* currentNode; 
	setNullPointer(currentNode);
	
	// Is the queue empty? 
	if (isQueueEmpty(*wQ) == true)
	{
		wQ->head = (struct ListNode*)malloc(sizeof(struct ListNode));
		wQ->head->aRec = jobList->rJob[resetIndex];
		setNullPointer(wQ->head->nextRec);
		wQ->currentJob = getHeadPointer(wQ);
		wQ->queueSize++;
	}
	
	else
	{
		currentNode = getHeadPointer(wQ);
		
		// While list node pointer is NOT NULL
		while (currentNode->nextRec != NULL)
		{
			currentNode = getNextPointer(currentNode);
		}
		
		currentNode->nextRec = (struct ListNode*)malloc(sizeof(struct ListNode));
		currentNode->nextRec->aRec = jobList->rJob[resetIndex];
		setNullPointer(currentNode->nextRec->nextRec);
		wQ->queueSize++;
	}

	// Resize List of jobs for a job just enqueued
	reduceList(resetIndex, jobList);
}
//------------------------------------------------------------------------------
// Dequeue Function: Removes a job from the waiting queue. 
void dequeue(struct Queue* wQ)
{
	struct ListNode* currentNode; 
	struct ListNode* targetNode; 
	
	setNullPointer(currentNode);
	setNullPointer(targetNode);
	
	currentNode = getHeadPointer(wQ);
	
	// If head of waiting queue is current job
	if (wQ->head == wQ->currentJob)
	{
		wQ->head = getNextPointer(wQ->head);
		wQ->currentJob = getHeadPointer(wQ);
	}
	
	// Find correct list node
	else
	{
	    // While list node pointer is not current job in waiting queue
		while (currentNode->nextRec != wQ->currentJob)
		{
			currentNode = getNextPointer(currentNode);
		}
		
		targetNode = getNextPointer(currentNode);
		currentNode = getNextPointer(targetNode);
	}
	
	wQ->queueSize--;
}
//------------------------------------------------------------------------------
// Sort Queue Function: Sorts the queue jobs by time quantum level
//void sortQueue(const int q, struct Queue* wQ)
//{
//	
//}
//------------------------------------------------------------------------------
// MISC Functions
//------------------------------------------------------------------------------
// Show Output Function: Sends the output of the algorithm to the console. 
void showOutput(struct Queue q, int CP)
{
	printf("%s \t %d \t %d \t %d \t \n", q.currentJob->aRec.jobName, 
			q.currentJob->aRec.arrivalTime, 
			q.currentJob->aRec.waitTime, CP);
}
//------------------------------------------------------------------------------
// Read Input Function: Reads input file from the console and creates struct 
// List of struct Records. 
void readInputFile(FILE* fp, struct List* jobList)
{
    char fileName[80]; // Approx. page length
    char jobName[5]; 
    int at, ert, p, st, wt, index = 0;
	
	printf("Enter a filename: ");
    scanf("%s", fileName);
    
    fp = fopen(fileName, "r");
    
    if(fp == NULL)
    {
        printf("FILE NOT FOUND\n");
        exit(1); // Error exit code
    }
    
    printf("Read %s file \n", fileName);
	
	while (fscanf(fp, "%s %d %d %d", jobName, &at, &ert, &p) != EOF)
	{
		jobList->rJob[index].jobName = malloc(5);
		strcpy(jobList->rJob[index].jobName, jobName);
		jobList->rJob[index].arrivalTime = at;
		jobList->rJob[index].estRunTime = ert;
		jobList->rJob[index].priority = p;
		jobList->rJob[index].serviceTime = st;
		jobList->rJob[index].waitTime = wt;
		jobList->size++;
		index++;
	}

	fclose(fp);
}
//------------------------------------------------------------------------------
// Write to File Function: Writes the output of the algorithm to a file.
void writeToFile(int CP, FILE* fp, struct Queue q)
{
	fprintf(fp,"%s  %d  %d  %d\n", q.currentJob->aRec.jobName, 
			q.currentJob->aRec.arrivalTime, q.currentJob->aRec.waitTime, CP);
}
//------------------------------------------------------------------------------
// System Loop Function: Main loop used to simulate the CPU.
void clockLoop(FILE* fp, struct List listObj, struct ListNode* nodeObj, 
				struct Queue qObj)
{
	const int QUANTUM = 10;
	int usedQuantum = 0;
	int clockPulse = 0;
	int currentSTime = 0;
	int currentERTime = 0;
	
	while (isListEmpty(listObj) == false || isQueueEmpty(qObj) == false )
	{
		// Does the queue contain any jobs?
		if (isQueueEmpty(qObj) == false)
		{
			currentSTime = qObj.currentJob->aRec.serviceTime;
			currentERTime = qObj.currentJob->aRec.estRunTime;

			// Is the current service time >= estimated runtime?
			// If yes, current job is complete, print to console/file, dequeue
			if (currentSTime >= currentERTime)
			{
				//printf("Queue Size: %d\n", qObj.queueSize);
				showOutput(qObj, clockPulse);
				writeToFile(clockPulse, fp, qObj);
				dequeue(&qObj);
				usedQuantum++;
			}
			
			else
			{
				if(usedQuantum == QUANTUM)
				{
					printf("usedQuantum == QUANTUM\n");
				}
			}
		}
		
		// Check for arrivals and enqueue
		// While next job arrival time matches with clock pulse
		while (getNextTime(&listObj) == clockPulse)
		{
			enqueue(&listObj, &qObj);
		}
		
		// Does the queue contain any jobs?
		if (isQueueEmpty(qObj) == false)
		{
			qObj.currentJob->aRec.serviceTime++;
			nodeObj = getHeadPointer(&qObj);
			
			// While a queue node is NOT NULL
			while (nodeObj != NULL)
			{
				// If queue node is NOT the current job
				// Increment wait time of an instance of a job
				if (nodeObj != qObj.currentJob)
				{
					nodeObj->aRec.waitTime++;
				}
				
				nodeObj = getNextPointer(nodeObj);
			}
		}
		
		usedQuantum++;
		clockPulse++;
	}
	
	printf("File Written \n");
	printf("Clock Pulse: %d\n", clockPulse);
	printf("Queue Size: %d\n", qObj.queueSize);
	printf("Current List Size: %d\n", listObj.size);
}
//------------------------------------------------------------------------------

