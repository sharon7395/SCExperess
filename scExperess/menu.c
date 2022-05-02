#include "menu.h"

#pragma warning(disable: 4996)
#define _CRT_SECURE_NO_WARNINGS


void mainMenu()
{
    Manager* managers = NULL;
    Client* clients = NULL;
    int managers_size = 0, clients_size = 0;
    int GeneralRun = 1;//do we want another iteration?
    int option;//the choosen option for the menu.
    float profit = 0.0;
    managers = get_All_Data_Manager(managers, &managers_size);
    clients = get_All_Data_Client(clients, &clients_size);
    while (GeneralRun)
    {  //while we still want to run:
        printGeneralOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option)
        {//act accordingly:
        case 1:
            managers = ManagerEntranceLoop(managers, &managers_size, &profit);
            //activate the methods that resposible for it
            break;//end of this iteration
        case 2:
            clients = ClientEntranceLoop(clients, &clients_size);
            break;
        case 3:
            GeneralRun = 0; //we want to stop running.
            printf("The system closed successfully\n");
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
    set_All_Data_Client(clients, clients_size);
    set_All_Data_Manager(managers, managers_size);
}

//A function that print the menu to screen.
void printGeneralOptions()
{
    printf("Please choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- Access manager menu\n");
    printf("2- Access client menu\n");
    printf("3- Exit\n");
    printf("----------------------------------------------------------------------\n");
}//end method printManagerOptions()

Manager* ManagerEntranceLoop(Manager* managers, int* size, float* profit)
{
    int ManagerEntranceRun = 1;//do we want another iteration?
    int option;//the choosen option for the menu.
    int index;
    while (ManagerEntranceRun)
    {  //while we still want to run:
        printManagerEntranceOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option)
        {//act accordingly:
        case 1:
            managers = ManagerRegister(managers, size);
            //no "break" means continue to login in case 2
        case 2:
            index = ManagerLogin(managers, size);
            if (index != -1)
                ManagerLoop(profit, managers[index]);
            break;
        case 3:
            ManagerEntranceRun = 0; //we want to stop running.
            printf("The system closed successfully\n");
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
    return managers;
}

//A function that print the menu to screen.
void printManagerEntranceOptions()
{
    printf("                              MNAGER MENU:\nPlease choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- Regiter\n");
    printf("2- Log in\n");
    printf("3- Exit\n");
    printf("----------------------------------------------------------------------\n");
}//end method printOptions()

Client* ClientEntranceLoop(Client* clients, int* size)
{
    int ClientEntranceRun = 1;//do we want another iteration?
    int option;//the choosen option for the menu.
    int index;
    Client c;
    while (ClientEntranceRun)
    {  //while we still want to run:
        printClientEntranceOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option)
        {//act accordingly:
        case 1:
            clients = ClientRegister(clients, size);
            //no "break" means continue to login in case 2
        case 2:
            index = ClientLogin(clients, size);
            if (index != -1)
                ClientLoop(clients[index]);
            break;
        case 3:
            ClientEntranceRun = 0; //we want to stop running.
            printf("The system closed successfully\n");
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
    return clients;
}

//A function that print the menu to screen.
void printClientEntranceOptions()
{
    printf("                              COSTUMER MENU:\nPlease choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- Regiter\n");
    printf("2- Log in\n");
    printf("3- Exit\n");
    printf("----------------------------------------------------------------------\n");
}//end method printOptions()

void ManagerLoop(float* profit, Manager m)
{
    Product* products = NULL;
    orders* Orders = NULL;
    Client* clients = NULL;
    int products_size = 0, Orders_size = 0, sn, tr = 0, rcount = 0, clients_size = 0;
    int ManagerRun = 1;//do we want another iteration?
    int option;//the choosen option for the menu.
    products = Get_All_Data(products, &products_size);
    clients = get_All_Data_Client(clients, &clients_size);
    Orders = Get_All_Waiting_Orders(Orders, &Orders_size);
    while (ManagerRun)
    {  //while we still want to run:
        printManagerOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option) {//act accordingly:
        case 1:
            products = ActionsOnProducts(products, &products_size);

            break;//end of this iteration
        case 2:
            Searches(products, products_size);
            break;
        case 3:
            printf("Enter serial number: ");
            scanf("%d", &sn);
            Update_Price(products, products_size, sn);
            break;
        case 4:
            ViewAllOrders();
            break;
        case 5:
            printf("Enter serial number: ");
            scanf("%d", &sn);
            (*profit) += ChangeStatus(Orders, &Orders_size, products, products_size, sn);
            break;
        case 6:
            Get_Rating_vars(&tr, &rcount);
            Print_Rating(tr, rcount);
            Set_Rating_vars(tr, rcount);
            break;
        case 7:
            ActionsOnClient(clients, clients_size);
            break;
        case 8:
            printf("Enter serial number: ");
            scanf("%d", &sn);
            Discount_Product(products, products_size, sn);
            break;
        case 9:
            PrintfProfit(profit);
            break;
        case 10:
            Print_All_Products(products, products_size);
            Print_Products_Out_Of_Stock(products, products_size);
            break;
        case 11:
            ManagerRun = 0; //we want to stop running.
            printf("Goodbye!\n");//tell the user goodbye.
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
    set_All_Data(products, products_size);
    set_All_Data_Client(clients, clients_size);
    Set_All_Waiting_Orders(Orders, Orders_size);
}

//A function that print the menu to screen.
void printManagerOptions()
{
    printf("Please choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- Actions on a product\n");
    printf("2- Search product\n");
    printf("3- change price\n");
    printf("4- View orders\n");
    printf("5- Change order status\n");
    printf("6- Watch average site rating\n");
    printf("7- Actions on client\n");
    printf("8- Sales\n");
    printf("9- Daily profit\n");
    printf("10- Inventory status\n");
    printf("11- Logout\n");
    printf("----------------------------------------------------------------------\n");
}//end method printManagerOptions()

void ClientLoop(Client c)
{
    Product* products = NULL;
    ProductFile* pf = NULL;
    orders* Orders = NULL;
    Cart cart;
    cart.sn = NULL;
    cart.amount = NULL;
    cart.tp = 0.0;
    int products_size = 0, Orders_size = 0, cart_size = 0, sn, quantity, tr, rcount, flag = 1;
    int ClientRun = 1, option;
    char name[50];
    products = Get_All_Data(products, &products_size);
    Orders = Get_All_Waiting_Orders(Orders, &Orders_size);

    while (ClientRun)
    {//while we still want to run:
        printClientOptions();//print the menu
        scanf("%d", &option);//get the user choise
        switch (option)
        {//act accordingly:
        case 1:
            ViewPersonalOrders(c.id);
            //activate the functions that resposible for it
            break;//end of this iteration
        case 2:
            Select_cat(products, products_size);
            break;
        case 3:
            Low_to_high(products, products_size);
            break;
        case 4:
            printf("Enter name of product: ");
            getchar();
            gets(name);
            Name_search(products, products_size, name);
            break;
        case 5:
            Get_Rating_vars(&tr, &rcount);
            Print_Rating(tr, rcount);
            Set_Rating_vars(tr, rcount);
            break;
        case 6:
            printf("Enter serial number of product: ");
            scanf("%d", &sn);
            printf("Enter quantity: ");
            scanf("%d", &quantity);

            cart = Add_To_Cart(products, products_size, cart, &cart_size, sn, quantity);
            break;
        case 7:
            flag = 1;
            while (flag) {
                if (cart_size)
                    View_cart(products, products_size, cart, cart_size, c);
                else
                {
                    printf("Your cart is empty\n");
                    flag = 0;
                    break;
                }
                printCartMenu();
                scanf("%d", &option);
                if (option == 1)
                {
                    printf("Enter serial number of product you want to remove from cart: ");
                    scanf("%d", &sn);
                    cart = Remove_From_Cart(cart, &cart_size, sn);
                    printf("Your updated cart is:\n");
                    View_cart(products, products_size, cart, cart_size, c);
                    flag = 0;
                }
                else if (option == 2)
                {
                    float deliveryCost;
                  
                    if (c.clubMember == 'y')
                        cart.tp *= 0.9;//10% discount
                    deliveryCost = ShippingDetails();
                    cart.tp += deliveryCost;//delivery not include in the club members discount (external company)
                    pf = Checkout(products, products_size, cart, cart_size);
                    Orders = Add_Order(Orders, &Orders_size, MakeOrder(pf, cart_size, Get_New_Order_SN(), c.name, c.id, 'w', cart.tp));
                    printf("Total price is: %.2f", cart.tp);
                    printf("Your order is waiting for manager approve\n");
                    pf = NULL;
                    cart.sn = NULL;
                    cart.amount = NULL;
                    cart.tp = 0.0;
                    cart_size = 0;
                    flag = 0;
                }
                else if (option == 3)
                    flag = 0;
                else
                    printf("Wrong number, please try again\n");
            }
            break;
        case 8:
            Get_Rating_vars(&tr, &rcount);
            Website_ranking(&tr, &rcount);
            Set_Rating_vars(tr, rcount);
            break;
        case 9: ClientRun = 0; //we want to stop running.
            printf("Goodbye!\n");//tell the user goodbye.
            break;
        default: printf("Wrong option. Please try again!\n"); //not a supported option
        }//end switch

    }//end while(run)
    set_All_Data(products, products_size);
    Set_All_Waiting_Orders(Orders, Orders_size);
}

void printCartMenu()
{
    printf("1- Remove product\n");
    printf("2- Buy cart\n");//ask for delivery
    printf("3- Back\n");

}

Product* ActionsOnProducts(Product* list, int* size)
{
    int index, flag = 1, option;
    int sn;
    while (flag)
    {
        printf("Please choose one of the following options:\n Press\n");
        printf("----------------------------------------------------------------------\n");
        printf("1- Add a product\n");
        printf("2- Search product\n");
        printf("3- change price\n");
        printf("4- back\n");
        scanf("%d", &option);
        switch (option)
        {
        case 1:
            list = Add_Product(list, size, New_Product());
            break;
        case 2:
            printf("Enter serial number of product: ");
            scanf("%d", &sn);
            list = Remove_Product(list, size, sn);
            break;
        case 3:
            printf("Enter serial number of product: ");
            scanf("%d", &sn);
            Update_Quantity(list, size, sn);
            break;
        case 4:
            flag = 0;
            break;
        default:
            printf("Wrong option. Please try again!\n");
        }

    }
    return list;
}

//A function that print the menu to screen.
void printClientOptions()
{
    printf("Please choose one of the following options:\n Press\n");
    printf("----------------------------------------------------------------------\n");
    printf("1- View order history\n");
    printf("2- Find products by categories\n");
    printf("3- Watch products by increasing price\n");
    printf("4- Search product by name\n");
    printf("5- Watch average site rating\n");
    printf("6- Add product to the cart\n");
    printf("7- Watch current cart\n");
    printf("8- Rate the site\n");
    printf("9- Logout\n");
    printf("----------------------------------------------------------------------\n");
}

void Searches(Product* products, int size)
{
    int sn, option, flag = 1;
    char name[50];

    do {
        printf("1- Search product by name\n2- Search product by serial number\n");
        scanf("%d", &option);
        if (option == 1)
        {
            printf("Enter name of product: ");
            getchar();
            gets(name);
            if ((Name_search(products, size, name)) == 0)
            {
                printf("this product does not exist.");
                break;
            }
            flag = 0;
        }
        else if (option == 2)
        {
            printf("Enter serial number of product: ");
            scanf("%d", &sn);
            if (Serial_num_search(products, size, sn) == 0)
            {
                printf("this serial number does not exist.");
                break;
            }
            flag = 0;
        }
        else
            printf("Wrong number, please try again.\n");
    } while (flag);
}

void Get_Rating_vars(int* tr, int* rcount)
{
    FILE* fr;
    char line[500];
    char* sp;

    fr = fopen("Rating_Vars.csv", "r");//open file for reading
    if (fr == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    while (fgets(line, 500, fr) != NULL)
    {
        sp = strtok(line, ",");
        (*tr) = atoi(sp);
        sp = strtok(NULL, ",");
        (*rcount) = atoi(sp);
    }
    fclose(fr);//close file
}

void Set_Rating_vars(int tr, int rcount)
{
    FILE* fw;

    fw = fopen("Rating_Vars.csv", "w");//open file for writing
    if (fw == NULL)
    {
        printf("Error!! file can't be opened\n");
        exit(1);
    }
    fprintf(fw, "%d,%d\n", tr, rcount);

    fclose(fw);//close file
}






