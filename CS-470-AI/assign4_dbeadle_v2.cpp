//------------------------------------------------------------------------------
// Donald Lee Beadle
// CS 470
// Traveling Salesman Problem (TSP)
// NOTE: Does not meet program criteria for assignment. Still does not isolate 
// the best path to the cities. Costs to cities and times elapsed seem to be 
// correct though. 
//------------------------------------------------------------------------------
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <ctime>
#include <iomanip>
using namespace std;
//------------------------------------------------------------------------------
// Structs: 
//------------------------------------------------------------------------------
struct City
{
    int name;
    double xCoord;
    double yCoord;
};
//------------------------------------------------------------------------------
// Function Declarations:
//------------------------------------------------------------------------------
void readInput(City cities[], int &size);
void printList(City list[], int size);
void swap(int &x,int &y);
void permute(City list[], City route[], int k, int size);
double euclidean(double x1, double y1, double x2, double y2);
double calculateDistance(City a, City b);
double calculateCost(City cities[], int size);
//------------------------------------------------------------------------------
// Main driver:
int main()
{
    // Clock variables for timing
    clock_t startTimer;
    double timeRan = 0;
    
    // Maximum number of cities
    const int MAX = 48; 
    City list[MAX];
    City route[MAX];
    int size = 0;

    readInput(list, size);
    
    startTimer = clock();
    permute(list, route, 0, size);
    timeRan = (clock() - startTimer) / (double) CLOCKS_PER_SEC;

    cout << fixed << setprecision(3) << endl << "Time Elapsed: "<< timeRan << endl;
    
    return 0;
}
//------------------------------------------------------------------------------
// Function Definitions:
//------------------------------------------------------------------------------
// Read Input Function: 
// Reads the text file and builds an array of City structs. 
void readInput(City cities[], int &size)
{
    ifstream inFile;
    
    inFile.open("assign4-in.txt");
    
    if(inFile.fail())
    {
        cout << "Error on file open" << endl;
    }
    
    else
    {
        inFile >> size;
        
        for(int i = 0; i < size; i++)
        {
            inFile >> cities[i].name;
            inFile >> cities[i].xCoord;
            inFile >> cities[i].yCoord;
        }
    }
    
    inFile.close();
}
//------------------------------------------------------------------------------
// Print List Function: 
// Prints the list. 
void printList(City list[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << list[i].name << " - ";
    }
    
    cout << list[0].name << "\t";
}
//------------------------------------------------------------------------------
// Swap Function: 
// Swap two integers. 
void swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}
//------------------------------------------------------------------------------
// Permute Function: 
// Performs the permutation to find the best path between cities based on cost. 
void permute(City list[], City route[], int k, int size)
{
    double currentCost[48];
    double lowestCost = 0;
    //int bestPath[48];
    
    if(k == size)
    {
        for(int i = 0; i < size; i++)
        {
            currentCost[i] = calculateCost(list, size);    
        }
        
        lowestCost = currentCost[0];
        
        for(int i = 0; i < size; i++)
        {
            if(currentCost[i] < lowestCost)
            {
                lowestCost = currentCost[i];
            }
        }
        
        printList(list, size);
        cout << fixed << setprecision(1) << "Total Cost: " << lowestCost << endl;
    }
    
    else
    {
        for(int i = k; i < size; i++)
        {
            swap(list[k], list[i]);
            permute(list, route, k+1, size);
            swap(list[k], list[i]);
        }
    }
}
//------------------------------------------------------------------------------
// Euclidean Function: 
// Calculates the distance between two points. 
double euclidean(double x1, double y1, double x2, double y2)
{
    double x, y, d = 0;
    
    x = pow((x2 - x1), 2);
    y = pow((y2 - y1), 2);
    
    d = sqrt(x + y);
    
    return d;
}
//------------------------------------------------------------------------------
// Calculate Distance Function:
// Calculates the total distance of the path. 
double calculateDistance(City a, City b)
{
    double d = 0;
    
    d = euclidean(a.xCoord, a.yCoord, b.xCoord, b.yCoord);
    
    return d;
}
//------------------------------------------------------------------------------
// Calculate Cost Function:
// Calculates the cost on the total path. 
double calculateCost(City cities[], int size)
{
    double cost = 0;
    double roundTrip =  0;
    double totalCost = 0;
  
    for (int i = 0; i < size-1; i++)
    {
        cost += calculateDistance(cities[i], cities[i+1]);
    }
    
    roundTrip = calculateDistance(cities[0], cities[size-1]);
    
    totalCost = cost + roundTrip;
    
    return totalCost;
}
//------------------------------------------------------------------------------