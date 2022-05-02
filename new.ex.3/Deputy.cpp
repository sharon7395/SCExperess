#include <iostream>
using namespace std;

#include "Tutor.h"
#include "Deputy.h"

Deputy::Deputy(char* name,long int id,int sen ,int size, char** arr, char* arr_a):Tutor(name ,id ,sen ,size ,arr ,arr_a)
{
}

Deputy:: Deputy(const Deputy& A):Tutor(A)
{
}

void Deputy::print()const
{
    Tutor::print();
}
float Deputy::salary()const
{
    return Tutor::salary() + 2500;
}
