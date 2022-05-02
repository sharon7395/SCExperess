#include "Orders.h"
#include "Register.h"

#define NORTH 55.0
#define CENTRAL 30.0
#define SOUTH 15.0

typedef struct
{
	int* sn;
	int* amount;
	float tp;//total price
} Cart;


void View_cart(Product* plist, int slist, Cart clist, int scart, Client c);//printing current cart as "product name" - "amount" - "price(amount * product's price)"
float ShippingDetails();
Cart Add_To_Cart(Product* plist, int slist, Cart clist, int* scart, int sn, int quantity);//adding product's details to cart
Cart Remove_From_Cart(Cart clist, int* scart, int sn);//remove product from cart by serial number
Cart Calculate_Delivery(Cart clist);//calculating delivery price
ProductFile* Checkout(Product* plist, int slist, Cart clist, int scart);//buying all products in cart
