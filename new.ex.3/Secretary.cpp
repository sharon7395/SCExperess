#include <iostream>
using namespace std;

#include "Secretary.h"
#include "Worker.h"

Secretary::Secretary(char* name,long int id,int sen ,int hours):Worker(name, id, sen)
{
    this->over_time = hours;
}
Secretary::Secretary(const Secretary& A):Worker(A)
{
    this->over_time = A.over_time;
    
}
void Secretary::print()const
{
    Worker::print();
    cout << this->over_time << endl;
}

float Secretary::salary()const
{
    return 5000 + (get_sen() * 200) + (get_hours() * 60);
}
