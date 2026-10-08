#include <iostream>
#include <vector>
#include <memory>
#include <iomanip>
#include <string>

using namespace std;


// ======================================================
// ABSTRACT BASE CLASS
// ======================================================

class Employee
{
protected:
    int employeeId;
    string name;
    string department;
    string designation;
    double basicSalary;

public:

    // Constructor
    Employee(int id, string n, string dept,
             string desig, double salary)
    {
        employeeId = id;
        name = n;
        department = dept;
        designation = desig;
        basicSalary = salary;
    }

    // Pure virtual functions
    virtual double calculateAllowance() const = 0;

    virtual double calculateDeduction() const = 0;

    virtual string getEmployeeType() const = 0;


    // Calculate Gross Salary
    double calculateGrossSalary() const
    {
        return basicSalary + calculateAllowance();
    }


    // Calculate Net Salary
    double calculateNetSalary() const
    {
        return calculateGrossSalary() - calculateDeduction();
    }


    // Display Payslip
    virtual void displayPayslip() const
    {
        cout << "\n============================================\n";
        cout << "              EMPLOYEE PAYSLIP\n";
        cout << "============================================\n";

        cout << "Employee ID       : " << employeeId << endl;
        cout << "Employee Name     : " << name << endl;
        cout << "Employee Type     : "
             << getEmployeeType() << endl;
        cout << "Department        : " << department << endl;
        cout << "Designation       : " << designation << endl;

        cout << "--------------------------------------------\n";

        cout << fixed << setprecision(2);

        cout << "Basic Salary      : Rs. "
             << basicSalary << endl;

        cout << "Allowances        : Rs. "
             << calculateAllowance() << endl;

        cout << "Gross Salary      : Rs. "
             << calculateGrossSalary() << endl;

        cout << "Deductions        : Rs. "
             << calculateDeduction() << endl;

        cout << "--------------------------------------------\n";

        cout << "Net Salary        : Rs. "
             << calculateNetSalary() << endl;

        cout << "============================================\n";
    }


    // Get Employee ID
    int getEmployeeId() const
    {
        return employeeId;
    }


    // Get Basic Salary
    double getBasicSalary() const
    {
        return basicSalary;
    }


    // Virtual destructor
    virtual ~Employee()
    {
    }
};


// ======================================================
// PERMANENT EMPLOYEE CLASS
// ======================================================

class PermanentEmployee : public Employee
{
private:
    double bonus;

public:

    // Constructor
    PermanentEmployee(int id, string n, string dept,
                      string desig, double salary,
                      double b)
        : Employee(id, n, dept, desig, salary)
    {
        bonus = b;
    }


    // Calculate Allowance
    virtual double calculateAllowance() const
    {
        double hra = basicSalary * 0.20;
        double da = basicSalary * 0.10;

        return hra + da + bonus;
    }


    // Calculate Deduction
    virtual double calculateDeduction() const
    {
        return basicSalary * 0.12;
    }


    // Employee Type
    virtual string getEmployeeType() const
    {
        return "Permanent";
    }
};


// ======================================================
// CONTRACT EMPLOYEE CLASS
// ======================================================

class ContractEmployee : public Employee
{
private:
    double transportAllowance;

public:

    // Constructor
    ContractEmployee(int id, string n, string dept,
                     string desig, double salary,
                     double transport)
        : Employee(id, n, dept, desig, salary)
    {
        transportAllowance = transport;
    }


    // Calculate Allowance
    virtual double calculateAllowance() const
    {
        return transportAllowance;
    }


    // Calculate Deduction
    virtual double calculateDeduction() const
    {
        return basicSalary * 0.05;
    }


    // Employee Type
    virtual string getEmployeeType() const
    {
        return "Contract";
    }
};


// ======================================================
// ADD EMPLOYEE
// ======================================================

void addEmployee(vector< unique_ptr<Employee> >& employees)
{
    int id;
    string name;
    string department;
    string designation;
    double basicSalary;
    int choice;

    cout << "\n============================================\n";
    cout << "              ADD EMPLOYEE\n";
    cout << "============================================\n";

    cout << "Enter Employee ID: ";
    cin >> id;

    cin.ignore();

    cout << "Enter Employee Name: ";
    getline(cin, name);

    cout << "Enter Department: ";
    getline(cin, department);

    cout << "Enter Designation: ";
    getline(cin, designation);

    cout << "Enter Basic Salary: ";
    cin >> basicSalary;

    cout << "\nSelect Employee Type:\n";
    cout << "1. Permanent\n";
    cout << "2. Contract\n";
    cout << "Enter choice: ";
    cin >> choice;


    // Permanent Employee
    if (choice == 1)
    {
        double bonus;

        cout << "Enter Bonus: ";
        cin >> bonus;

        unique_ptr<Employee> employee(
            new PermanentEmployee(
                id,
                name,
                department,
                designation,
                basicSalary,
                bonus
            )
        );

        employees.push_back(move(employee));

        cout << "\nPermanent employee added successfully!\n";
    }


    // Contract Employee
    else if (choice == 2)
    {
        double transport;

        cout << "Enter Transport Allowance: ";
        cin >> transport;

        unique_ptr<Employee> employee(
            new ContractEmployee(
                id,
                name,
                department,
                designation,
                basicSalary,
                transport
            )
        );

        employees.push_back(move(employee));

        cout << "\nContract employee added successfully!\n";
    }


    // Invalid Employee Type
    else
    {
        cout << "\nInvalid employee type!\n";
    }
}


// ======================================================
// DISPLAY ALL EMPLOYEES
// ======================================================

void displayAllEmployees(
    const vector< unique_ptr<Employee> >& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    cout << "\n============================================\n";
    cout << "           ALL EMPLOYEE RECORDS\n";
    cout << "============================================\n";

    for (size_t i = 0; i < employees.size(); i++)
    {
        employees[i]->displayPayslip();
    }
}


// ======================================================
// SEARCH EMPLOYEE
// ======================================================

void searchEmployee(
    const vector< unique_ptr<Employee> >& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    int id;

    cout << "\nEnter Employee ID to search: ";
    cin >> id;

    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i]->getEmployeeId() == id)
        {
            employees[i]->displayPayslip();
            return;
        }
    }

    cout << "\nEmployee not found.\n";
}


// ======================================================
// GENERATE PAYSLIP
// ======================================================

void generatePayslip(
    const vector< unique_ptr<Employee> >& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    int id;

    cout << "\nEnter Employee ID: ";
    cin >> id;

    for (size_t i = 0; i < employees.size(); i++)
    {
        if (employees[i]->getEmployeeId() == id)
        {
            employees[i]->displayPayslip();
            return;
        }
    }

    cout << "\nEmployee not found.\n";
}


// ======================================================
// PAYROLL REPORT
// ======================================================

void payrollReport(
    const vector< unique_ptr<Employee> >& employees)
{
    if (employees.empty())
    {
        cout << "\nNo employee records available.\n";
        return;
    }

    double totalBasic = 0;
    double totalGross = 0;
    double totalDeduction = 0;
    double totalNet = 0;


    for (size_t i = 0; i < employees.size(); i++)
    {
        totalBasic =
            totalBasic + employees[i]->getBasicSalary();

        totalGross =
            totalGross + employees[i]->calculateGrossSalary();

        totalDeduction =
            totalDeduction + employees[i]->calculateDeduction();

        totalNet =
            totalNet + employees[i]->calculateNetSalary();
    }


    cout << "\n============================================\n";
    cout << "              PAYROLL REPORT\n";
    cout << "============================================\n";

    cout << fixed << setprecision(2);

    cout << "Number of Employees : "
         << employees.size() << endl;

    cout << "Total Basic Salary  : Rs. "
         << totalBasic << endl;

    cout << "Total Gross Salary  : Rs. "
         << totalGross << endl;

    cout << "Total Deductions    : Rs. "
         << totalDeduction << endl;

    cout << "Total Net Salary    : Rs. "
         << totalNet << endl;

    cout << "============================================\n";
}


// ======================================================
// MAIN FUNCTION
// ======================================================

int main()
{
    // Vector stores all employee objects
    vector< unique_ptr<Employee> > employees;

    int choice;


    // Menu repeats until user selects Exit
    do
    {
        cout << "\n\n============================================\n";
        cout << "       EMPLOYEE PAYROLL MANAGEMENT SYSTEM\n";
        cout << "============================================\n";

        cout << "1. Add Employee\n";
        cout << "2. Display All Employees\n";
        cout << "3. Search Employee\n";
        cout << "4. Generate Payslip\n";
        cout << "5. Payroll Report\n";
        cout << "6. Exit\n";

        cout << "============================================\n";

        cout << "Enter your choice: ";
        cin >> choice;


        switch (choice)
        {
            case 1:
                addEmployee(employees);
                break;


            case 2:
                displayAllEmployees(employees);
                break;


            case 3:
                searchEmployee(employees);
                break;


            case 4:
                generatePayslip(employees);
                break;


            case 5:
                payrollReport(employees);
                break;


            case 6:
                cout << "\nThank you for using the system!\n";
                break;


            default:
                cout << "\nInvalid menu choice!\n";
        }

    } while (choice != 6);


    return 0;
}