#include <iostream>
using namespace std;

#include "Temp.h"
#include "Teacher.h"

Temp::Temp(char* name,long int id,int sen ,int size, char** arr ,int hours):Teacher(name ,id ,sen ,size ,arr)
{
    this->weekly_hours = hours;
}

Temp::Temp(const Temp& A):Teacher(A)
{
    this->weekly_hours = A.weekly_hours;
}

void Temp::print()const
{
    Teacher::print();
    cout << this->weekly_hours << endl;
}

float Temp::salary()const
{
    if(get_sen() > 5 && weekly_hours > 10)
    {
        return (300 * weekly_hours) + 700;
    }
    else
        return 300 * weekly_hours;
}
