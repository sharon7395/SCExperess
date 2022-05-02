#include "SearchProduct.h"
#include <stdio.h>
#include <string.h>

int Name_search(Product* list, int size, char* name)
{
    int i, x = 0;
    if (name == NULL)
    {
        printf("EROR\n");
        return 0;
    }

    for (i = 0; i < size; i++)
    {
        if (strcmp(list[i].name, name) == 0)
        {
            x++;
            printf("\n");
            Print_Product(list[i]);
            printf("\n");
        }
    }
    if (x == 0)
        return 0;
    return 1;
}

int Serial_num_search(Product* list, int size, int num)
{
    int i;
    if (num == 0)
    {
        printf("EROR\n");
    }

    for (i = 0; i < size; i++)
    {
        if (list[i].sn == num)
        {
            printf("\n");
            Print_Product(list[i]);
            printf("\n");
            return 1;
        }
    }
    return 0;
}

//printing the average rating
void Print_Rating(int total_rate, int rating_count)
{
    float temp = ((float)total_rate / (float)rating_count);
    printf("The average rating of our site is: %.1f\n", temp);
}

void Website_ranking(int* total, int* count)
{
    int number;
    printf("Please enter a number from one to five");
    scanf("%d", &number);

    if (number > 0 && number <= 5)
    {
        (*total) += number;
        (*count)++;
    }
    else
    {
        printf("wrong number\n");
    }

}

void Low_to_high(Product* list, int size)
{
    int count;
    int* lth = (int*)malloc(size * sizeof(int));//lth means low to high

    for (int i = 0; i < size; i++)
        lth[i] = i;

    if (!size)
        printf("Error! currently there are no products in the store\n");

    for (int i = 0; i < size; i++)
    {
        count = 0;
        for (int j = 0; j < size; j++)
        {
            if (list[i].price > list[j].price)
                count++;

        }
        lth[count] = i;
    }
    for (int i = 0; i < size; i++)
        Print_Product(list[lth[i]]);
}

void Select_cat(Product* list, int size)
{
    int x = 0;
    char* cat, str[50];
    printf("Please select a category: ");
    getchar();
    gets(str);

    for (int i = 0; i < size; i++)
    {
        if (!strcmp(list[i].category, str))
        {
            printf("\n");
            Print_Product(list[i]);
            printf("\n");
            x++;
        }

    }
    if (x == 0)
    {
        printf("Category not exist\n");
    }

}

