#include <iostream>
#include <fstream>
#include <cstring>
#include <new>

using namespace std;

ofstream g("out.txt");


class Departments {

    char** departments;
    unsigned int numberOfDepartments;

    public:

    Departments()
    {
        departments = nullptr;
        numberOfDepartments = 0;
    }

    Departments (const char* fileName)
    {   
        ifstream inputFile(fileName);
    
        numberOfDepartments = 0;
        char currentDepartment[100];
        while (inputFile.getline(currentDepartment,100))
        {
            numberOfDepartments++;
        }

        departments = new char*[numberOfDepartments];

        unsigned int index = 0;
        
        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        for (int index = 0; index < numberOfDepartments; index++) 
        {
            inputFile.getline(currentDepartment,100);
            departments[index] = new char[strlen(currentDepartment)];
            strcpy(departments[index], currentDepartment);
        }

        inputFile.close();
    }

    ~Departments()
    {
        delete[] departments;
    }

};

int main()
{
    Departments d("departments.txt"), e;
    return 0;
}