#include "Product.h"

typedef struct
{
	char* name;
	int sn;
	int amount;
	float price;
}ProductFile;

typedef struct
{
	char* username;
	int id;
	int serial;
	char status;
	int size;
	float tp;
	ProductFile* items;

}orders;

orders* Get_All_Waiting_Orders(orders* list, int* size);
orders* Set_All_Waiting_Orders(orders* list, int size);
orders* Add_Order(orders* list, int* size, orders order);
orders* Remove_Order(orders* list, int* size, int orderSN);
int DailyProfit(float* pTotalPrice, float tp);
void PrintfProfit(int* pTotalPrice);
int Get_New_Order_SN();
orders MakeOrder(ProductFile* listPro, int sizep, int orderSN, char* username, int id, char status, float tp);
void ViewAllOrders();
void UpdateStock(Product* plist, int psize, orders o);
void ViewPersonalOrders(int id);
float ChangeStatus(orders* Allorders, int* size, Product* plist, int psize, int sn);
void orderHistory(orders o);
