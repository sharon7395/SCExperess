#include "Product.h"
#include "Orders.h"

//creating empty product (used in some cases as an error object)
Product Empty_Product()
{
	Product p;
	p.name = (char*)malloc(6 * sizeof(char));
	p.name = "empty";
	p.quantity = 0;
	p.price = 0.0;
	p.discount = 0;
	return p;
}

//get all products data from "Products.csv" file
Product* Get_All_Data(Product* list, int* size)
{
	FILE* fr;
	char line[500];
	char* sp, * name, * category;
	int sn, quantity, Discount;
	float price;

	fr = fopen("Products.csv", "r");//open file for reading
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
		category = (char*)malloc((strlen(sp) + 1) * sizeof(char));
		if (category == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		strcpy(category, sp);
		sp = strtok(NULL, ",");
		sn = atoi(sp);
		sp = strtok(NULL, ",");
		quantity = atoi(sp);
		sp = strtok(NULL, ",");
		price = atof(sp);
		sp = strtok(NULL, ",");
		Discount = atoi(sp);
		list = Add_Product(list, size, Create_Product(name, category, sn, quantity, price, Discount));//adding to list
	}
	fclose(fr);//close file
	return list;
}

//set all products data in "Products.csv" file
void set_All_Data(Product* list, int size)
{
	FILE* fw;

	fw = fopen("Products.csv", "w");//open file for writing
	if (fw == NULL)
	{
		printf("Error!! file can't be opened\n");
		exit(1);
	}
	for (int i = 0; i < size; i++)
		fprintf(fw, "%s,%s,%d,%d,%f,%d\n", list[i].name, list[i].category, list[i].sn, list[i].quantity, list[i].price, list[i].discount);
	fclose(fw);//close file
}

//get the next serial number
int Get_New_Product_SN()
{
	FILE* fr, * fw;
	char line[50];
	char* sp;
	int sn;


	fr = fopen("Next_Product_SN.csv", "r");//open file for reading
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
	fw = fopen("Next_Product_SN.csv", "w");//open file for writing
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

////////////ACTION ON PRODUCTS////////////

//creating new product
Product New_Product()
{
	Product p;
	char str[100];
	int temp;
	//get name
	printf("Enter name of product: ");
	getchar();
	gets(str);
	p.name = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (p.name == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	strcpy(p.name, str);

	//get category
	printf("Enter category of product: ");
	gets(str);
	p.category = (char*)malloc((strlen(str) + 1) * sizeof(char));
	if (p.category == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	strcpy(p.category, str);

	//get quantity
	printf("Enter quantity: ");
	scanf("%d", &(p.quantity));

	//get price
	printf("Enter price: ");
	scanf("%f", &(p.price));

	//get discount (0%-99%)
	printf("If you don't want to put this product in a discount enter 0 ,\n");
	printf("If you want to put this product in a discount enter the precentage of discount : ");
	scanf("%d", &(p.discount));

	//if product's details are legal
	if ((p.name != NULL) && (p.quantity >= 0) && (p.price >= 0.0) && (p.discount >= 0) && (p.discount < 100))
	{
		p.sn = Get_New_Product_SN();
		return p;
	}
	else//if product's details are illegal
	{
		printf("One of your following details are invalid.\n");
		return Empty_Product();
	}
}

//create and return product object
Product Create_Product(char* name, char* category, int sn, int quantity, float price, int Discount)
{
	Product p;
	p.name = (char*)malloc((strlen(name) + 1) * sizeof(char));
	if (p.name == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	strcpy(p.name, name);
	p.category = (char*)malloc((strlen(category) + 1) * sizeof(char));
	if (p.category == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	strcpy(p.category, category);
	p.sn = sn;
	p.quantity = quantity;
	p.price = price;
	p.discount = Discount;
	return p;
}

//add a new product to the list
Product* Add_Product(Product* list, int* size, Product p)
{
	Product* newlist = NULL;
	if (p.name == "empty")//product is illegal
	{
		printf("Error! Product can't be added.\n");
		return list;
	}
	else//product is legal
	{
		newlist = (Product*)malloc((*size + 1) * sizeof(Product));
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
			newlist[i].category = (char*)malloc((strlen(list[i].category) + 1) * sizeof(char));
			if (newlist[i].category == NULL)
			{
				printf("Allocate memory failed.\n");
				exit(1);
			}
			strcpy(newlist[i].category, list[i].category);
			newlist[i].discount = list[i].discount;
			newlist[i].price = list[i].price;
			newlist[i].quantity = list[i].quantity;
			newlist[i].sn = list[i].sn;
		}

		//add new product
		newlist[*size].name = (char*)malloc((strlen(p.name) + 1) * sizeof(char));
		if (newlist[*size].name == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		strcpy(newlist[*size].name, p.name);
		newlist[*size].category = (char*)malloc((strlen(p.category) + 1) * sizeof(char));
		if (newlist[*size].category == NULL)
		{
			printf("Allocate memory failed.\n");
			exit(1);
		}
		strcpy(newlist[*size].category, p.category);
		newlist[*size].discount = p.discount;
		newlist[*size].price = p.price;
		newlist[*size].quantity = p.quantity;
		newlist[*size].sn = p.sn;
		(*size)++;
		//delete old list
		for (int i = 0; i < *size - 1; i++)
		{
			free(list[i].name);
			free(list[i].category);
		}
		free(list);
		return newlist;
	}
}

//add a new product to the list
Product* Remove_Product(Product* list, int* size, int sn)
{
	Product* newlist = NULL;
	int flag = FALSE;
	int index = 0;

	for (int i = 0; i < *size; i++)
		if (list[i].sn == sn)//if product found
		{
			index = i;
			i = *size;
			flag = TRUE;
		}
	if (!flag)//product not found
	{
		printf("Product not found.\n");
		return list;
	}
	else//product found
	{
		newlist = (Product*)malloc((*size - 1) * sizeof(Product));
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
				newlist[i].name = (char*)malloc((strlen(list[*size - 1].name) + 1) * sizeof(char));
				if (newlist[i].name == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].name, list[*size - 1].name);
				newlist[i].category = (char*)malloc((strlen(list[*size - 1].category) + 1) * sizeof(char));
				if (newlist[i].category == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].category, list[*size - 1].category);
				newlist[i].discount = list[*size - 1].discount;
				newlist[i].price = list[*size - 1].price;
				newlist[i].quantity = list[*size - 1].quantity;
				newlist[i].sn = list[*size - 1].sn;
			}
			else//coppy product from old list
			{
				newlist[i].name = (char*)malloc((strlen(list[i].name) + 1) * sizeof(char));
				if (newlist[i].name == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].category, list[i].category);
				newlist[i].category = (char*)malloc((strlen(list[i].category) + 1) * sizeof(char));
				if (newlist[i].category == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				strcpy(newlist[i].category, list[i].category);
				newlist[i].discount = list[i].discount;
				newlist[i].price = list[i].price;
				newlist[i].quantity = list[i].quantity;
				newlist[i].sn = list[i].sn;
			}
		}
		(*size)--;
		//delete old list
		for (int i = 0; i < *size + 1; i++)
		{
			free(list[i].name);
			free(list[i].category);
		}
		free(list);
		return newlist;
	}
}

//return TRUE if product is exist, FALSE if not
int Get_Index_Of_Product(Product* list, int size, int sn)
{
	for (int i = 0; i < size; i++)
		if (list[i].sn == sn)//if product found
			return i;
	return -1;
}

//return calculated price after discount
float Get_Price(Product p)
{
	return (p.price - (p.price * (p.discount / 100.0)));
}

//updating price of product if he is exist
void Update_Price(Product* list, int size, int sn)
{
	float new_price;
	int index = Get_Index_Of_Product(list, size, sn);
	if (index == -1)//Product not found
		printf("Product not found.\n");
	else//Product found
	{
		printf("The current price is: %f\nEnter updated price: ", list[index].price);
		scanf("%f", &new_price);
		if (new_price >= 0)//valid price
		{
			list[index].price = new_price;
			printf("The new price is: %f\n", Get_Price(list[index]));
		}
		else//invalid price
			printf("Invalid price, price not changed.\n");
	}
}

//updating quantity of product if he is exist
void Update_Quantity(Product* list, int size, int sn)
{
	int new_quantity;
	int index = Get_Index_Of_Product(list, size, sn);
	if (index == ERROR)//Product not found
		printf("Product not found.\n");
	else//Product found
	{
		printf("The current quantity is: %d\nEnter new quantity: ", list[index].quantity);
		scanf("%d", &new_quantity);
		if (new_quantity >= 0)//valid quantity
		{
			list[index].quantity = new_quantity;
			printf("The new quantity is: %d\n", list[index].quantity);
		}
		else//invalid quantity
			printf("Invalid quantity, quantity not changed.\n");
	}
}

//print all details of a product
void Print_Product(const Product p)
{
	printf("Name: %s\nCategory: %s\nSerial number: %d\nQuantity: %d\n", p.name, p.category, p.sn, p.quantity);
	printf("Price: %.2f\n", Get_Price(p));
}

//apply a discount to product
void Discount_Product(Product* list, int size, int sn)
{
	int discount_precentage;
	int index = Get_Index_Of_Product(list, size, sn);
	if (index == ERROR)//Product not found
		printf("Product not found.\n");
	else//Product found
	{
		printf("Enter the precentage of discount you want to apply on this product:\n");
		printf("For example: if you want to apply 40 % of discount, enter 40 \n");
		printf("If you want to disable the discount enter 0 which means 0 % discount\n");
		scanf("%d", &discount_precentage);
		if ((discount_precentage > 0) && (discount_precentage < 100))
		{
			list[index].discount = discount_precentage;
			printf("The updated price is: %f\n", Get_Price(list[index]));
		}
		else if (discount_precentage == 0)
		{
			list[index].price = (list[index].price) / (1 - ((list[index].price) / 100.0));
			list[index].discount = 0;
		}
		else
			printf("Invalid discount precentage, discount not changed.\n");
	}
}

//print all products
void Print_All_Products(Product* list, int size)
{
	for (int i = 0; i < size; i++)
	{
		Print_Product(list[i]);
		printf("\n");
	}
}

//print all the products are out of stock
void Print_Products_Out_Of_Stock(Product* list, int size)
{
	for (int i = 0; i < size; i++)
		if (!list[i].quantity)//if quantity is 0
			Print_Product(list[i]);
}