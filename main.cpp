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

ifstream c("pet_owners.txt");


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


class Vet: public Person {

    float salary;
    static int numOfVets;

    public:
    Vet() : Person()
    {
        numOfVets++;
        salary = 3000;
    }

    Vet(string setName, Birthday setBirthday) : Person(setName, setBirthday)
    {
        numOfVets++;
        salary = 3000;
    }

    void set_salary(float setSalary)
    {
        salary = setSalary;
    }

    float get_salary()
    {
        return salary;
    }

    static unsigned int get_num_of_vets()
    {
        return numOfVets;
    }
    
    virtual ~Vet()
    {
        numOfVets--;
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




class NotLongEnoughName : public exception {
public:
   
    const char* what() const throw() {
        return "A name should be at least 3 characters long!";
    }

};

class InvalidAge : public exception {
public:
   
    const char* what() const throw() {
        return "One's age cannot be a negative value!";
    }

};

class InvalidSalary : public exception {
public:
   
    const char* what() const throw() {
        return "One's salary cannot be less than 3000";
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
        name = "";
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


    void set_name(string setName)
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
    string breed;
    string species;

    public:
    Dog() : Pet()
    {
        breed = "";
        species = "";
    }

    Dog(string setName, unsigned int setAge, string setBreed) : Pet(setName, setAge)
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

    public:
    Cat() : Pet()
    {
        breed = "";
        species = "";
    }

    Cat(string setName, unsigned int setAge, string setBreed) : Pet(setName, setAge)
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
int Vet::numOfVets = 0;

int main()
{
   Client clients[10];
   int i = 0;
   string names[10]={"Maria Ionescu","Ion Constantin", "Va"};
   
   for (int i=0; i < names->length(); i++)
   {
    try
    {
        if (names[i].length() < 3)
        {
            throw(NotLongEnoughName());
            
        }
        else
        {
            clients[i].set_name(names[i]);
        }
        
    }
    catch(const NotLongEnoughName& e)
    {
        std::cerr << e.what() << '\n';
    }

   
    
   }
   Dog dogs[2];
   g << Pet::get_num_pets();
   int ages[10]={2, -3, 5};

   string DogNames[2]={"Dorel","te"};
   for (int i =0; i< 2; i++)
   {
        dogs[i].set_name(DogNames[i]);

    try
    {
        if(ages[i] < 0)
        {
            throw(InvalidAge());
        }
        else
        {
            dogs[i].set_age(ages[i]);
        }
    
    }
    catch(const InvalidAge& r)
    {
        std::cerr << r.what() << endl;
    }
   }

    Vet vets[2];
    string VetNames[2]={"Costelus","Maria"};
    int salary[2] = {100, 60000};
    for(int i = 0; i < 2; i++)
    {
        vets[i].set_name(VetNames[i]);

        try
        {
            if(salary[i] < 3000)
            {
                throw(InvalidSalary());
            }
            else
            {
                vets[i].set_salary(salary[i]);
            }
        }
        catch(const InvalidSalary& e)
        {
            std::cerr << e.what() << '\n';
        }
        
    }

    return 0;
}