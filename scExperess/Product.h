#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define TRUE 1
#define FALSE 0
#define ERROR -1

typedef struct
{
	char* name;
	char* category;
	int sn;//serial number
	int quantity;
	float price;
	int discount;//representing the precentage of discount

} Product;

Product Empty_Product();//creating empty product (used in some cases as an error object)
Product* Get_All_Data(Product* list, int* size);//get all products data from "Products.csv" file
void set_All_Data(Product* list, int size);//set all products data in "Products.csv" file
int Get_New_Product_SN();//get the next serial number

////////////ACTION ON PRODUCTS////////////

Product New_Product();//creating new product
Product Create_Product(char* name, char* category, int sn, int quantity, float price, int Discount);//create and return product object
Product* Add_Product(Product* list, int* size, Product p);//add a new product to the list
Product* Remove_Product(Product* list, int* size, int sn);//remove a product from the list
int Get_Index_Of_Product(Product* list, int size, int sn);//return TRUE if product is exist, FALASE if not
float Get_Price(Product p);//return calculated price after discount
void Update_Price(Product* list, int size, int sn);//updating price of product if he is exist
void Update_Quantity(Product* list, int size, int sn);//updating quantity of product if he is exist
void Print_Product(const Product p);//print all details of a product
void Discount_Product(Product* list, int size, int sn);//apply a discount to product
void Print_All_Products(Product* list, int size);//print all products
void Print_Products_Out_Of_Stock(Product* list, int size);//print all the products are out of stock