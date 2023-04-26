#include <iostream>
#include <stdio.h>
#include <fstream>
#include <cstring>
#include <string>
#include <vector>
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

class LoyaltyPoints
{
    private:
    int points;
    protected:
    virtual float calculate_loyalty_points(int price) = 0;
    
};

class Discount
{
    protected:
    virtual float calculate_discount(int price);
    
    virtual ~Discount() {}
};

class Client : public Discount, public LoyaltyPoints {

    string name;
    Birthday birthday;
    
    public:
    Client(string setName, Birthday setBirthday) : Discount(), LoyaltyPoints()
    {
        name = setName;
        birthday = setBirthday;
    }

    string get_name()
    {
        return name;
    }

    string print_birthday()
    {
        g<<birthday;
    }

    void calculate_loyalty_points

    float calculate_discount(int price)
    {
        return (price - (price * 15)/100);
    }

};

class PremiumClient : public Discount, public LoyaltyPoints {

    string name;
    Birthday birthday;
    
    public:
    PremiumClient(string setName, Birthday setBirthday) : Discount(), LoyaltyPoints()
    {
        name = setName;
        birthday = setBirthday;
    }

    string get_name()
    {
        return name;
    }

    string print_birthday()
    {
        g<<birthday;
    }

    float calculate_discount(int price)
    {
        return (price - (price * 30)/100);
    }

};




class CustomException : public exception {
public:
   
    const char* what() const throw() {
        return "You shouldn't reset a property, it could lead to unwanted bugs!";
    }

};


class Pet {

    protected:

    string name;
    string owner;
    unsigned int age;

    public:
    Pet()
    {
        age = 0;
        name = nullptr;
        owner = "";
    }

    Pet(string setName, string setOwner, unsigned int setAge)
    {
        name = setName;
        owner = setOwner;
        age = setAge;
    }

    unsigned int get_age() const
    {
        return age;
    }

    string get_name() const
    {
        return name;
    }

    string get_owner() const
    {
        return owner;
    }

    void set_name(const char* setName)
    {
        try
        {
           name = setName;
           throw CustomException();
        }
        catch(const CustomException& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

     virtual void print_info() const
    {
        g << "Pet Information:" << endl;
        g << "Name: " << name << endl;
        g << "Owner: " << owner << endl;
        g << "Age: " << age << endl;
    }

    virtual ~Pet()
    {
       
    }

};

class Dog : public Pet {

    private:
    string breed;
    string species;

    public:
    Dog() : Pet()
    {
        breed = "";
        species = "";
    }

    Dog(const char* setName, string setOwner, unsigned int setAge, string setBreed) : Pet(setName, setOwner, setAge)
    {
        breed = setBreed;
        species = "Dog";
    }

    string get_breed()
    {
        return breed;
    }

    string get_species()
    {
        return species;
    }

    void print_info() const override
    {
        g << "Dog Information:" << endl;
        g << "Name: " << name << endl;
        g << "Owner: " << owner << endl;
        g << "Age: " << age << endl;
        g << "Breed: " << breed << endl;
    }

    

};

int main()
{

    Pet* pet = new Dog("Dorel", "Teo", 3, "Goldie");
    pet->print_info();
    delete pet;

    Dog d();

    Pet p("Costinel", "Teo", 3);
   
    g<<p.get_age()<<endl;

    Client c();


    return 0;
}