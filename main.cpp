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


class Departments: private vector<string> {

    public:
    void add_department(string department)
    {
        push_back(department);
    }

    void delete_department(string department)
    {
        if(!(*this).empty())
        {
            (*this).erase(remove((*this).begin(), (*this).end(), department), (*this).end());
        }
    }

    void get_departments() {

        for (int i = 0; i < (*this).size(); i++)
        {
            g<<(*this)[i];
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

class Person 
{
    private:
    string name;
    Birthday birthday;

    public:
    Person()
    {
        name = "";
    }

    Person(string setName, Birthday setBirthday)
    {
        name = setName;
        birthday = setBirthday;
    }
    
    void set_name(string setName)
    {
        name = setName;
    }

    void set_birthday(Birthday setBirthday)
    {
        birthday = setBirthday;
    }

    string get_name()
    {
        return name;
    }
    Birthday get_birthday()
    {
        return birthday;
    }
};


class Vets: public Person {

    float salary = 3000;

    void set_salary(float setSalary)
    {
        salary = setSalary;
    }

    float get_salary()
    {
        return salary;
    }
    
       
};

class LoyaltyPoints
{
    protected:
    virtual float calculate_loyalty_points(int price) = 0;

    virtual ~LoyaltyPoints() {}
};

class Discount
{
    protected:
    virtual float calculate_discount(int price) = 0;
    
    virtual ~Discount() {}
};


class Client : public Person, public Discount, public LoyaltyPoints {

    private:
    string telNumber;
    public:
    Client() : Person()
    {
        telNumber = "";
    }
    Client(string setName, Birthday setBirthday, string setTelNumber) : Person(setName, setBirthday), Discount(), LoyaltyPoints()
    {
       telNumber = setTelNumber;
    }

    string get_tel_no()
    {
        return telNumber;
    }

    float calculate_loyalty_points(int price)
    {
        return 0.15 * price;
    }

    float calculate_discount(int price)
    {
        return (price - (price * 15)/100);
    }

};

class PremiumClient : public Client {

    string name;
    Birthday birthday;
    string telNumber;
    
    public:
    PremiumClient(string setName, Birthday setBirthday, string setTelNum) : Client(setName, setBirthday, setTelNum)
    {
        name = setName;
        birthday = setBirthday;
        telNumber = setTelNum;
    }

    float calculate_discount(int price)
    {
        return (price - (price * 30)/100);
    }

    float calculate_loyalty_points(int price)
    {
        return 0.25 * price;
    }

};




class CustomExceptionName : public exception {
public:
   
    const char* what() const throw() {
        return "A name should be at least 3 characters long!";
    }

};


class Pet {

    protected:

    string name;
    unsigned int age;

    private:
    static int numOfPets;

    public:
    Pet()
    {
        age = 0;
        numOfPets++;
        name = nullptr;
    }

    Pet(string setName, unsigned int setAge)
    {
        numOfPets++;
        name = setName;
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


    void set_name(const char* setName)
    {
           name = setName;
    }

    void set_age(unsigned int setAge)
    {
        age = setAge;
    }

    static int get_num_pets()
    {
        return numOfPets;
    }

    virtual void print_info() = 0;

    virtual ~Pet()
    {
        
       --numOfPets;
     
    }

};

class Dog : public Pet {

    private:
    string food;
    string breed;
    string species;

    public:
    Dog() : Pet()
    {
        breed = "";
        species = "";
    }

    Dog(const char* setName, unsigned int setAge, string setBreed) : Pet(setName, setAge)
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

    void print_info()  
    {
        g << "Dog Information:" << endl;
        g << "Name: " << name << endl;
        g << "Age: " << age << endl;
        g << "Breed: " << breed << endl;
    }

    

};

class Cat : public Pet {

    private:
    string breed;
    string species;
    string food;

    public:
    Cat() : Pet()
    {
        breed = "";
        species = "";
    }

    Cat(const char* setName, unsigned int setAge, string setBreed) : Pet(setName, setAge)
    {
        breed = setBreed;
        species = "Cat";
    }

    string get_breed()
    {
        return breed;
    }

    string get_species()
    {
        return species;
    }

    void print_info()  
    {
        g << "Cat Information:" << endl;
        g << "Name: " << name << endl;
        g << "Age: " << age << endl;
        g << "Breed: " << breed << endl;
    }

};

int Pet::numOfPets = 0;

int main()
{

   Dog dogs[10];
   dogs[0].set_name("Charlie");
   dogs[0].set_age(3);

   Client clients[10];


    return 0;
}