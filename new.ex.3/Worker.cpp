#include <iostream>
using namespace std;
#include "Worker.h"
#include <string.h>

Worker::Worker(char* name,long int id,int sen)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name ,name);
    this->ID = id;
    this->seniority = sen;
}
Worker::Worker(const Worker& A)
{
    this->name = new char[strlen(A.name) + 1];
    strcpy(this->name ,A.name);
    this->ID = A.ID;
    this->seniority = A.seniority;
}
Worker::~Worker()
{
    delete [] name;
}
void Worker::print()const
{
    cout << this->name << endl << this->ID << endl << this->seniority << endl;
}
