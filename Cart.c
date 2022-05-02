#include "Cart.h"

//adding product's details to cart
Cart Add_To_Cart(Product* plist, int slist, Cart clist, int* scart, int sn, int quantity)
{
	for (int i = 0; i < slist; i++)
	{
		if (sn == plist[i].sn)
		{
			if ((quantity > 0) && (quantity <= plist[i].quantity))//add product
			{
				for (int j = 0; j < *scart; j++)//if product already in cart
				{
					if (sn == clist.sn[j])
					{
						clist.amount[j] += quantity;
						clist.tp += quantity * Get_Price(plist[i]);
						return clist;
					}
				}
				(*scart)++;
				int* newSN, * newAmount;
				newSN = (int*)malloc((*scart) * sizeof(int));
				if (newSN == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				newAmount = (int*)malloc((*scart) * sizeof(int));
				if (newAmount == NULL)
				{
					printf("Allocate memory failed.\n");
					exit(1);
				}
				//copy old list
				for (int i = 0; i < *scart - 1; i++)
				{
					newSN[i] = clist.sn[i];
					newAmount[i] = clist.amount[i];
				}
				//add new product's details
				newSN[*scart - 1] = sn;
				newAmount[*scart - 1] = quantity;
				free(clist.sn);
				free(clist.amount);
				clist.sn = newSN;
				clist.amount = newAmount;
				clist.tp += Get_Price(plist[i]) * quantity;
				printf("%d of the product: %s, added to your cart\n", quantity, plist[i].name);
				return clist;
			}
			else
			{
				printf("Error! illegal quantity.\n");
				return clist;
			}
		}
	}
	printf("Error! product can't be found.\n");
	return clist;
}

//printing current cart as "serial number" - "product name" - "amount" - "price(amount * product's price)"
void View_cart(Product* plist, int slist, Cart clist, int scart, Client c)
{
	int index;
	if (!scart)//scart = 0
		printf("Cart is empty.\n");
	else
	{
		printf("serial number - product - amount - price\n");
		for (int i = 0; i < scart; i++)
		{
			index = Get_Index_Of_Product(plist, slist, clist.sn[i]);
			if (index != ERROR)
				printf("%d - %s - %d - %.2f\n", clist.sn[i], plist[index].name, clist.amount[i], (clist.amount[i] * Get_Price(plist[index])));//print details
		}
		if (c.clubMember == 'y')
			printf("Total price: %.2f\n", clist.tp * 0.9);
		else
			printf("Total price: %.2f\n", clist.tp);
	}
	printf("\n");
}

double ShippingDetails()
{
	int state;
	while (TRUE) {
		printf("Choose your state:\n1-North\n2-Central\n3-South\n");
		scanf("%d", &state);
		if (state == 1)
			return NORTH;
		else if (state == 2)
			return CENTRAL;
		else if (state == 3)
			return SOUTH;
		else
			printf("Wrong number, please try again\n");
	}
}

//remove product from cart by serial number
Cart Remove_From_Cart(Cart clist, int* scart, int sn, Product* plist, int psize)
{
	int* newSN, * newAmount;
	int flag = 1;
	for (int i = 0; i < *scart; i++)
	{
		if (sn == clist.sn[i])
		{
			flag = 0;
			i = *scart;
		}
	}
	if (flag)
	{
		printf("Product not found in the cart\n");
		return clist;
	}

	(*scart)--;
	if (!*scart)
	{
		clist.sn = NULL;
		clist.amount = NULL;
		clist.tp = 0;
		return clist;
	}
	newSN = (int*)malloc((*scart) * sizeof(int));
	if (newSN == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	newAmount = (int*)malloc((*scart) * sizeof(int));
	if (newAmount == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	//copy old list(except the serial number we need to remove)
	for (int i = 0; i < *scart + 1; i++)
	{
		if (sn == clist.sn[i])
		{
			//update tp
			for (int j = 0; j < psize; j++)
			{
				if (sn == plist[j].sn)
					clist.tp -= (Get_Price(plist[j]) * clist.amount[i]); //adding product list to this func and updated tp after removing product
			}
			newSN[i] = clist.sn[*scart];
			newAmount[i] = clist.amount[*scart];
		}
		else
		{
			newSN[i] = clist.sn[i];
			newAmount[i] = clist.amount[i];
		}
	}
	//free memory
	free(clist.sn);
	free(clist.amount);
	clist.sn = newSN;
	clist.amount = newAmount;
	return clist;
}

//calculating delivery price
Cart Calculate_Delivery(Cart clist)
{
	int delivery, delFLAG = 1;
	while (delFLAG)
	{
		printf("1 - North (%lf nis)\n2 - Central (%lf nis)\n3 - South (%lf nis)\n4 - Back\n", NORTH, CENTRAL, SOUTH);
		scanf("%d", &delivery);
		if (delivery == 1)
		{
			clist.tp += NORTH;
			delFLAG = 0;
		}
		else if (delivery == 2)
		{
			clist.tp += CENTRAL;
			delFLAG = 0;
		}
		else if (delivery == 3)
		{
			clist.tp += SOUTH;
			delFLAG = 0;
		}
		else if (delivery == 4)
		{
			delFLAG = 0;
		}
		else
			printf("Wrong number, try again.\n");
		return clist;
	}
}

//buying all products in cart - transporting the data into productFile array
ProductFile* Checkout(Product* plist, int slist, Cart clist, int scart)
{
	int index;
	ProductFile* newlist;
	newlist = (ProductFile*)malloc(scart * sizeof(ProductFile));
	if (newlist == NULL)
	{
		printf("Allocate memory failed.\n");
		exit(1);
	}
	for (int i = 0; i < scart; i++)
	{
		index = Get_Index_Of_Product(plist, slist, clist.sn[i]);
		if (index != ERROR)
		{
			newlist[i].name = (char*)malloc(strlen(plist[index].name + 1) * sizeof(char));
			if (newlist[i].name == NULL)
			{
				printf("Allocate memory failed.\n");
				exit(1);
			}
			strcpy(newlist[i].name, plist[index].name);
			newlist[i].sn = clist.sn[i];
			newlist[i].amount = clist.amount[i];
			newlist[i].price = (clist.amount[i] * Get_Price(plist[index]));
			plist[index].quantity -= clist.amount[i];//update stock
		}
	}
	return newlist;
}
