// Donald Lee Beadle
// CS 420
// HPF (NOT FUNCTIONING)
//------------------------------------------------------------------------------
#include <stdio.h>
#include <stdbool.h>
//------------------------------------------------------------------------------
// NODE TYPE and FUNCTIONS:
// Struct Node: Used to create a linked list of records. 
struct node
{
    char* jobName;
    int arrivalTime;
    int estimatedRunTime;
    int priority;
    int waitTime;
    int exitTime;
    int timeOfService;
    struct node *next
} *head, *tail;
// Struct Node Functions:
void insertRecord(char* job, int at, int ert, int p, int wt, int et, 
                  int tos, struct node *nextNode);
void seekRecords(int clockP); 
void trackPriority(struct node* target); // NOT IMPLEMENTED
//------------------------------------------------------------------------------
// QUEUE TYPE and FUNCTIONS:
// Struct QueueStruct: Creates a queue data structure.
typedef struct QueueStruct
{
    char* qJobName;
    int qArrivalTime;
    int qEstimatedRunTime;
    int qPriority;
    int qWaitTime;
    int qExitTime;
    int qTimeOfService;
    struct QueueStruct *next
} qNode;
struct QueueStruct *qHead, *qTail;
// Queue Functions:
void insertQ(char* job, int at, int ert, int p, int wt, int et, 
                  int tos, struct node* nextIn);
qNode* removeQ();
bool checkQ();
void swapNode(struct node* temp, struct node* head); // NOT IMPLEMENTED
//------------------------------------------------------------------------------
// I/O FUNCTIONS:
void readInput();
void writeOutput(char* job, int at, int wt, int et);
// Global variable to track jobs
int jobs = 0;
//------------------------------------------------------------------------------
//MAIN DRIVER:
//------------------------------------------------------------------------------
int main() 
{
    int system = 0;
    int clockPulse = 0;
    qNode *selectedN;
    
    // Initialize queue head and tail to NULL.
    qHead = NULL;
    qTail = NULL;
    
    readInput();

    while(1) // Loop only breaks when jobs are serviced.
    {
        if(system != 0) // Check for current job completion.
        {
            --system; // Decrement system.
            
            if(system == 0 && jobs != 0)
            {
                --jobs; // Decrement jobs.
            }
        }
        
        if(system == 0 && jobs == 0) // Check current status of jobs.
        {
            exit(0); // Successful exit.
        }
        
        seekRecords(clockPulse);
        
        if(system == 0 && checkQ() == false) // Check for arrivals on wait q.
        {
         
            selectedN = removeQ();
            selectedN->qTimeOfService = clockPulse;
            selectedN->qWaitTime = (selectedN->qTimeOfService 
                                    - selectedN->qArrivalTime);
            selectedN->qExitTime = (selectedN->qTimeOfService 
                                    + selectedN->qEstimatedRunTime);
            printf("%s %d %d %d \n", selectedN->qJobName, selectedN->qArrivalTime, 
                    selectedN->qWaitTime, selectedN->qExitTime);
                    
            writeOutput(selectedN->qJobName, selectedN->qArrivalTime, 
                        selectedN->qWaitTime, selectedN->qExitTime);
                    
            system = selectedN->qEstimatedRunTime;
        }
        
        ++clockPulse;// Increment clock pulse before looping. 
    }
    
    return 0;
}
//------------------------------------------------------------------------------
// Inserts a record into the linked list. 
void insertRecord(char* job, int at, int ert, int p, int wt, int et, int tos, 
                  struct node *nextIn)
{
    struct node *node = malloc(sizeof(struct node));
    
    node->jobName = malloc(5); // Allocate memory.
    
    // Assign member variables of struct node. 
    strcpy(node->jobName, job);
    node->arrivalTime = at;
    node->estimatedRunTime = ert;
    node->priority = p;
    node->waitTime = wt;
    node->exitTime = et;
    node->timeOfService = tos;
    node->next = NULL;
    
    if(head == NULL)
    {
        head = node;
        tail = node;
    }
    
    else
    {
        tail->next = node;
        tail = node;
    }
    
}
//------------------------------------------------------------------------------
// Searches the list of records based on the clock pulse at that time. 
void seekRecords(int clockP)
{
    struct node *selectedN = head;
    
    while(selectedN != NULL)
    {
        if(selectedN->arrivalTime == clockP) // If matches clock pulse
        {
            insertQ(selectedN->jobName, selectedN->arrivalTime, 
                    selectedN->estimatedRunTime,selectedN->priority, 
                    selectedN->waitTime, selectedN->exitTime,
                    selectedN->timeOfService, selectedN->next);
        }
        
        // Move pointer to next node in list. 
        selectedN = selectedN->next;
    }
}
//------------------------------------------------------------------------------
// NOT IMPLEMENTED
void trackPriority(struct node* target)
{
    
}
//------------------------------------------------------------------------------
// Inserts a record from the linked list into the queue.
void insertQ(char* job, int at, int ert, int p, int wt, int et, int tos, 
             struct node *nextIn)
{
    qNode* target;
    
    // Allocate memory.
    target = (qNode *)malloc(sizeof(qNode));
    target->qJobName = malloc(5); 
    
    // Assign member variables of type QueueStruct.
    strcpy(target->qJobName, job);
    target->qArrivalTime = at;
    target->qEstimatedRunTime = ert;
    target->qPriority = p;
    target->qWaitTime = wt;
    target->qExitTime = et;
    target->qTimeOfService = tos;
    target->next = NULL;
    
    // Set queue head and queue tail to target (item inserted) if q head == NULL.
    if(qHead == NULL)
    {
        qHead = target;
        qTail = target;
    }
    
    // Else set tail prt next to target and tail to target.
    else
    {
        qTail->next = target;
        qTail = target;
    }
}
//------------------------------------------------------------------------------
// Removes a record from the queue. Returns a qNode ptr type of removed node. 
qNode* removeQ()
{
    qNode *target;
    qNode *rNode;
    
    // Allocate memory.
    target = (qNode *)malloc(sizeof(qNode));
    rNode = (qNode *)malloc(sizeof(qNode));

    // Assign member variables of type QueueStruct
    rNode->qJobName = qHead->qJobName;
    rNode->qArrivalTime = qHead->qArrivalTime;
    rNode->qEstimatedRunTime = qHead->qEstimatedRunTime;
    rNode->qPriority = qHead->qPriority;
    rNode->qWaitTime = qHead->qWaitTime;
    rNode->qExitTime = qHead->qExitTime;
    rNode->qTimeOfService = qHead->qTimeOfService;
    
    // Move pointers.
    target = qHead;
    qHead = qHead->next;
    
    free(target); // Deallocates memory of malloc
    
    return rNode;
}
//------------------------------------------------------------------------------
// Conditional check to see if the queue is empty. Returns a boolean of true or
// false.
bool checkQ()
{
    if(qHead == NULL)
    {
        return true;
    }
    
    else
    {
        return false; 
    }
}
//------------------------------------------------------------------------------
// NOT IMPLEMENTED
void swapNode(struct node* temp, struct node* head)
{
    
}
//------------------------------------------------------------------------------
// Reads the input file and (if exists) creates list of records.
void readInput()
{
    FILE* fin;
    char fileName[80];
    char jobName[5]; // Max job name of 5 chars.
    int at, ert, p = 0;
    
    printf("Enter a filename: ");
    scanf("%s", fileName);
    
    fin = fopen(fileName, "r");
    
    if(fin == NULL)
    {
        printf("FILE NOT FOUND\n");
        exit(1); // Error exit code
    }
    
    else
    {
        printf("File ");
        printf("%s", fileName);
        printf(" is found\n");
    }
    
    // Read until EOF
    while(fscanf(fin, "%s %d %d %d", jobName, &at, &ert, &p) != EOF)
    {
        insertRecord(jobName, at, ert, p, 0, 0, 0, NULL);
        jobs++;// Increment number of jobs for tracking
    }
    
    fclose(fin);
}
//------------------------------------------------------------------------------
// Writes the results to a file "outFile.txt". 
void writeOutput(char* job, int at, int wt, int et)
{
    FILE* fout;
    fout = fopen("hpf_outFile.txt", "a");
    
    if(fout == NULL)
    {
        printf("CANNOT BUILD RESULTS FILE!!!\n");
        exit(1); // Error Exit
    }
    
    fprintf(fout, "%s %d %d %d \n", job, at, wt, et);
}
//------------------------------------------------------------------------------