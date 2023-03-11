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
            numberOfDepartments++;
        
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

    unsigned int get_number_of_departments() 
    {
        return numberOfDepartments;
    }
        
    void add_new_department(char newDepartment[100])
    {
        char** newArr = new char*[numberOfDepartments + 1];
        memcpy(newArr, departments, numberOfDepartments * sizeof(char*));
        newArr[numberOfDepartments] = new char[strlen(newDepartment)];
        strcpy(newArr[numberOfDepartments], newDepartment);

        departments = newArr;
        
        numberOfDepartments++;
    }

    void get_departments() 
    {
        for(int index=0; index < numberOfDepartments; index++)
            g<<departments[index]<<endl;
    }
    
    ~Departments()
    {
       for (int index = 0 ;index < numberOfDepartments ; index++)
            delete departments[index];
        delete[] departments;
    }

};

int main()
{
    Departments d("departments.txt"), e;
    d.add_new_department("Diabetology");
    d.get_departments();
    g<<d.get_number_of_departments();


    return 0;
}