#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <exception>
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

        for (int index = 0; index < 200; index++)
            birthOfPetOwner[index] = Birthday(NULL,NULL,NULL); 

        for (int index = 0; index < 200; index++)
            isMember[index] = NULL;

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

    
    int get_isMember(char FullName[])
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
        else return (-1);
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
            else return procedurePrice;
        }
        else return -1;

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

class PetNameNotInArray : public exception 
{
    string error_message;

    public:
    PetNameNotInArray(const string& message) : error_message(message) {}
    
        const char* what() const noexcept override 
        {
            return error_message.c_str();
        }
};



class Pets {

    char** petNames;
    unsigned int numberOfPets;

    public:
    Pets()
    {
        petNames = nullptr;
        numberOfPets = 0;

    }

    protected:
    Pets(string names[200], unsigned int numberOfNames)
    {
        for (int i = 0; i < numberOfNames; i++)
        {    
            int saveIndex = -1;
            string name = names[i];
            
            for(int index = 0; index < numberOfPets; index++)
            {
                if(name == petNames[index])
                {
                    saveIndex = index;
                    break;
                }
            }

            if (saveIndex == -1)
            {
                throw PetNameNotInArray("One or more invalid pet names");
            }
        }
    }

    unsigned int get_pet_index_in_array (string name)
    {
        int saveIndex = -1;
        
        for(int index = 0; index < numberOfPets; index++)
        {
            if(name == petNames[index])
            {
                saveIndex = index;
                break;
            }
         }

        if (saveIndex == -1)
        {
            throw PetNameNotInArray("One or more invalid pet names");
        }

        return saveIndex;
    }

    public:
    Pets(Pets& p)
    {
        if (p.petNames != nullptr) {
            numberOfPets = p.numberOfPets;
            petNames = new char*[numberOfPets];
            for(int index = 0; index < numberOfPets; index++)
            {
                petNames[index] = new char[strlen(p.petNames[index])+1];
                strcpy(petNames[index], p.petNames[index]);
            }
        }
    }

      friend ostream & operator<< (ostream &os, const Pets &Array)
    {
            for(int index = 0; index < Array.numberOfPets; index++)
                os << Array.petNames[index] << endl;

        return os;
    }

    unsigned int get_number_of_pets() {
        return numberOfPets;
    }

    void set_new_pet(const char newPet[])
    {
            
        char** newArr = new char*[numberOfPets + 1];
        memcpy(newArr, petNames, numberOfPets * sizeof(char*));
        newArr[numberOfPets] = new char[strlen(newPet)+1];
        strcpy(newArr[numberOfPets], newPet);

        petNames = newArr;
        
        numberOfPets++;
    
    }

        void delete_pet(char pet[])
    {
        int saveIndex = -1;
        for(int index = 0; index < numberOfPets; index++)
        {
            if(strcmp(pet, petNames[index]) == 0)
            {
                saveIndex = index;
                break;
            }
         }

        if (saveIndex != -1)
        {
            delete[] petNames[saveIndex];

            for(int index = saveIndex; index < numberOfPets - 1; index++)
                petNames[index] = petNames[index+1];

            --numberOfPets;
        }
        else g<<"Invalid owner name.";
    }


    ~Pets() {
        if(petNames != nullptr)
        {
            for(int index = 0; index < numberOfPets; index++)
                delete[] petNames[index];
            delete[] petNames;
        }
    }
};

class Dogs : public Pets
{
    private:
    string species[200];
    public:
    Dogs(string names[200], unsigned int numberOfNames, const string dogSpecies = "Dog") : Pets(names, numberOfNames) {

        for (int index = 0; index < numberOfNames; index++)
        {
            string name = names[index];
            species[Pets::get_pet_index_in_array(name)] = dogSpecies;
        }
    }
};

int main()
{

Pets pet;
pet.set_new_pet("nacho");
g<<pet.get_number_of_pets();

    return 0;
}