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
        if (departments!=nullptr)
        {
            for (int index = 0 ;index < numberOfDepartments ; index++)
                delete[] departments[index];
            delete[] departments;
        }
       
    }

};



class Birthday 
{

    unsigned int day, month, year;

    public:
    Birthday() {
        this->day = 0;
        this->month = 0;
        this->year = 0;
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
    unsigned int netSalary[50];

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

        for(index = 0; index < numberOfVets; index++)
        {
            strcpy(departmentForVet[index], "/");
        }

        for(int index = 0; index < 50; index++)
        {
            birthForVet[index] = Birthday(0,0,0);
        }

        for(index = 0; index < 50; index++)
            netSalary[index] = 3000;
       
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

        if (saveIndex != -1)
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

    void set_new_vet(const char* newVet)
    {
        char** newArr = new char*[numberOfVets + 1];
        memcpy(newArr, vets, numberOfVets * sizeof(char*));
        newArr[numberOfVets] = new char[strlen(newVet)+1];
        strcpy(newArr[numberOfVets], newVet);

        vets = newArr;
        
        numberOfVets++;
    }

       void set_department_for_vet(char vetFullName[], char departmentName[], char** validDepartments, unsigned int numberOfValidDepartments)
    {
        int saveIndex = -1;
        bool validDepartment = 0;

        for(int index = 0; index < numberOfValidDepartments; index++)
        {
            if (strcmp(departmentName, validDepartments[index]) == 0)
               { 
                validDepartment = 1;
                break;
               }
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

    char* get_department_for_vet(char vetFullName[])
    {
        for(int index = 0; index < numberOfVets; index++)
        {
            if (strcmp(vets[index], vetFullName)==0)
                return departmentForVet[index];
        }
        return "Invalid vet";
    }

    void set_netSalary(char vetFullName[], unsigned int salary)
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

        if (saveIndex != -1)
        {
            if (salary < 3000)
                g<<"Invalid salary value. Must be over 3000";
            else
            {
                netSalary[saveIndex] = salary;
            }
        }
        else g<<"Invalid vet";
    }

    unsigned int get_netSalary(char vetFullName[])
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

        if (saveIndex != -1)
        {
            return netSalary[saveIndex];
        }
        return -1;
    }

    float get_hourly_salary(char vetFullName[])
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

        if (saveIndex != -1)
        {
            return float(netSalary[saveIndex])/160;
        }
        else return -1;
    }

    unsigned int get_anual_salary(char vetFullName[])
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

        if (saveIndex != -1)
        {
            return netSalary[saveIndex]*12;
        }
        else return -1;
    }

    void get_full_vet_info(char vetFullName[])
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

        if (saveIndex != -1)
        {
            g<<vets[saveIndex]<<endl<<departmentForVet[saveIndex]<<endl<<birthForVet[saveIndex]<<netSalary[saveIndex];
        }
        else g<<"Invalid vet name";
    }

    ~Vets()
    {
        for (int index = 0; index < numberOfVets; index++)
            delete[] vets[index];
        delete[] vets;
    }
};

class PetOwners {

    char** petOwners;
    int numberOfPetOwners;
    Birthday birthOfPetOwner[200];
    bool isMember[200];

    public: 

    PetOwners()
    {
        petOwners = nullptr;
        numberOfPetOwners = 0;
    }
    
    PetOwners(UtilityReadFromFile read)
    {
        numberOfPetOwners = read.get_length();
        petOwners = new char*[numberOfPetOwners];

        unsigned int index = 0;
        for(index = 0; index < numberOfPetOwners; index++)
        {
             this->petOwners[index] = new char[strlen(read.get_array()[index])];
            strcpy(this->petOwners[index], read.get_array()[index]);
        }

        for (int index = 0; index < 200; index++)
            birthOfPetOwner[index] = Birthday(0,0,0); 
    

        for (int index = 0; index < 200; index++)
            isMember[index] = 0;
    }


    friend ostream & operator<< (ostream &os, const PetOwners &Array)
    {
            for(int index = 0; index < Array.numberOfPetOwners; index++)
                os << Array.petOwners[index] << endl;

        return os;
    }
   

   unsigned int get_number_of_pet_owners()
   {
        return numberOfPetOwners;
   }

    void set_new_petOwner(const char* newPetOwner)
    {
        char** newArr = new char*[numberOfPetOwners + 1];
        memcpy(newArr, petOwners, numberOfPetOwners * sizeof(char*));
        newArr[numberOfPetOwners] = new char[strlen(newPetOwner)+1];
        strcpy(newArr[numberOfPetOwners], newPetOwner);

        petOwners = newArr;
        
        numberOfPetOwners++;
    }


       void delete_petOwner(char FullName[])
    {
        int saveIndex = -1;
        for(int index = 0; index < numberOfPetOwners; index++)
        {
            if(strcmp(FullName, petOwners[index]) == 0)
            {
                saveIndex = index;
                break;
            }
         }

        if (saveIndex != -1)
        {
            delete[] petOwners[saveIndex];

            for(int index = saveIndex; index < numberOfPetOwners - 1; index++)
                petOwners[index] = petOwners[index+1];
                
            for(int index = saveIndex; index < numberOfPetOwners - 1; index++)
                 birthOfPetOwner[index] = birthOfPetOwner[index+1];

            --numberOfPetOwners;
        }
        else g<<"Invalid owner name.";
    }

     void set_birthday_for_petOwner(char FullName[], Birthday birth)
    {
        bool validName = 0;
        unsigned int saveIndex = -1;
        for (int index = 0; index < numberOfPetOwners; index++)
        {
            if (strcmp(FullName, petOwners[index]) == 0)
            {
                validName = 1;
                saveIndex = index;
            }
        }

        if (saveIndex != -1)
        {
            birthOfPetOwner[saveIndex] = birth;
        } 
        else g<<"Invalid vet";
    }

    Birthday get_birthday_for_perOwner(char FullName[]) {
        bool validName = 0;
        unsigned int saveIndex = -1;

        for (int index = 0; index < numberOfPetOwners; index++)
        {
            if (strcmp(FullName, petOwners[index]) == 0)
            {
                validName = 1;
                saveIndex = index;
            }
        }

         if (saveIndex != -1)
        {
            return birthOfPetOwner[saveIndex];
        } 
    }

    void set_isMember(char FullName[])
    {
         unsigned int saveIndex = -1;

        for (int index = 0; index < numberOfPetOwners; index++)
        {
            if (strcmp(FullName, petOwners[index]) == 0)
            {
                saveIndex = index;
                break;
            }
        }
        if (saveIndex != -1)
        {
            isMember[saveIndex] = 1;
        }
    }

    bool get_isMember(char FullName[])
    {
         unsigned int saveIndex = -1;

        for (int index = 0; index < numberOfPetOwners; index++)
        {
            if (strcmp(FullName, petOwners[index]) == 0)
            {
                saveIndex = index;
                break;
            }
        }
        if (saveIndex != -1)
        {
            return isMember[saveIndex];
        }
    }

    float apply_discount15_if_isMember(char FullName[], unsigned int procedurePrice)
    {
        unsigned int saveIndex = -1;

        for (int index = 0; index < numberOfPetOwners; index++)
        {
            if (strcmp(FullName, petOwners[index]) == 0)
            {
                saveIndex = index;
                break;
            }
        }
        if (saveIndex != -1)
        {
            if (isMember[saveIndex] == 1)
            {
                return float(0.75 * procedurePrice);
            }
        }

    }

    ~PetOwners()
    {
        if(petOwners != nullptr)
        {
            for(int index = 0; index < numberOfPetOwners; index++)
                delete[] petOwners[index];
            delete[] petOwners;
        }
    }

};

int main()
{
    UtilityReadFromFile read("departments.txt");
    Departments d(read), f;

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
    g<<"Add department to an empty departments array:"<<endl;
    f.set_new_department("Diabetology");
    g<<f.get_number_of_departments()<<endl;
    g<<f;
    g<<endl<<endl;


    Vets m(UtilityReadFromFile ("vets.txt")),n;
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
    m.set_birthday_for_vet("Ioana Popescu", Birthday(19,6,1989));
    g<<endl;
    g<<"Get birthday for vet: ";
    g<<m.get_birthday_for_vet("Ioana Popescu");
    g<<endl<<endl;
    m.delete_vet("Marian Ivascu");
    g<<m;
    g<<endl;
    g<<"Add new vet:"<<endl;
    m.set_new_vet("Ion Constantin");
    g<<m;
    g<<endl;
    g<<"Add new vet to empty vets array:"<<endl;
    n.set_new_vet("Ionel Cornel");
    g<<n;
    n.set_department_for_vet("Ionel Cornel", "Neurology", d.get_pointer_to_departments(), d.get_number_of_departments());
    g<<n.get_department_for_vet("Ionel Cornel");
    n.set_birthday_for_vet("Ionel Cornel", Birthday(2,3,1967));
    g<<endl;
    g<<n.get_birthday_for_vet("Ionel Cornel");
    g<<endl;
    g<<"Set and get salary for a vet"<<endl;
    m.set_netSalary("Ioana Popescu", 3500);
    g<<m.get_netSalary("Ioana Popescu")<<endl;
    g<<"Get hourly salary:"<<endl;
    g<<m.get_hourly_salary("Ioana Popescu")<<endl;
    g<<"Get annual salary:"<<endl;
    g<<m.get_anual_salary("Ioana Popescu")<<endl;
    g<<"Get full vet info:"<<endl;
    g<<endl;
    m.get_full_vet_info("Ioana Popescu");

    g<<endl<<endl;

    PetOwners p(UtilityReadFromFile ("pet_owners.txt"));
    g<<p;
    g<<p.get_number_of_pet_owners()<<endl;
    g<<endl;
    p.set_new_petOwner("Maria Lefter");
    g<<p;
    g<<p.get_number_of_pet_owners()<<endl;
    p.delete_petOwner("Maria Lefter");
    g<<endl;
    p.set_new_petOwner("Maria Lefter");
    p.set_birthday_for_petOwner("Maria Lefter", Birthday(3,4,1978));
    g<<p.get_birthday_for_perOwner("Maria Lefter");
    g<<p<<endl;
    p.set_isMember("Maria Lefter");
    g<<p.get_isMember("Maria Lefter");
    g<<endl;
    g<<p.apply_discount15_if_isMember("Maria Lefter", 100);



    return 0;
}