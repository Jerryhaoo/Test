#include <stdio.h>

typedef struct element
{
    int key;
} Element;

void printList(Element list[], int n);

void quickSort(Element list[], int left, int right, int n);

int main(int argc, char const *argv[])
{
    int n = 0;
    Element list[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &list[i]);
    }
    quickSort(list, 0, n - 1, n);
    return 0;
}

void printList(Element list[], int n)
{
    for (int k = 0; k < n; k++)
    {
        printf("%d ", list[k]);
    }
    printf("%s", "\n");
}

void quickSort(Element list[], int left, int right, int n)
{
    int pivot = 0, i = 0, j = 0;
    Element temp;
    if (left < right)
    {
        i = left;
        j = right + 1;
        pivot = list[left].key;
        do
        {
            do
            {
                i++;
            } while (list[i].key < pivot);
            do
            {
                j--;
            } while (list[j].key > pivot);
            if (i < j)
            {
                temp = list[i];
                list[i] = list[j];
                list[j] = temp;
            }
        } while (i < j);
        temp = list[left];
        list[left] = list[j];
        list[j] = temp;
        printList(list, n);
        quickSort(list, left, j - 1, n);
        quickSort(list, j + 1, right, n);
    }
}