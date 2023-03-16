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

    char** get_pointer_to_departments() {
        return departments;
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
    Birthday() {
        this->day = day;
        this->month = month;
        this->year = year;
    }
    Birthday(unsigned int day, unsigned int month, unsigned int year)
    {
        this->day = day;
        this->month = month;
        this->year = year;
    }

    Birthday& operator=(const Birthday& birth)
    {
        if(this != &birth)
            {
                day = birth.day;
                month = birth.month;
                year = birth.year;
            }
        return *this;
    }

     friend ostream & operator<< (ostream &os, const Birthday &Array)
    {
        os << Array.day<<"/"<<Array.month<<"/"<<Array.year<< endl;
        return os;
    }
};



class Vets {

    char** vets;
    unsigned int numberOfVets;
    char departmentForVet[50][100];
    Birthday birthForVet[50];

    public:
    Vets()
    {
        vets = nullptr;
        numberOfVets = 0;
        strcpy(departmentForVet[0],NULL);
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

        for(index = 0; index < numberOfVets; index++)
        {
            strcpy(departmentForVet[index], "/");
        }

        for(int index = 0; index < 100; index++)
        {
            birthForVet[index] = Birthday(0,0,0);
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

    void set_department_for_vet(char vetFullName[], char departmentName[], char** validDepartments, unsigned int numberOfValidDepartments)
    {
        int saveIndex = -1;
        bool validDepartment = 0;

        for(int index = 0; index < numberOfValidDepartments; index++)
        {
            if (strcmp(departmentName, validDepartments[index]) == 0)
                validDepartment = 1;
        }

        if (validDepartment == 0)
            g << "Invalid department";
        else {

            for (int index = 0 ; index < numberOfVets; index++)
            if(strcmp(vetFullName, vets[index]) == 0)
            {
                saveIndex = index;
            }

            if (saveIndex != -1)
            {
                strcpy(departmentForVet[saveIndex], departmentName);
            }
            else g<<"Invalid vet";

        }
    }

    void set_birthday_for_vet (char vetFullName[], Birthday birth)
    {
        bool validName = 0;
        unsigned int saveIndex = -1;
        for (int index = 0; index < numberOfVets; index++)
        {
            if (strcmp(vetFullName, vets[index]) == 0)
            {
                validName = 1;
                saveIndex = index;
            }
        }

        if (saveIndex != -1)
        {
            birthForVet[saveIndex] = birth;
        } 
        else g<<"Invalid vet";
    }

    Birthday get_birthday_for_vet(char vetFullName[]) {
        bool validName = 0;
        unsigned int saveIndex = -1;

        for (int index = 0; index < numberOfVets; index++)
        {
            if (strcmp(vetFullName, vets[index]) == 0)
            {
                validName = 1;
                saveIndex = index;
            }
        }

         if (saveIndex != -1)
        {
            return birthForVet[saveIndex];
        } 

    }

    void delete_vet(char vetFullName[])
    {
        int saveIndex = -1;
        for(int index = 0; index < numberOfVets; index++)
        {
            if(strcmp(vetFullName, vets[index]) == 0)
            {
                saveIndex = index;
                break;
            }
        }

        if (saveIndex != 1)
        {
            delete[] vets[saveIndex];

            for(int index = saveIndex; index < numberOfVets - 1; index++)
                vets[index] = vets[index+1];

            for(int index = saveIndex; index < numberOfVets - 1; index++)
                strcpy(departmentForVet[index], departmentForVet[index+1]);
                
            for(int index = saveIndex; index < numberOfVets - 1; index++)
                birthForVet[index] = birthForVet[index+1];

            --numberOfVets;
        }
        else g<<"Invalid vet";
    }

    char* get_department_for_vet(char vetFullName[])
    {
        for(int index = 0; index < numberOfVets; index++)
        {
            if (strcmp(vets[index], vetFullName)==0)
                return departmentForVet[index];
        }
        return "Invalid vet";
    }

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
    g<<endl;


    Vets m(UtilityReadFromFile ("vets.txt"));
    g<<"Vets read from file:"<<endl;
    g<<m<<endl;
    g<<"Number of vets:"<<endl;
    g<<m.get_number_of_vets();
    g<<endl<<endl;
    g<<"Try to assign a department to a non-existent vet"<<endl;
    m.set_department_for_vet("Marian Ivasc", "Neurology", d.get_pointer_to_departments(), d.get_number_of_departments());
    g<<endl<<endl;
    g<<"Try to assing a non-existent department to a vet"<<endl;
    m.set_department_for_vet("Marian Ivascu", "Neurol", d.get_pointer_to_departments(), d.get_number_of_departments());
    g<<endl<<endl;
    g<<"Assign a department to a vet"<<endl;
    m.set_department_for_vet("Marian Ivascu", "Neurology", d.get_pointer_to_departments(), d.get_number_of_departments());
    g<<endl<<endl;
    g<<"Get the department a vet works in:"<<endl;
    g<<m.get_department_for_vet("Marian Ivascu")<<endl;
    g<<m.get_department_for_vet("Ion Constantin")<<endl;
    g<<m.get_department_for_vet("Cornel Sorin");
    g<<endl<<endl;
    g<<"Setting birthday for vet";
    m.set_birthday_for_vet("Marian Ivascu", Birthday(19,6,1989));
    g<<endl;
    m.set_birthday_for_vet("Marian Ivasc", Birthday(19,6,1989));
    g<<endl;
    g<<"Get birthday for vet: ";
    g<<m.get_birthday_for_vet("Marian Ivascu");
    g<<endl<<endl;
    m.delete_vet("Marian Ivascu");
    g<<m;

    return 0;
}