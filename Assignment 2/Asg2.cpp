//BALQIS BINTI MOHD SARMIZI A24CS0053
// NUR ELISA AFIRA BINTI MOHAMAD NAZIR A24CS0160
// 11 JANUARY 2025


#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

const int maxSize = 50;

//function prototype
int readInput(string name[],string dept[],double salary[],int hour[]);
double determineRate(string dept);
void calcSalaries(string name[],string dept[],double salary[],
int hour[],double ovt[],double totalSalary[],int total_employee);
void displayOutput(string name[],string dept[],double salary[],int hour[],
double ovt[],double totalSalary[],int total_employee);
void displayAnalysis(string name[],string dept[],double ovt[],double totalSalary[],int total_employee);


int main()
{
 
    string name[maxSize]; //Name of the employee
    string dept[maxSize]; //department name of the employee
    double salary[maxSize]; //basic monthly salary of the employee
    int hour[maxSize]; //Number of overtime hours worked by the employee
    double ovt[maxSize]; // monthly overtime pay
    double totalSalary[maxSize]; //Total salary of the employee

    //function call
    int total_employee = readInput(name,dept,salary,hour); //read input from file and store in array
    calcSalaries (name,dept,salary,hour,ovt,totalSalary,total_employee); //calculate total salary of each employee
    displayOutput(name,dept,salary,hour,ovt,totalSalary,total_employee); //display output
    displayAnalysis(name,dept,ovt,totalSalary,total_employee); //display analysis 

    system("pause");
    return 0;
   

}

//task 2 : function to read input from file and store in array
int readInput(string name[],string dept[],double salary[],int hour[])
{   
    ifstream input("employee.txt"); //open the file 
    //to check if the file can open
    if (!input.is_open())
        {
            cout << "Error! File is not exist" << endl;
            system("pause");
            exit (0);
        }
    
    int count=0;  //initialize and count the number of employee
    while(count<maxSize&&getline(input,name[count],','))
    {   
        getline(input, dept[count],','); //read department name
        input>>salary[count]; //read salary
        input.ignore();  // Ignore the space before overtime hours
        input >> hour[count]; //read overtime hours
        input.ignore(); // Ignore the space 
        count++; // increment count by 1
    }
    
    input.close(); //close the file
    return count;
}

//task 3 : function to return rate based on department
double determineRate(string dept)
{
    if(dept=="Human Resource")
    return 15.00;
    else if(dept=="Information Technology")
    return 20.00;
    else if (dept=="Finance")
    return 18.00;
    else
    return 0.00; // default rate if department is not found
    
}

//task 4 : function to calculate total salary and overtime pay for each employee
void calcSalaries(string name[],string dept[],double salary[],
int hour[],double ovt[],double totalSalary[],int total_employee)
{
    for(int i=0;i<total_employee;i++)
    {
        double rate = determineRate(dept[i]);
        ovt[i]=rate*hour[i];
        totalSalary[i]=salary[i]+ovt[i];
    }
}

//task 5 : display the all of the employee information
void displayOutput(string name[],string dept[],double salary[],int hour[],
double ovt[],double totalSalary[],int total_employee)
{
    cout << fixed << setprecision(2);
    cout << "Name"; 
    cout << setw(32)<< "Department" ;
    cout << setw(33) << "Basic Salary"; 
    cout << setw(17) <<"Overtime Hour";  
    cout << setw(17) <<"Overtime Pay";  
    cout << setw(17) <<"Total Salary" << endl;
    cout << string(120, '-') << endl;

    cout << left;
    cout << setw(26) <<name[0];
    cout << left;
    cout << setw(25) << dept[0];
    cout << right;
    cout << setw(16) << salary[0];
    cout << setw(14) << hour[0];
    cout << setw(19) << ovt[0];
    cout << setw(18) << totalSalary[0];
    cout << endl;

    for(int i=1;i<total_employee;i++)
    {
        cout << left;
        cout << setw(26) <<name[i];
        cout << left;
        cout << setw(25) << dept[i];
        cout << right;
        cout << setw(16) << salary[i];
        cout << setw(14) << hour[i];
        cout << setw(19) << ovt[i];
        cout << setw(18) << totalSalary[i];
        cout << endl;
        
    }
    cout << endl << endl;
}

//task 6 : display analysis for each department and determine the highest and lowest salary in each department
void displayAnalysis(string name[],string dept[],double ovt[],double totalSalary[],int total_employee)
{
    //declare and initialize variables
    double average[3]={0.0,0.0,0.0};
    double totalSalaries[3]={0.0,0.0,0.0};
    double overtimePay[3] = {0.0,0.0,0.0};
    int count[3]={0,0,0},i;
    
    double highestSalary = -99999; //initialize highest salary to a very low value
    double lowestSalary = 99999; //initialize lowest salary to a very high value
    string highestName = name[0], lowestName = name[0];
    string highestDept = dept[0], lowestDept = dept[0];


    for( i=0;i<total_employee;i++)
    {
        //determine the overtime pay , total salary and number of employees in each department
        if(dept[i]=="Human Resource")
        {
            overtimePay [0]+=ovt[i];
            totalSalaries[0]+=totalSalary[i];
            count[0]++;
        }
        else if(dept[i]=="Information Technology")
        {
            overtimePay[1]+=ovt[i];
            totalSalaries[1]+=totalSalary[i];
            count[1]++;
        }
        else if(dept[i]=="Finance")
        {
            overtimePay[2]+=ovt[i];
            totalSalaries[2]+=totalSalary[i];
            count[2]++;
        }

        // Update highest and lowest salary
        if(totalSalary[i]>highestSalary)
        {highestSalary=totalSalary[i];
        highestName =name[i];
        highestDept = dept[i];}

        if(totalSalary[i]<lowestSalary)
        {lowestSalary=totalSalary[i];
        lowestName =name[i];
        lowestDept = dept[i];}
    }
    
    //calculate the average salary for each department
    for(i=0;i<3;i++)
        average[i]=totalSalaries[i]/count[i];

    //print the results
    cout << endl;
    cout << fixed << setprecision(2);
    cout << "Department"; 
    cout << setw(35) << "Total Overtime Pay";
    cout << setw(20 ) << "Total Salary";
    cout << setw(20 ) << "Average Salary"<<endl;
    cout << string(86, '-') << endl;

    cout << "Human Resource"; 
    cout << setw(25) << right << overtimePay[0] << setw(24) <<totalSalaries[0] << setw(18) << average[0] << endl;
    cout << "Information Technology";
    cout  << setw(17) << right << overtimePay[1] << setw(24) << totalSalaries[1] << setw(18)<< average[1] << endl;
    cout << "Finance"; 
    cout << setw(32)<< right << overtimePay[2] << setw(24) <<totalSalaries [2] << setw(18) << average[2] << endl << endl;

    cout << "Highest Salary: " << highestName << " (MYR" << highestSalary << ") from Department of " 
     << highestDept << endl;
    cout << "Lowest Salary: " << lowestName << " (MYR" << lowestSalary << ") from Department of " 
     << lowestDept << endl;

}