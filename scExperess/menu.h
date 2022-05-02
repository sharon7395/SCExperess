#include "Cart.h"
#include "searchProduct.h"

void mainMenu();
void printGeneralOptions();//A function that print the menu to screen.
Manager* ManagerEntranceLoop(Manager* managers, int* size, float* profit);
void printManagerEntranceOptions();//A function that print the menu to screen.
Client* ClientEntranceLoop(Client* clients, int* size);
void printClientEntranceOptions();//A function that print the menu to screen.
void ManagerLoop(float* profit, Manager m);
void printManagerOptions();//A function that print the menu to screen.
void ClientLoop(Client c);
void printCartMenu();
Product* ActionsOnProducts(Product* list, int* size);
void printClientOptions();//A function that print the menu to screen.
void Searches(Product* products, int size);//sub menu of different searches
void Get_Rating_vars(int* tr, int* rcount);
void Set_Rating_vars(int tr, int rcount);