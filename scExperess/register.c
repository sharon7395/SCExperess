#define _CRT_SECURE_NO_WARNINGS
#include "Register.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


//client register
Client* ClientRegister(Client* list, int* size)
{
    FILE* fp;
    int i, flag = 1, id, password;
    char userName[50], filename[50];
    char clubMember, status;
    printf("                        ---CLIENT REGISTRATION--- \n");
    printf("please enter your User Name: ");
    do {
        getchar();
        gets(userName);
        for (i = 0; i < strlen(userName); i++)
        {
            if ((userName[i] >= 65 && userName[i] <= 122) || userName[i] == ' ')
            {
                if (userName[i] == ' ')
                {
                    if (i == 0 || i == strlen(userName) - 1)
                    {
                        flag = 0;

                    }
                }
                else if (i == strlen(userName) - 1)
                    flag = 1;
                continue;
            }

            printf("Your User Name must be your full name, only letters are allowed, please try again: ");
            flag = 0;
            break;
        }
    } while (flag == 0);

    flag = 1;
    printf("please enter your Id: ");
    do {
        scanf("%d", &id);
        flag = 1;
        if (id < 100000000 || id > 999999999)
        {
            printf("Id must be 9 digits. please try again ");
            flag = 0;
        }

    } while (flag == 0);



    printf("please enter your Password: ");
    flag = 1;
    do {
        scanf("%d", &password);
        flag = 1;
         if (password < 10000 || password > 99999)
         {
             printf("Password must be 5 digits. please try again ");
             flag = 0;
         }
    } while (flag == 0);
    clubMember = 'n';
    status = 'y';

    list = Add_Client(list, size, userName, id, password, status, clubMember);
    sprintf(filename, "%d.txt", id);
    fp = fopen(filename, "w");
    fclose(fp);
    return list;
}

//set all products data in "Users.csv" file
void set_All_Data_Client(Client* list, int size)
{
    FILE* fw;

    fw = fopen("Clients.csv", "w");//open file for writing
    if (fw == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
        fprintf(fw, "%s,%d,%d,%c,%c\n", list[i].name, list[i].id, list[i].password, list[i].status, list[i].clubMember);
    fclose(fw);//close file
}

Client* get_All_Data_Client(Client* list, int* size)
{
    FILE* fr;
    char line[500];
    char* sp, * name;
    int id, pas, status, clubmember;

    fr = fopen("Clients.csv", "r");//open file for reading
    if (fr == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    while (fgets(line, 500, fr) != NULL)
    {
        sp = strtok(line, ",");
        name = (char*)malloc((strlen(sp) + 1) * sizeof(char));
        if (name == NULL)
        {
            printf("Allocate memory failed.\n");
            exit(1);
        }
        strcpy(name, sp);
        sp = strtok(NULL, ",");
        id = atoi(sp);
        sp = strtok(NULL, ",");
        pas = atoi(sp);
        sp = strtok(NULL, ",");
        status = sp[0];
        sp = strtok(NULL, ",");
        clubmember = sp[0];
        list = Add_Client(list, size, name, id, pas, status, clubmember);
    }
    fclose(fr);//close file
    return list;
}

//client login
int ClientLogin(Client* list, int* size)
{
    int i, flag = 0, flag2 = 1, id, password, clientIndex;
    char userName[50];
    char clubMember;
    printf("                        ---CLIENT LOG IN--- \n");
    printf("please enter your Id: ");
    scanf("%d", &id);
    for (i = 0; i < *size; i++)
    {
        if (list[i].id == id)
        {
            flag = 1;
            clientIndex = i;
        }

    }
    if (flag == 0)
    {
        printf("This user Id does not registered in the system, if tou are a new user, go to registration");
        return -1;
    }

    printf("please enter your User Name: ");
    getchar();
    gets(userName);
    if (strcmp(list[clientIndex].name, userName) != 0)
    {
        printf("User name does not exists");
        return -1;
    }

    printf("please enter your password: ");
    scanf("%d", &password);
    if (list[clientIndex].password != password)
    {
        printf("this password does not match your user details");
        return -1;
    }

    if (list[clientIndex].status == 'n')
    {
        printf("This user is blocked. Please contact management for more details");
        return -1;
    }
    if (list[clientIndex].clubMember == 'n')
        list[clientIndex].clubMember = ClubMember();

    return clientIndex;
}

 //actions on a client
void ActionsOnClient(Client* c, int clients_size)
{
    int flag = 0;
    char userName[50];
    int id, password, index = -1;
    printf("Please enter client's details: \n");
    do {
        printf("Name: ");
        getchar();
        gets(userName);
        printf("Id: ");
        scanf("%d", &id);
        for (int i = 0; i < clients_size; i++)
            if (c[i].id == id)
                index = i;

        if (strcmp(userName, c[index].name) == 0 && id == c[index].id)
        {
            flag = 1;
        }
        //flag = 0;
        if (flag == 0)
            printf("User Name or Id are Incorrect , please try again: ");

    } while (flag == 0);
    //switchcase block un block
    int run = 1, option;
    while (run)
    {  //while we still want to run:
        printBlockOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option)
        {//act accordingly:
        case 1:
            c[index].status = 'n';
            printf("This user is now blocked.");
            run = 0;
            break;//end of this iteration
        case 2:
            c[index].status = 'y';
            printf("This user is now unblocked.");
            run = 0;
            break;
        case 3:
            run = 0; //we want to stop running.
            //printf("The system closed successfully\n");
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
}

//A function that print the menu to screen.
void printBlockOptions()
{
    printf("Please choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- Block this user\n");
    printf("2- Unblock this user\n");
    printf("3- Exit\n");
    printf("----------------------------------------------------------------------\n");
}//end method printManagerOptions()

//adding manager into the manager's list
Manager* Add_Manager(Manager* list, int* size, char* name, int id, int pas)
{
    Manager* newlist = NULL;

    newlist = (Manager*)malloc((*size + 1) * sizeof(Manager));
    if (newlist == NULL)
    {
        printf("Allocate memory failed.\n");
        exit(1);
    }
    //copy old list
    for (int i = 0; i < *size; i++)
    {
        newlist[i].name = (char*)malloc((strlen(list[i].name) + 1) * sizeof(char));
        if (newlist[i].name == NULL)
        {
            printf("Allocate memory failed.\n");
            exit(1);
        }
        strcpy(newlist[i].name, list[i].name);

        newlist[i].id = list[i].id;
        newlist[i].password = list[i].password;
    }

    //add new product
    newlist[*size].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    if (newlist[*size].name == NULL)
    {
        printf("Allocate memory failed.\n");
        exit(1);
    }
    strcpy(newlist[*size].name, name);
    newlist[*size].id = id;
    newlist[*size].password = pas;

    (*size)++;
    //delete old list
    for (int i = 0; i < *size - 1; i++)
        free(list[i].name);

    free(list);
    return newlist;
}

//adding manager into the manager's list
Client* Add_Client(Client* list, int* size, char* name, int id, int pas, char status, char clubmember)
{
    Client* newlist = NULL;

    newlist = (Client*)malloc((*size + 1) * sizeof(Client));
    if (newlist == NULL)
    {
        printf("Allocate memory failed.\n");
        exit(1);
    }
    //copy old list
    for (int i = 0; i < *size; i++)
    {
        newlist[i].name = (char*)malloc((strlen(list[i].name) + 1) * sizeof(char));
        if (newlist[i].name == NULL)
        {
            printf("Allocate memory failed.\n");
            exit(1);
        }
        strcpy(newlist[i].name, list[i].name);

        newlist[i].id = list[i].id;
        newlist[i].password = list[i].password;
        newlist[i].status = list[i].status;
        newlist[i].clubMember = list[i].clubMember;
    }

    //add 
    newlist[*size].name = (char*)malloc((strlen(name) + 1) * sizeof(char));
    if (newlist[*size].name == NULL)
    {
        printf("Allocate memory failed.\n");
        exit(1);
    }
    strcpy(newlist[*size].name, name);
    newlist[*size].id = id;
    newlist[*size].password = pas;
    newlist[*size].status = status;
    newlist[*size].clubMember = clubmember;

    (*size)++;
    //delete old list
    for (int i = 0; i < *size - 1; i++)
        free(list[i].name);

    free(list);
    return newlist;
}

//manager register
Manager* ManagerRegister(Manager* list, int* size)
{
    int i, flag = 1;
    char userName[50];
    int id, password;
    printf("                        ---MANAGER REGISTRATION--- \n");
    printf("please enter your User Name: ");
    getchar();
    gets(userName);
    printf("please enter your Id: ");
    do {
        flag = 1;
        scanf("%d", &id);
        
        if (id < 100000000 || id > 999999999)
        {
            printf("Id must be 9 digits. please try again\n");
            flag = 0;
        }
        else
            flag = 1;

    } while (flag == 0);

    printf("please enter your Password: ");
    flag = 1;
    do {
        scanf("%d", &password);
        flag = 1;
        if (password < 10000 || password > 99999)
        {
            printf("Password must be 5 digits. please try again ");
            flag = 0;

        }
        else
            flag = 1;
    } while (flag == 0);

    list = Add_Manager(list, size, userName, id, password);
    return list;
}

//set all products data in "Users.csv" file
void set_All_Data_Manager(Manager* list, int size)
{
    FILE* fw;

    fw = fopen("Managers.csv", "w");//open file for writing
    if (fw == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    for (int i = 0; i < size; i++)
        fprintf(fw, "%s,%d,%d\n", list[i].name, list[i].id, list[i].password);
    fclose(fw);//close file
}

Manager* get_All_Data_Manager(Manager* list, int* size)
{
    FILE* fr;
    char line[500];
    char* sp, * name;
    int id, pas;

    fr = fopen("Managers.csv", "r");//open file for reading
    if (fr == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    while (fgets(line, 500, fr) != NULL)
    {
        sp = strtok(line, ",");
        name = (char*)malloc((strlen(sp) + 1) * sizeof(char));
        if (name == NULL)
        {
            printf("Allocate memory failed.\n");
            exit(1);
        }
        strcpy(name, sp);
        sp = strtok(NULL, ",");
        id = atoi(sp);
        sp = strtok(NULL, ",");
        pas = atoi(sp);

        list = Add_Manager(list, size, name, id, pas);
    }
    fclose(fr);//close file
    return list;
}

//manager login
int ManagerLogin(Manager* list, int* size)
{
    int i, flag = 0, flag2 = 1, id, password, ManagerIndex;
    char userName[50];
    printf("                        ---MANAGER LOG IN--- \n");
    printf("please enter your Id: ");
    scanf("%d", &id);
    for (i = 0; i < *size; i++)
    {
        if (list[i].id == id)
        {
            flag = 1;
            ManagerIndex = i;
        }

    }
    if (flag == 0)
    {
        printf("This user Id does not registered in the system, if tou are a new user, go to registration");
        return -1;
    }

    printf("please enter your User Name: ");
    getchar();
    gets(userName);
    if (strcmp(list[ManagerIndex].name, userName) != 0)
    {
        printf("User name does not exists");
        return -1;
    }

    printf("please enter your password: ");
    scanf("%d", &password);
    if (list[ManagerIndex].password != password)
    {
        printf("this password does not match your user details\n");
        return -1;
    }

    return ManagerIndex;

}

char ClubMember()
{
    int option;
    while (1)
    {
        printf("do you want to be a club member? choose one of the following options: \n ");
        printf("1 - yes \n ");
        printf("2 - no \n ");
        scanf("%d", &option);
        if (option == 1)
            return 'y';
        else if (option == 2)
            return 'n';
        else
            printf("Wrong number, please try again\n");
    }
}






