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
        
    void set_new_department(const char* newDepartment)
    {
        char** newArr = new char*[numberOfDepartments + 1];
        memcpy(newArr, departments, numberOfDepartments * sizeof(char*));
        newArr[numberOfDepartments] = new char[strlen(newDepartment)+1];
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
            for(int index = 0; index < Array.numberOfDepartments; index++)
                os << Array.departments[index] << endl;

        return os;
    }
   

    ~Departments()
    {
       for (int index = 0 ;index < numberOfDepartments ; index++)
            delete[] departments[index];
       delete[] departments;
    }

};



class Birthday 
{

    unsigned int day, month, year;

    public:
    Birthday(unsigned int day, unsigned int month, unsigned int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }
};



class Address
{
    char street[30];
    unsigned int number;

    public:
    Address(char street[30], unsigned int number)
    {
        strcpy(this->street, street);
        this->number = number;
    }
};



class Vets {

    char** vets;
    unsigned int numberOfVets;
    char departmentForVet[50][100];
    char birthdayForVet[50][20];
    char addressForVet[50][100];

    public:
    Vets()
    {
        vets = nullptr;
        numberOfVets = 0;
    }

    Vets(UtilityReadFromFile read)
    {
       numberOfVets = read.get_length();
        vets = new char*[numberOfVets];

        unsigned int index = 0;
        for(index = 0; index < numberOfVets; index++)
        {
             this->vets[index] = new char[strlen(read.get_array()[index])];
            strcpy(this->vets[index], read.get_array()[index]);
        }
    }

      friend ostream & operator<< (ostream &os, const Vets &Array)
    {
            for(int index = 0; index < Array.numberOfVets; index++)
                os << Array.vets[index] << endl;

        return os;
    }

    unsigned int get_number_of_vets()
    {
        return numberOfVets;
    }

    // void set_department_for_vet(const char vetFullName, char departmentName)
    // {
    //     int saveIndex = -1;

    //     for (int index = 0 ; index < numberOfVets; index++)
    //         if(strcmp(vetFullName, vets[index]) == 0)
    //         {
    //             saveIndex = index;
    //         }
    //         else {
    //             strcpy(departmentForVet[index], "/");
    //         }

    // }

    ~Vets()
    {
        for (int index = 0; index < numberOfVets; index++)
            delete[] vets[index];
        delete[] vets;
    }

};



int main()
{
    Departments d(UtilityReadFromFile ("departments.txt"));

    g<<"FUNCTIONALITY FOR CLASS DEPARTMENTS:"<<endl;
    g<<"Departments read from file:"<<endl;
    g<<d;
    g<<endl;
    g<<"Get number of departments: ";
    g << d.get_number_of_departments()<<endl;
    d.set_new_department("Neurology"); // adding a new department
    g<<endl;
    g<<"Departments after adding a new one:"<<endl;
    g<<d;
    g<<endl;
    g<<"Get departments after addition: ";
    g<<d.get_number_of_departments()<<endl;
    g<<endl;
    g<<"Delete a department:"<<endl;
    d.delete_department("Oncology");
    g<<"Delete another department:"<<endl;
    d.delete_department("Cardiology");
    g<<endl;
    g<<"Try to delete an non-existent department: "<<endl;
    d.delete_department("Oncology");
    g<<endl;
    g<<d;
    g<<endl;
    g<<"Number of departments after deletion: ";
    g<<d.get_number_of_departments()<<endl;
    g<<endl;
    g<<d;



    Vets m(UtilityReadFromFile ("doctors.txt"));
    g<<endl<<endl;
    g<<m;
    g<<m.get_number_of_vets();
    return 0;
}