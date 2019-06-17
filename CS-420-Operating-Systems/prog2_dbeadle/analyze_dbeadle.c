//------------------------------------------------------------------------------
//	Donald Lee Beadle
//	CS 420
//	Scheduler Algorithm Analysis
//	This program calls the four scheduling algorithms of FCFS, HPF, SRT, and RR
//  and generates outfiles for statistical analysis. 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define MAX (100) // Global definition for MAX number of jobs
//------------------------------------------------------------------------------
// Data Structures: 
//------------------------------------------------------------------------------
struct Record
{
	char* jobName;
    int arrivalTime;
    int waitTime;
    int clockPulse;
};
//------------------------------------------------------------------------------
struct List
{
	// Record of job
	struct Record rJob[MAX];  
	int size;
};
//------------------------------------------------------------------------------
// Function Declarations:
//------------------------------------------------------------------------------
void runScheduler();
void readInputFile(FILE* fp, char* name, struct List* jobList);
void showOutput(struct List* jobList);
double findMean(struct List* jobList);
double findVar(const int mean, struct List* jobList);
//------------------------------------------------------------------------------
// Main Driver:
int main() 
{
	struct List fcfsJobs, hpfJobs, srtJobs, rrJobs;
	double fcfsMean, hpfMean, srtMean, rrMean = 0;
	double fcfsVar, hpfVar, srtVar, rrVar = 0;
	FILE* fp = NULL;
	char* fcfsName = "fcfs_outFile.txt";
	char* hpfName = "hpf_outFile.txt";
	char* srtName = "srt_outFile.txt";
	char* rrName = "rr_outFile.txt";
	
	fcfsJobs.size = 0;
	hpfJobs.size = 0;
	srtJobs.size = 0;
	rrJobs.size = 0;
	
	runScheduler();
	
	readInputFile(fp, fcfsName ,&fcfsJobs);
	fcfsMean = findMean(&fcfsJobs);
	fcfsVar = findVar(fcfsMean, &fcfsJobs);
	printf("FCFS MEAN: %f \t", fcfsMean);
	printf("FCFS VAR: %f \n", fcfsVar);
	
	readInputFile(fp, hpfName ,&hpfJobs);
	hpfMean = findMean(&hpfJobs);
	hpfVar = findVar(hpfMean, &hpfJobs);
	printf("HPF MEAN: %f \t", hpfMean);
	printf("HPF VAR: %f \n", hpfVar);
	
	readInputFile(fp, srtName ,&srtJobs);
	srtMean = findMean(&srtJobs);
	srtVar = findVar(srtMean, &srtJobs);
	printf("SRT MEAN: %f \t", srtMean);
	printf("SRT VAR: %f \n", srtVar);
	
	readInputFile(fp, rrName ,&rrJobs);
	rrMean = findMean(&rrJobs);
	rrVar = findVar(rrMean, &rrJobs);
	printf("RR MEAN: %f \t", rrMean);
	printf("RR VAR: %f \n", rrVar);
	
	return 0;
}
//------------------------------------------------------------------------------
// Run Scheduler Function: Uses the system() call to run the FCFS, HPF, SRT, and
// RR scheduling algorithms. 
void runScheduler()
{
   	system("./fcfs");
    system("./hpf");
    system("./srt");
    system("./rr"); 
}
//------------------------------------------------------------------------------
// Read Input Function: Reads input file and builds a list of records each with
// job name, arrival time, wait time, and clock pulse attributes. 
void readInputFile(FILE* fp, char* name, struct List* jobList)
{
    char jn[5]; 
    int at, wt, cp, index = 0;
    
    fp = fopen(name, "r");
    
    if(fp == NULL)
    {
        printf("FILE NOT FOUND\n");
        exit(1); // Error exit code
    }
	
	while (fscanf(fp, "%s %d %d %d", jn, &at, &wt, &cp) != EOF)
	{
		jobList->rJob[index].jobName = malloc(5);
		strcpy(jobList->rJob[index].jobName, jn);
		jobList->rJob[index].arrivalTime = at;
		jobList->rJob[index].waitTime = wt;
		jobList->rJob[index].clockPulse = cp;
		jobList->size++;
		index++;
	}

	fclose(fp);
}
//------------------------------------------------------------------------------
// Find Average Function: Calculates the avg (mean) of a scheduling algorithm 
// output file. 
double findMean(struct List* jobList)
{
    int index = 0;
    int totalSize = jobList->size - 1;
    double sum, mean = 0;
    double time[jobList->size];
    double numJobs = jobList->size; 
    
    for (index = 0; index < totalSize; index++)
    {
        time[index] = jobList->rJob[index].waitTime;
        sum = sum + time[index];
    }
    
    mean = sum / numJobs;
    return mean;
}
//------------------------------------------------------------------------------
// Find Variance Function: Calculates the variance of a scheduling algorithm 
// output file. 
double findVar(const int mean, struct List* jobList)
{
    int index = 0;
    int totalSize = jobList->size - 1;
    double sum, num, var = 0;
    double time[jobList->size];
    double numJobs = jobList->size; 
    
    for (index = 0; index < totalSize; index++)
    {
        time[index] = jobList->rJob[index].waitTime;
        num = (time[index] - mean);
        sum = (sum + (num * num));
        //printf("%f \n", time[index]);
    }
    
    var = sum / numJobs;
    
    return var;
}
//------------------------------------------------------------------------------
