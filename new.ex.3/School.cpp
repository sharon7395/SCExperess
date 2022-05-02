#include <iostream>
using namespace std;

#include "School.h"
#include "Teacher.h"
#include "Temp.h"
#include "Tutor.h"
#include "Manager.h"
#include "Secretary.h"
#include "Deputy.h"

#include <string.h>

School::School()
{
    this->size = 0;
    this->arr = NULL;
    this->manager = false;
}

School::~School()
{
    for(int i = 0; i < size; i++)
    {
        delete arr[i];
    }
    delete [] arr;
}

void School::Menu()
{
    int ch;
    do
    {
        cout << "Choose type of:" << endl << "1.Add worker" << endl << "2.Print workers" << endl << "3.Print profession" << endl << "4.Print tutors" << endl << "5.Print management" << endl << "6.Exit" << endl;
        cin >> ch;
        
        switch (ch)
        {
            case 1:
            {
                Add_worker();
                break;
            }
            case 2:
            {
                for(int i = 0 ; i < size;i++)
                {
                    arr[i]->print();
                    cout<<"The salary is:"<<this->arr[i]->salary()<<endl;
                }
                break;
            }
            case 3:
            {
                char cours[3];
                int i;
                
                cout << "Enter a name of the coruss:" << endl;
                cin >> cours;
                
                for(i = 0;i < this->size ;i++)
                {
                    Teacher* p = dynamic_cast<Teacher*>(arr[i]);
                    if(p != NULL && p->Check(cours) != 0)
                    {
                        p->print();
                    }
                }
                break;
                
            }
            case 4:
            {
                int i;
                
                for(i = 0;i < this->size;i++)
                {
                    Tutor* p = dynamic_cast<Tutor*>(arr[i]);
                    if(p != NULL)
                    {
                        cout << p->get_name() << endl << p->get_class() << endl;
                        
                    }
                }
                break;
            }
            case 5:
            {
                for(int i = 0;i < this->size;i++)
                {
                    
                    Deputy* t = dynamic_cast<Deputy*>(arr[i]);
                    if(t != NULL)
                    {
                        cout << "the deputy is:";
                        t->print();
                    }
                    else
                    {
                        Manager* p = dynamic_cast<Manager*>(arr[i]);
                        if(p != NULL)
                        {
                            cout << "the manager is:";
                            p->print();
                        }
                    }
                }
            }
            case 6:
            {
                return;
            }
            default:
                break;
        }
        
    }while (ch != 6);
    
}

void School::Add_worker_arr(Worker* T_temp)
{
    Worker** temp = new Worker*[this->size + 1];
    
    for(int i = 0;i < this->size;i++)
    {
        temp[i] = this->arr[i];
    }
    delete [] this->arr;
    temp[this->size] = T_temp;
    this->arr = temp;
    this->size++;
    
}

void School::Add_worker()
{
    char name [10] ,ch;
    long int ID;
    int seniority;
    
    cout << "Choose type of worker:" << endl << "A.Teacher" << endl << "B.Temp" << endl << "C.Tutor" << endl << "D.Deputy" << endl << "E.Manager" << endl << "F.Secretary" << endl;
    
    cin >> ch;
    
    cout << "Enter a name:" << endl;
    cin >> name;
    cout << "Enter a id:" << endl;
    cin >> ID;
    for(int i = 0 ; i < this->size;i++)
    {
        if(ID == this->arr[i]->get_id())
        {
            cout << "Error There is a teacher in the school with this ID" << endl;
            return;
        }
    }
    cout << "Enter a seniority:" << endl;
    cin >> seniority;

    switch (ch)
    {
        case 'A':case 'B':case 'C':case 'D':
        {
            int size ,i;
            char** arr;
            
            cout << "Enter a size of coruss:" << endl;
            cin >> size;
            arr = new char*[size];
            for(i = 0 ; i < size;i++)
            {
                arr [i] = new char[10];
                cout << "Enter a name of the coruss:" << endl;
                cin >> arr[i];
            }
            if(ch == 'A')
            {
                Teacher* T_temp = new Teacher(name ,ID ,seniority ,size ,arr);
                Add_worker_arr(T_temp);
            }
            else if(ch == 'B')
            {
                int hours_size;
                cout << "Enter the Overtime" <<endl;
                cin >> hours_size;

                Temp* T_temp = new Temp(name ,ID ,seniority ,size ,arr ,hours_size);
                
                Add_worker_arr(T_temp);
                
            }
            else
            {
                char cours[3];
                
                cout << "Enter a name of the corus is tutor:" << endl;
                cin >> cours;
                for(int i = 0 ; i < this->size;i++)
                {
                    if(Tutor* p = dynamic_cast<Tutor*>(this->arr[i]))
                    {
                        if(strcmp(p->get_class(), cours) == 0)
                        {
                            cout << "Error The teacher is educating another class" << endl;
                            return;
                        }
                    }
                    
                }
                if(ch == 'C')
                {
                    Tutor* T_temp = new Tutor(name ,ID ,seniority ,size ,arr ,cours);
                    Add_worker_arr(T_temp);
                }
                else
                {
                    Deputy* T_temp = new Deputy(name ,ID ,seniority ,size ,arr ,cours);
                    Add_worker_arr(T_temp);
                }
               
            }
            
            for(i = 0; i < size;i++)
            {
                delete [] arr[i];
            }
            delete [] arr;
            
            break;
        }
      
        case 'E':
        {
            if(manager)
            {
                cout << "Eror The school has a manager" << endl;
                return;
            }
            else
            {
                Manager* T_temp = new Manager(name ,ID ,seniority);
                Add_worker_arr(T_temp);
            }
            break;
            
        }
        case 'F':
        {
            int c;
            cout << "Enter the Overtime" << endl;
            cin >> c;
            
            Secretary* T_temp = new Secretary(name ,ID ,seniority ,c);
            Add_worker_arr(T_temp);
            break;
        }
            
        default:
            break;
    }
    
}

