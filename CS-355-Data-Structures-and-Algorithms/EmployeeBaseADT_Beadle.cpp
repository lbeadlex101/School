//-----------------------------------------------------------------------------
// Main.cpp
// Employee Class Hierarchy
// 
// Copyright (c) 2016 Donald Lee Beadle 
//
//-----------------------------------------------------------------------------
#include <iostream>
using namespace std;
//-----------------------------------------------------------------------------
// The base class.
class Employee 
{ 
  protected:
    double rate;
  
  public:
		  Employee(double r) 
    {
      rate = r;
    }
		
		  ~Employee() //Base class destructor
      {
      }

    virtual double pay() = 0; // Virtual function
};
//-----------------------------------------------------------------------------
// A derived class of Class Employee
class TempEmployee : public Employee 
{ // temp
  public:
		  TempEmployee(double r) : Employee(r)
    {
			 }
    
    ~TempEmployee() // Temp derived class destructor
    {
			 }

    double pay()
    {
      double total = 0;
      total = (rate * 40); 
      return total;
    }
};
//-----------------------------------------------------------------------------
// A derived class of Class Employee
class FullTimeEmployee : public Employee 
{ 
  public:
    FullTimeEmployee(double r) : Employee(r)
    {
    }
		
    ~FullTimeEmployee() // FullTime derived class destructor
    { 
    }

    double pay()
    {
      double total = 0;
      total = (rate / 12); 
      return total;
    }
};
//-----------------------------------------------------------------------------
// Payroll function: Calls a type of Class Employee to calculate pay based on
// class derived type.
double runPayroll(Employee& emp)
{
  cout << ": $" << emp.pay();
}
//-----------------------------------------------------------------------------
// Main Driver for testing
int main() 
{
 
  TempEmployee jim(9.75);
  FullTimeEmployee edwin(80000);

  cout << "Jim";
  runPayroll(jim);
  cout << endl;

  cout << "Edwin";
  runPayroll(edwin);
  cout << endl;

  return 0;

}
//-----------------------------------------------------------------------------
