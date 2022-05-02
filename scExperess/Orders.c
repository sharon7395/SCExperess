#include "Orders.h"



/* REMEMBER: free all the allocate memory in the main */


//Manager's view of all the orders
//flag initialized to 0 at first, to check if there is any history at all


//The function bascilly adding one order at the time 
//Flag for poting that if this is the first user or not
//The *ptr for pointing at the location of the user order 
//pSer is initialized at digit 10000, to make a following serial number
//username is the name of the customer
//id is the id number of the customer
orders MakeOrder(ProductFile* listPro, int sizep, int orderSN, char* username, int id, char status, float tp)
{
	orders order;
	order.username = (char*)malloc((strlen(username) + 1) * sizeof(char));
	if (order.username == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	strcpy(order.username, username);
	order.id = id;
	order.size = sizep;
	order.items = listPro;
	order.serial = orderSN;
	order.status = status;
	order.tp = tp;

	return order;
}

orders* Get_All_Waiting_Orders(orders* list, int* size)
{
	FILE* fr;
	ProductFile* plist;
	char line[500];
	char* sp, * username, * name;
	int Osn, sn2, amount, id, size1 = 0;
	char status;
	float price, tp;
	fr = fopen("WaitingOrders.csv", "r");//open file for reading
	if (fr == NULL)
	{
		printf("Error!! file can't be opened\n");
		exit(1);
	}
	while (fgets(line, 500, fr) != NULL)
	{
		sp = strtok(line, ",");
		username = (char*)malloc((strlen(sp) + 1) * sizeof(char));
		if (username == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		strcpy(username, sp);
		sp = strtok(NULL, ",");
		id = atoi(sp);
		sp = strtok(NULL, ",");
		Osn = atoi(sp);
		sp = strtok(NULL, ",");
		status = sp[0];
		sp = strtok(NULL, ",");
		size1 = atoi(sp);
		sp = strtok(NULL, ",");
		tp = atof(sp);
		plist = (ProductFile*)malloc(size1 * sizeof(ProductFile));
		if (plist == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		for (int i = 0; i < size1; i++)//init plist
		{
			plist[i].name = (char*)malloc((strlen(sp) + 1) * sizeof(char));
			if (plist[i].name == NULL)
			{
				printf("Allocate memory failed.\n");
				exit(1);
			}
			sp = strtok(NULL, ",");
			strcpy(plist[i].name, sp);
			sp = strtok(NULL, ",");
			sn2 = atoi(sp);
			sp = strtok(NULL, ",");
			amount = atoi(sp);
			sp = strtok(NULL, ",");
			price = atof(sp);
			plist[i].amount = amount;
			plist[i].price = price;
			plist[i].sn = sn2;
		}
		list = Add_Order(list, size, MakeOrder(plist, size1, Osn, username, id, status, tp));
	}
	fclose(fr);//close file
	return list;
}

orders* Set_All_Waiting_Orders(orders* list, int size)
{
	FILE* fw;

	fw = fopen("WaitingOrders.csv", "w");//open file for writing
	if (fw == NULL)
	{
		printf("Error!! file can't be opened\n");
		exit(1);
	}
	for (int i = 0; i < size; i++)
	{
		fprintf(fw, "%s,%d,%d,%c,%d,%f,", list[i].username, list[i].id, list[i].serial, list[i].status, list[i].size, list[i].tp);
		for (int j = 0; j < list[i].size; j++)//write items list
		{
			fprintf(fw, "%s,%d,%d,%f,", list[i].items->name, list[i].items->sn, list[i].items->amount, list[i].items->price);
		}
	}
	fclose(fw);//close file
}

orders* Add_Order(orders* list, int* size, orders order)
{
	orders* newlist;
	newlist = (orders*)malloc((*size + 1) * sizeof(orders));
	if (newlist == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	//copy old list
	for (int i = 0; i < *size; i++)
	{
		newlist[i].username = (char*)malloc((strlen(list[i].username) + 1) * sizeof(char));
		if (newlist[i].username == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		strcpy(newlist[i].username, list[i].username);
		newlist[i].id = list[i].id;
		newlist[i].items = list[i].items;
		newlist[i].serial = list[i].serial;
		newlist[i].status = list[i].status;
		newlist[i].size = list[i].size;
		newlist[i].tp = list[i].tp;
	}
	newlist[*size].username = order.username;
	newlist[*size].id = order.id;
	newlist[*size].items = order.items;
	newlist[*size].serial = order.serial;
	newlist[*size].status = order.status;
	newlist[*size].size = order.size;
	newlist[*size].tp = order.tp;
	(*size)++;

	free(list);

	return newlist;
}

orders* Remove_Order(orders* list, int* size, int orderSN)
{
	orders* newlist = NULL;
	int flag = FALSE;
	int index = 0;

	for (int i = 0; i < *size; i++)
		if (list[i].serial == orderSN)//if order found
		{
			index = i;
			i = *size;
			flag = TRUE;
		}
	if (!flag)//order not found
	{
		printf("Order not found.\n");
		return list;
	}
	else//order found
	{
		newlist = (orders*)malloc((*size - 1) * sizeof(orders));
		if (newlist == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		//copy old list
		for (int i = 0; i < *size - 1; i++)
		{
			if (i == index)//taking last product into the index of the removed product
			{
				newlist[i].username = (char*)malloc((strlen(list[*size - 1].username) + 1) * sizeof(char));
				if (newlist[i].username == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].username, list[*size - 1].username);
				newlist[i].id = list[*size - 1].id;
				newlist[i].serial = list[*size - 1].serial;
				newlist[i].status = list[*size - 1].status;
				newlist[i].size = list[*size - 1].size;
				newlist[i].items = list[*size - 1].items;
			}
			else//coppy product from old list
			{
				newlist[i].username = (char*)malloc((strlen(list[i].username) + 1) * sizeof(char));
				if (newlist[i].username == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].username, list[i].username);
				newlist[i].id = list[i].id;
				newlist[i].serial = list[i].serial;
				newlist[i].status = list[i].status;
				newlist[i].size = list[i].size;
				newlist[i].items = list[i].items;
			}
		}
		(*size)--;
		//delete old list
		for (int i = 0; i < *size + 1; i++)
			free(list[i].username);
		free(list);
		return newlist;
	}
}

//pTotalPrice initialized to 0 at first, to start with 0 profit
int DailyProfit(float* pTotalPrice, float tp)
{
	*pTotalPrice += tp;
	return *pTotalPrice;
}

void PrintfProfit(int* pTotalPrice)
{
	printf("The total profit of the day is: %d\n", *pTotalPrice);

}

float ChangeStatus(orders* Allorders, int* size, Product* plist, int psize, int sn)
{
	int i, flag = 1, option;
	float tp = 0;
	//char YN;//Yes and No to approve or cancel
	//puts("Please enter the customer's id: ");
	//getchar();
	for (i = 0; i < *size; i++)
	{
		if (Allorders[i].serial == sn)
		{
			do {
				printf("Please choose one of the following options:\n Press\n");
				printf("1- Approve the order\n");
				printf("2- Cancel the order\n");
				printf("3- Back\n");
				scanf("%d", &option);


				if (option == 1)
				{
					Allorders[i].status = 'Y';
					tp = Allorders[i].tp;
					flag = 0;
				}
				else if (option == 2)
				{
					Allorders[i].status = 'N';
					UpdateStock(plist, psize, Allorders[i]);
					tp = 0;
					flag = 0;
				}
				else if (option == 3)
				{
					flag = 0;
				}
				else
					printf("wrong input, please try again\n");
			} while (flag);
			orderHistory(Allorders[i]);

			Allorders = Remove_Order(Allorders, size, sn);
			i = *size;//exit the loop
		}
	}
	if (flag)
		printf("Order can not be found\n");
	return tp;
}

//status should get if the order is approved or not 
//order shloud get the array of the structure
//items is the number of the items that in the cart
//pTotalPrice initialized to 0 at first, to start with 0 profit
/*----> The user's orders history*/
//sn is the serial number of the order 
//sn is the serial number of the order 
void orderHistory(orders o)
{
	FILE* personalHistory;
	FILE* ManagerHistory;
	char filename[50];
	int i;
	sprintf(filename, "%d.txt", o.id);
	personalHistory = fopen(filename, "a");
	if (!personalHistory)
	{
		puts("Open file have failed");
		exit(1);
	}
	ManagerHistory = fopen("HistoryOfAllOrders.txt", "a");
	if (!(ManagerHistory))
	{
		puts("Open file have failed");
		exit(1);
	}
	{//print into personal history
		fprintf(personalHistory, "ORDER NUMBER:  %d\n", o.serial);
		fprintf(personalHistory, "Client's name:  %s\n", o.username);
		fprintf(personalHistory, "Client's ID:  %d\n", o.id);
		if (o.status == 'Y')
			fprintf(personalHistory, "Order status: Approved\n");
		else //if (o.status == 'N')
			fprintf(personalHistory, "Order status: Denied\n");
		fprintf(personalHistory, "Serial number - Product - Amount - Price\n");
		for (i = 0; i < o.size; i++)
		{
			fprintf(personalHistory, "%d - %s - %d - %.2f\n", o.items->sn, o.items->name, o.items->amount, o.items->price);
		}
		fprintf(personalHistory, "Total:  %.2f\n\n", o.tp);
	}
	{//print into manager history
		fprintf(ManagerHistory, "ORDER NUMBER:  %d\n", o.serial);
		fprintf(ManagerHistory, "Client's name:  %s\n", o.username);
		fprintf(ManagerHistory, "Client's ID:  %d\n", o.id);
		if (o.status == 'Y')
			fprintf(ManagerHistory, "Order status: Approved\n");
		else //if (o.status == 'N')
			fprintf(ManagerHistory, "Order status: Denied\n");
		fprintf(ManagerHistory, "Serial number - Product - Amount - Price\n");
		for (i = 0; i < o.size; i++)
		{
			fprintf(ManagerHistory, "%d - %s - %d - %.2f\n", o.items->sn, o.items->name, o.items->amount, o.items->price);
		}
		fprintf(ManagerHistory, "Total:  %.2f\n\n", o.tp);
	}
	fclose(personalHistory);
	fclose(ManagerHistory);
}

void ViewAllOrders()
{
	FILE* fp;
	char temp = { 0 };
	fp = fopen("HistoryOfAllOrders.txt", "r");
	if (!fp)
	{
		puts("Can't open file");
		exit(1);
	}
	temp = fgetc(fp);
	if (temp == EOF)
		printf("There is no history.\n");
	else
	{
		printf("%c", temp);
		while (temp != EOF)
		{
			temp = fgetc(fp);
			printf("%c", temp);
		}
	}
	fclose(fp);
}

void UpdateStock(Product* plist, int psize, orders o)
{
	for (int i = 0; i < o.size; i++)
		for (int j = 0; j < psize; j++)
		{
			if (o.items[i].sn == plist[j].sn)
			{
				plist[j].quantity += o.items[i].amount;
				j = psize;//jump to the next product
			}
		}
}

void ViewPersonalOrders(int id)
{
	FILE* fp;
	char temp = { 0 };
	char filename[50];
	sprintf(filename, "%d.txt", id);
	fp = fopen(filename, "r");
	if (!fp)
	{
		puts("Can't open file");
		exit(1);
	}
	temp = fgetc(fp);
	if (temp == EOF)
		printf("There is no history.\n");
	else
	{
		printf("%c", temp);
		while (temp != EOF)
		{
			temp = fgetc(fp);
			printf("%c", temp);
		}
	}
	fclose(fp);
}
//void PendingOrders(orders* List)
//{
//	FILE* fp;
//	fp = fopen("PendingOrders.csv", "a");
//	if (!(fp))
//	{
//		puts("Can't open file");
//		exit(1);
//	}
//
//	fprintf(fp, "Name:,ID:,Serial:,Status:\n");
//	fprintf(fp, "%s,%d,%d,%c\n", List->username, List->id, List->ser, List->status);
//
//	fclose(fp);
//}

int Get_New_Order_SN()
{
	FILE* fr, * fw;
	char line[50];
	char* sp;
	int sn;


	fr = fopen("Next_Order_SN.csv", "r");//open file for reading
	if (fr == NULL)
	{
		printf("Error!! file can't be opened\n");
		exit(1);
	}
	fgets(line, 50, fr);
	sp = strtok(line, ",");
	sn = atoi(sp);
	sn++;
	fclose(fr);//close file (stop reading)
	fw = fopen("Next_Order_SN.csv", "w");//open file for writing
	if (fw == NULL)
	{
		printf("Error!! file can't be opened\n");
		exit(1);
	}
	fprintf(fw, "%d", sn);
	fclose(fw);//close file (stop writing)
	sn--;
	return sn;
}
