#include <iostream>
using namespace std;

#include "Teacher.h"
#include "Tutor.h"
#include <string.h>

Tutor::Tutor(char* name,long int id,int sen ,int size, char** arr, char* arr_a):Teacher(name ,id ,sen ,size ,arr)
{
    strcpy(this->arr_class, arr_a);
}

Tutor::Tutor(const Tutor& A):Teacher(A)
{
    strcpy(this->arr_class, A.arr_class);
}

void Tutor::print()const
{
    Teacher::print();
    cout << this->arr_class << endl;
}

float Tutor::salary()const
{
    return Teacher::salary() + 1000;
}
