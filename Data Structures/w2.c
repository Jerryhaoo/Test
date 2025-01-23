#include <stdio.h>

int binSearch(int list[], int searchNum, int left, int right);

int main(int argc, char const *argv[])
{
    int n = 0, list[100] = {0}, searchNum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &list[i]);
    }
    scanf("%d", &searchNum);
    printf("%d", binSearch(list, searchNum, 0, n - 1));
    return 0;
}

int binSearch(int list[], int searchNum, int left, int right)
{
    int middle = 0;
    middle = (left + right) / 2;
    if (searchNum > list[middle])
    {
        printf("%d %d %d\n", left, middle, right);
        printf("%d %d %d\n", list[left], list[middle], list[right]);
        return binSearch(list, searchNum, middle + 1, right);
    }
    else if (searchNum < list[middle])
    {
        printf("%d %d %d\n", left, middle, right);
        printf("%d %d %d\n", list[left], list[middle], list[right]);
        return binSearch(list, searchNum, left, middle - 1);
    }
    else
    {
        printf("%d %d %d\n", left, middle, right);
        printf("%d %d %d\n", list[left], list[middle], list[right]);
        return middle;
    }
}