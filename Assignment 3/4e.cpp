/*NUR ELISA AFIRA BINTI MOHAMAD NAZIR   A24CS0160
  BALQIS BINTI MOHAMAD SARMIZI          A24CS0053
  22 JANUARY 2025*/
#include <iostream> 
#include <fstream>
#include <iomanip>
#include <string>
#define Q 4 // Define the number of quarters
using namespace std;

//Task 1 : Define the struct to store information
struct Hub
{
    string hubCode;
    string hubName;
    string hubLocation;
    double quarterlyRevenue[Q]; //q1, q2, q3, q4
    double annualRevenue;
    double percentage;
};

// Function prototypes
void validateFile(Hub *hubs, int &count);
void hubDetails(Hub *hubs, int count);
void revenueAnalysis(Hub *hubs, int count , double totalQuarter[], double averageQuarter[], double &averageAnnual, 
double &averagePercentage, int &highestRevenue, int &lowestRevenue, int &highestQuarterRevenue, int &lowestQuarterRevenue);
void revenueReport(Hub *hubs, int, double totalQuarter[], double averageQuarter[], double averageAnnual, 
double averagePercentage, int highestRevenue, int lowestRevenue, int highestQuarterRevenue, int lowestQuarterRevenue);

int main()
{
    Hub hubs [9999]; // Adjust size as needed
    // Initialize the variables
    int count=0;
    double averageAnnual = 0;
    double averagePercentage = 0;
    double totalQuarter[Q] = {0,0,0,0};
    double averageQuarter[Q]= {0,0,0,0};
    int  highestRevenue = 0, lowestRevenue = 0, highestQuarterRevenue = 0, lowestQuarterRevenue = 0;
   
    // Call the function
    validateFile(hubs, count);
    hubDetails(hubs, count);
    revenueAnalysis(hubs, count , totalQuarter, averageQuarter, averageAnnual,
    averagePercentage, highestRevenue, lowestRevenue, highestQuarterRevenue , lowestQuarterRevenue);
    revenueReport(hubs, count ,totalQuarter, averageQuarter, averageAnnual,
    averagePercentage, highestRevenue, lowestRevenue, highestQuarterRevenue, lowestQuarterRevenue);

    system("pause");
    return 0;
}

// Task 2 : Function to read the file
void validateFile(Hub *hubs, int &count)
{
    // Open all the file 
    ifstream file("hubs.txt");
    ifstream q1File("q1.txt");
    ifstream q2File("q2.txt");
    ifstream q3File("q3.txt");
    ifstream q4File("q4.txt");

    // Check if the file is opened successfully
    if(!file || !q1File || !q2File || !q3File || !q4File)
    {
        cout << "Error! One or more files are not found" << endl;
        system("pause");
        exit(0);
    }

    // Read all the files
    while(getline(file, hubs[count].hubCode))
    {
        q1File >> hubs[count].quarterlyRevenue[0];
        q2File >> hubs[count].quarterlyRevenue[1];
        q3File >> hubs[count].quarterlyRevenue[2];
        q4File >> hubs[count].quarterlyRevenue[3];
        count++; // determine the number of hubs based on the lines in the file
    }
    
    // check if the number of lines in each file is the same
    if (!file.eof() || !q1File.eof() || !q2File.eof() || !q3File.eof() || !q4File.eof())
    {
        cout << "Error! The number of lines in each file is not the same." << endl;
        system("pause");
        exit(0);
    }

    // Close all the file
    file.close();
    q1File.close();
    q2File.close();
    q3File.close();
    q4File.close();
}

// Task 3 : Determine hub name and location based on prefix
void hubDetails(Hub *hubs,int count)
{
    for (int i = 0; i < count; i++)
    {
        if (hubs[i].hubCode.substr(0, 3) == "KLS") // Check the first 3 characters of the hub code
        {
            hubs[i].hubName = "KL Sentral";
            hubs[i].hubLocation = "Kuala Lumpur";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "PNS")
        {
            hubs[i].hubName = "Penang Sentral";
            hubs[i].hubLocation = "Penang";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "JBS")
        {
            hubs[i].hubName = "JB Sentral";
            hubs[i].hubLocation = "Johor Bahru";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "IPS")
        {
            hubs[i].hubName = "Ipoh Sentral";
            hubs[i].hubLocation = "Ipoh";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "MKS")
        {
            hubs[i].hubName = "Melaka Sentral";
            hubs[i].hubLocation = "Melaka";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "KKS")
        {
            hubs[i].hubName = "KK Sentral";
            hubs[i].hubLocation = "Kota Kinabalu";
        }
        else if (hubs[i].hubCode.substr(0, 3) == "KTS")
        {
            hubs[i].hubName = "Kuantan Sentral";
            hubs[i].hubLocation = "Kuantan";
        }
    }
}

// Task 4 : Function to calculate annual revenue, percentage, average and determine quarter with highest and lowest revenue
void revenueAnalysis(Hub *hubs, int count , double totalQuarter[], double averageQuarter[], double &averageAnnual,
 double &averagePercentage, int &highestRevenue, int &lowestRevenue, int &highestQuarterRevenue, int &lowestQuarterRevenue)
{
    double totalAnnualRevenue = 0;
    double totalPercentage = 0;

    for (int i = 0; i < count; i++)
    {
        hubs[i].annualRevenue = 0;
        for (int j = 0; j < Q; j++)
        {
            // Calculate total revenue for each quarter across all hubs
            totalQuarter[j] += hubs[i].quarterlyRevenue[j];
        }
        // Calculate total revenue for each hub across all quarters
        hubs[i].annualRevenue = hubs[i].quarterlyRevenue[0] + hubs[i].quarterlyRevenue[1] + hubs[i].quarterlyRevenue[2] + hubs[i].quarterlyRevenue[3];
        // Calculate total annual revenue
        totalAnnualRevenue += hubs[i].annualRevenue;
    }

     // Calculate percentage of revenue for each hub
    for (int i = 0; i < count; i++)
    {
        hubs[i].percentage = (hubs[i].annualRevenue / totalAnnualRevenue) * 100;
        totalPercentage = totalPercentage + hubs[i].percentage;
    }

    // determine hub with highest annual revenue and quarter with highest revenue
    for (int i = 0; i < count; i++)
    {
        if (hubs[i].annualRevenue > highestRevenue)
            highestRevenue = i;
            for (int j = 0; j < Q; j++)
                if (hubs[i].quarterlyRevenue[j] > hubs[highestQuarterRevenue].quarterlyRevenue[j])
                    highestQuarterRevenue = j;
    }

    // determine hub with lowest annual revenue and quarter with lowest revenue
    for (int i = 0; i < count; i++)
    {
        if (hubs[i].annualRevenue < lowestRevenue)
            lowestRevenue = i;
            for (int j = 0; j < Q; j++)
                if (hubs[i].quarterlyRevenue[j] < hubs[lowestQuarterRevenue].quarterlyRevenue[j])
                    lowestQuarterRevenue = j;
    }

    // Calculate average revenue for each quarter across all hubs, annual revenue and percentage
    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < Q; j++)
            averageQuarter[j] = totalQuarter[j] / count;
    }

    averageAnnual = totalAnnualRevenue / count;
    averagePercentage = totalPercentage / count;
}

// Task 5 : Function to display the report
void revenueReport(Hub *hubs, int count, double totalQuarter[], double averageQuarter[], double averageAnnual, 
double averagePercentage, int highestRevenue, int lowestRevenue, int highestQuarterRevenue, int lowestQuarterRevenue)
{
    // Display the header
    cout << "HUB CODE"; 
    cout << setw(12) <<"HUB NAME" ;
    cout << setw(20) <<"LOCATION"; 
    cout << setw(14) <<"Q1";  
    cout << setw(11) <<"Q2";  
    cout << setw(11) <<"Q3";
    cout << setw(11) <<"Q4";
    cout << setw(15) <<"ANNUAL REV";
    cout << setw(16) <<"CONTRIBUTION" << endl;
    cout << string(118, '-') << endl;

    // display the details of each hub
    for(int i=0;i<count;i++)
    {
        cout << fixed << setprecision(0);
        cout << left;
        cout << setw(12) << hubs[i].hubCode;
        cout << left;
        cout << setw(20) << hubs[i].hubName;
        cout << left;
        cout << setw(18) << hubs[i].hubLocation;
        cout << right;
        cout << setw(6) << hubs[i].quarterlyRevenue[0];
        cout << setw(11) << hubs[i].quarterlyRevenue[1];
        cout << setw(11) << hubs[i].quarterlyRevenue[2];
        cout << setw(11) << hubs[i].quarterlyRevenue[3];
        cout << setw(11) << hubs[i].annualRevenue;
        cout << setw(14) << fixed << setprecision(2) << hubs[i].percentage << "%" << endl;
        cout << endl;
    }
    
    // Display the average revenue for each quarter, annual revenue and percentage
    cout << string(118, '-') << endl;
    cout << setw(30) << "AVERAGE";
    cout << setw(26) << averageQuarter[0];
    cout << setw(11) << averageQuarter[1];
    cout << setw(11) << averageQuarter[2];
    cout << setw(11) <<averageQuarter[3];
    cout << setw(11) << averageAnnual;
    cout << setw(14) << averagePercentage << "%" << endl;
    cout << string(118, '-') << endl<<endl;

    // Display the overall report
    cout << "OVERALL REPORT" << endl;
    cout << string(14, '=') << endl;
    cout << fixed << setprecision(0);
    cout << right;
    cout << "GRAND TOTAL REVENUE" << setw(7) << "= " << totalQuarter[0] + totalQuarter[1] + totalQuarter[2] + totalQuarter[3] << endl;
    cout << "HIGHEST ANNUAL REVENUE" << setw(4) <<  "= "  << hubs[highestRevenue].annualRevenue << " (" << hubs[highestRevenue].hubName << ", " << hubs[highestRevenue].hubLocation << ") " << endl;
    cout << "LOWEST ANNUAL REVENUE" << setw(5) <<  "= " << hubs[lowestRevenue].annualRevenue << " (" << hubs[lowestRevenue].hubName  << ", " << hubs[lowestRevenue].hubLocation << ") "  << endl;
    cout << "QUARTER WITH HIGHEST TOTAL REVENUE: QUARTER " << highestQuarterRevenue+1 << " (" << totalQuarter[highestQuarterRevenue] << ")" << endl;
    cout << "QUARTER WITH LOWEST TOTAL REVENUE : QUARTER " << lowestQuarterRevenue+1 << " (" << totalQuarter[lowestQuarterRevenue] << ")" << endl;
}
