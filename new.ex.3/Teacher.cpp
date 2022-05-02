#include <iostream>
using namespace std;

#include "Teacher.h"
#include "Worker.h"
#include <string.h>

Teacher::Teacher(char* name,long int id,int sen ,int size, char** arr):Worker(name, id, sen)
{
    this->size = size;
    this->arr = new char* [size];
    if(this->arr == NULL)
    {
        return;
    }
    for(int i = 0;i < size ;i++)
    {
        this->arr[i] = new char[strlen(arr[i]) + 1];
        if(this->arr[i])
            return;
        strcpy(this->arr[i],arr[i]);
    }
}
Teacher::Teacher(const Teacher& A):Worker(A)
{
    this->size = A.size;
    this->arr = new char* [A.size];
    if(this->arr == NULL)
    {
        return;
    }
    for(int i = 0;i < A.size ;i++)
    {
        this->arr[i] = new char[strlen(A.arr[i]) + 1];
        if(this->arr[i])
            return;
        strcpy(this->arr[i],A.arr[i]);
    }
}
void Teacher::print()const
{
    Worker::print();
    cout << this->size << endl;
    for(int i = 0;i < size;i++)
    {
        cout << arr[i] << endl;
    }
}

float Teacher::salary()const
{
    return 5000 + (get_sen() * 500) + (300 * size);
}

Teacher::~Teacher()
{
    for(int i = 0;i < size;i++)
    {
        delete [] arr[i];
    }
    delete [] arr;
    
}

bool Teacher::Check(char* arr)const
{
    for(int i = 0;i < size; i++)
    {
        if(strcmp(this->arr[i],arr) == 0)
            return true;
    }
    
    return false;
}
