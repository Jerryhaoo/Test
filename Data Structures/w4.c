#include <stdio.h>

typedef struct term
{
    int row;
    int col;
    int value;
} Term;

void fastTranspose(Term a[], Term b[]);

void storeSum(Term d[], int *totalD, int row, int column, int *sum);

int compare(int a, int b);

void mmult(Term a[], Term b[], Term d[]);

int main(int argc, char const *argv[])
{
    Term a[101], b[101], d[101];
    int rowsA = 0, colsA = 0, totalA = 0;
    int rowsB = 0, colsB = 0, totalB = 0;
    scanf("%d%d%d", &rowsA, &colsA, &totalA);
    for (int i = 1; i <= totalA; i++)
    {
        scanf("%d%d%d", &a[i].row, &a[i].col, &a[i].value);
    }
    scanf("%d%d%d", &rowsB, &colsB, &totalB);
    for (int i = 1; i <= totalB; i++)
    {
        scanf("%d%d%d", &b[i].row, &b[i].col, &b[i].value);
    }
    a[0].row = rowsA;
    a[0].col = colsA;
    a[0].value = totalA;
    b[0].row = rowsB;
    b[0].col = colsB;
    b[0].value = totalB;
    mmult(a, b, d);
    return 0;
}

void fastTranspose(Term a[], Term b[])
{
    int rowTerms[101] = {}, startingPos[101] = {};
    int i = 0, j = 0, numCols = a[0].col, numTerms = a[0].value;
    b[0].row = numCols, b[0].col = a[0].row;
    b[0].value = numTerms;
    if (numTerms > 0)
    {
        for (i = 0; i < numCols; i++)
        {
            rowTerms[i] = 0;
        }
        for (i = 1; i <= numTerms; i++)
        {
            rowTerms[a[i].col]++;
        }
        startingPos[0] = 1;
        for (i = 1; i < numCols; i++)
        {
            startingPos[i] = startingPos[i - 1] + rowTerms[i - 1];
        }
        for (i = 1; i <= numTerms; i++)
        {
            j = startingPos[a[i].col]++;
            b[j].row = a[i].col;
            b[j].col = a[i].row;
            b[j].value = a[i].value;
        }
    }
}

void storeSum(Term d[], int *totalD, int row, int column, int *sum)
{
    if (*sum)
    {
        if (*totalD < 101)
        {
            d[++*totalD].row = row;
            d[*totalD].col = column;
            d[*totalD].value = *sum;
            *sum = 0;
        }
    }
}

int compare(int a, int b)
{
    if (a > b)
    {
        return -1;
    }
    else if (a == b)
    {
        return 0;
    }
    else if (a < b)
    {
        return 1;
    }
}

void mmult(Term a[], Term b[], Term d[])
{
    int i = 0, j = 0, column = 0, totalB = b[0].value, totalD = 0;
    int rowsA = a[0].row, colsA = a[0].col, totalA = a[0].value;
    int colsB = b[0].col, rowBegin = 1, row = a[1].row, sum = 0;
    Term newB[101];
    fastTranspose(b, newB);
    a[totalA + 1].row = rowsA;
    newB[totalB + 1].row = colsB;
    newB[totalB + 1].col = 0;
    for (i = 1; i <= totalA;)
    {
        sum = 0;
        column = newB[1].row;
        for (j = 1; j <= totalB + 1;)
        {
            if (a[i].row != row)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                for (; newB[j].row == column; j++)
                {
                    ;
                }
                column = newB[j].row;
            }
            else if (newB[j].row != column)
            {
                storeSum(d, &totalD, row, column, &sum);
                i = rowBegin;
                column = newB[j].row;
            }
            else
            {
                switch (compare(a[i].col, newB[j].col))
                {
                case 1:
                    i++;
                    break;
                case 0:
                    sum += (a[i++].value * newB[j++].value);
                    break;
                case -1:
                    j++;
                }
            }
        }
        for (; a[i].row == row; i++)
        {
            ;
        }
        rowBegin = i;
        row = a[i].row;
    }
    d[0].row = rowsA;
    d[0].col = colsB;
    d[0].value = totalD;
    for (i = 0; i <= totalD; i++)
    {
        printf("%d %d %d\n", d[i].row, d[i].col, d[i].value);
    }
}