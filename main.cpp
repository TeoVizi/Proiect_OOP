#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <new>

using namespace std;

ofstream g("out.txt", ios::out);

class UtilityReadFromFile {

    char** Array;
    unsigned int length;

    public:
    UtilityReadFromFile(const char* fileName)
    {
        ifstream inputFile(fileName);

        length = 0;
        char currentElemnent[100];

        while (inputFile.getline(currentElemnent,100))
            length++;

        Array = new char*[length];

        unsigned int index = 0;

        inputFile.clear();
        inputFile.seekg(0, ios::beg);

        for (int index = 0; index < length; index++) 
        {
            inputFile.getline(currentElemnent,100);
            Array[index] = new char[strlen(currentElemnent)];
            strcpy(Array[index], currentElemnent);
        }

        inputFile.close();

    }

    char** get_array() {
        return Array;
    }

    unsigned int get_length() {
        return length;
    }

    ~UtilityReadFromFile()
    {
       for (int index = 0 ;index < length ; index++)
            delete[] Array[index];
        delete[] Array;
    }

};






class Departments {

    char** departments;
    unsigned int numberOfDepartments;

    public:
    Departments()
    {
        departments = nullptr;
        numberOfDepartments = 0;
    }



    Departments (UtilityReadFromFile read)
    {   
        
        numberOfDepartments = read.get_length();
        departments = new char*[numberOfDepartments];

        unsigned int index = 0;
        for(index = 0; index < numberOfDepartments; index++)
        {
             this->departments[index] = new char[strlen(read.get_array()[index])];
            strcpy(this->departments[index], read.get_array()[index]);
        }

    }



    unsigned int get_number_of_departments() 
    {
        return numberOfDepartments;
    }
        
    void set_new_department(char newDepartment[100])
    {
        char** newArr = new char*[numberOfDepartments + 1];
        memcpy(newArr, departments, numberOfDepartments * sizeof(char*));
        newArr[numberOfDepartments] = new char[strlen(newDepartment)];
        strcpy(newArr[numberOfDepartments], newDepartment);

        departments = newArr;
        
        numberOfDepartments++;
    }



    void delete_department(char* elementToDelete)
    {
        int indexToDelete = -1;
        for (int index=0; index < numberOfDepartments; index++)
            if(strcmp(departments[index], elementToDelete) == 0 )
            {
                indexToDelete = index;
                break;
            }
        
        if(indexToDelete == -1)
            {
                g<< "Element not found in departments."<<endl;
            }
            else {
            delete[] departments[indexToDelete];
            for (int index = indexToDelete; index<numberOfDepartments; index++)
                departments[index] = departments[index+1];

            char** newArr = new char*[numberOfDepartments-1];
            for (int index=0; index < numberOfDepartments-1; index++)
            {
                int length = strlen(departments[index]);
                newArr[index] = new char[length+1];
                strcpy(newArr[index], departments[index]);
            }
            
            departments = newArr;
            numberOfDepartments--;
            
        }
    }



    friend ostream & operator<< (ostream &os, const Departments &Array)
    {
        ofstream output("out.txt", ios::out);
        if (output.is_open()) 
        {   
            output.clear();
            output.seekp(0, ios::end);

            for(int index = 0; index < Array.numberOfDepartments; index++)
                os << Array.departments[index] << endl;
        }
        
        os << endl;

         output.close();

         output.clear();
         output.seekp(0, ios::end);

        return os;
    }


    ~Departments()
    {
       for (int index = 0 ;index < numberOfDepartments ; index++)
            delete[] departments[index];
       delete[] departments;
    }

};

int main()
{
    Departments d(UtilityReadFromFile ("departments.txt"));

    g<< d.get_number_of_departments();
    g<< d;
    g << d.get_number_of_departments();
    return 0;
}