#include <iostream>
#include <fstream>
#include <cstring>
#include <new>

using namespace std;

ifstream f("departments.txt");
ofstream g("out.txt");


class Departments {

    char** departments;
    unsigned int number_of_departments;

    public:
    Departments ()
    {   
        number_of_departments = 0;
        char currentDepartment[100];
        while (f.getline(currentDepartment,100))
        {
            number_of_departments++;
        }

        departments = new char*[number_of_departments];

        unsigned int index = 0;
        
        f.clear();
        f.seekg(0, ios::beg);

        for (int index = 0; index < number_of_departments; index++) 
        {
            f.getline(currentDepartment,100);
            departments[index] = new char[strlen(currentDepartment)];
            strcpy(departments[index], currentDepartment);
        }
    }

    ~Departments()
    {
        delete[] departments;
    }

};

int main()
{
    Departments d;
    return 0;
}