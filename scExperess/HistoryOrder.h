


//status shloud get if the order is approved or not 
int main()
{
	ProductFile* order;
	int id;
	int items, i;
	int* ptr;
	ptr = 0;

	scanf("%d", &id);
	char name[50];
	char filechar = { 0 };
	puts("How many items?");
	scanf("%d", &items);
	order = (ProductFile*)malloc(items * sizeof(ProductFile));
	for (i = 0; i < items; i++)
	{
		getchar();
		gets(order[i].name);
		scanf("%d", &order[i].sn);
		scanf("%d", &order[i].amount);
		scanf("%f", &order[i].price);
	}

	orderHistory(id, order, items, &ptr);

	return 0;

}

