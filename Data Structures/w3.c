#include <stdio.h>
#include <string.h>

typedef struct poly
{
    int coef;
    int exp;
} Poly;

int compare(int a, int b);

int main(int argc, char const *argv[])
{
    char arr1[10] = {0}, arr2[10] = {0};
    int poly1[10] = {0}, poly2[10] = {0};
    int startA = 0, finishA = 0, startB = 0, finishB = 0, count = 0;
    Poly terms[10];
    scanf("%s%s", arr1, arr2);
    finishA = strlen(arr1) / 2 - 1;
    startB = finishA + 1;
    finishB = (strlen(arr1) + strlen(arr2)) / 2 - 1;
    for (int i = 0; i < strlen(arr1); i++)
    {
        poly1[i] = arr1[i] - '0';
    }
    for (int i = 0; i < strlen(arr2); i++)
    {
        poly2[i] = arr2[i] - '0';
    }
    for (int i = 0; i < (strlen(arr1) / 2); i++)
    {
        terms[i].coef = poly1[count];
        count += 2;
    }
    count = 0;
    for (int i = 0; i < (strlen(arr2) / 2); i++)
    {
        terms[i + strlen(arr1) / 2].coef = poly2[count];
        count += 2;
    }
    count = 1;
    for (int i = 0; i < (strlen(arr1) / 2); i++)
    {
        terms[i].exp = poly1[count];
        count += 2;
    }
    count = 1;
    for (int i = 0; i < (strlen(arr2) / 2); i++)
    {
        terms[i + strlen(arr1) / 2].exp = poly2[count];
        count += 2;
    }
    while (startA <= finishA && startB <= finishB)
    {
        switch (compare(terms[startA].exp, terms[startB].exp))
        {
        case -1:
            printf("%dX^", terms[startB].coef);
            printf("%d ", terms[startB].exp);
            startB++;
            break;
        case 0:
            if (terms[startA].coef + terms[startB].coef)
            {
                printf("%dX^", terms[startA].coef + terms[startB].coef);
                printf("%d ", terms[startA].exp);
            }
            startA++;
            startB++;
            break;
        case 1:
            printf("%dX^", terms[startA].coef);
            printf("%d ", terms[startA].exp);
            startA++;
        }
    }
    for (; startA <= finishA; startA++)
    {
        printf("%dX^", terms[startA].coef);
        printf("%d ", terms[startA].exp);
    }
    for (; startB <= finishB; startB++)
    {
        printf("%dX^", terms[startB].coef);
        printf("%d ", terms[startB].exp);
    }
    return 0;
}

int compare(int a, int b)
{
    if (a < b)
    {
        return -1;
    }
    else if (a == b)
    {
        return 0;
    }
    else if (a > b)
    {
        return 1;
    }
}