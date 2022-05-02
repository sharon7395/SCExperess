#include <iostream>
using namespace std;

#include "Manager.h"
#include "Worker.h"

Manager::Manager(char* name,long int id,int sen):Worker(name, id, sen)
{
}
Manager::Manager(const Manager& A):Worker(A)
{
}
void Manager::print()const
{
    Worker::print();
}

float Manager::salary()const
{
    return 1000 + (get_sen() * 800);
}
