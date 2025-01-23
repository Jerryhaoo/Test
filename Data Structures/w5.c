#include <stdio.h>
#include <time.h>

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
    int e[400][400], f[400][400], h[400][400];
    double diffA = 0.0;
    clock_t startA, endA;
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 400; j++)
        {
            e[i][j] = 0;
            f[i][j] = 0;
            h[i][j] = 0;
        }
    }
    e[0][0] = 1;
    f[0][0] = 1;
    startA = clock();
    for (int i = 0; i < 400; i++)
    {
        for (int j = 0; j < 400; j++)
        {
            h[i][j] = 0;
            for (int k = 0; k < 400; k++)
            {
                h[i][j] += e[i][k] * f[k][j];
            }
        }
    }
    endA = clock();
    diffA = endA - startA;
    printf("%f ms\n", diffA / CLOCKS_PER_SEC);

    Term a[400], b[400], d[400];
    int totalA = 0;
    int totalB = 0;
    double diffB = 0.0;
    clock_t startB, endB;
    a[0].row = 400;
    a[0].col = 400;
    a[0].value = 1;
    b[0].row = 400;
    b[0].col = 400;
    b[0].value = 1;
    totalA = a[0].value;
    totalB = b[0].value;
    for (int i = 1; i <= totalA; i++)
    {
        a[i].row = 0;
        a[i].col = 0;
        a[i].value = 1;
    }
    for (int i = 1; i <= totalB; i++)
    {
        b[i].row = 0;
        b[i].col = 0;
        b[i].value = 1;
    }
    startB = clock();
    mmult(a, b, d);
    endB = clock();
    diffB = endB - startB;
    printf("%f ms\n", diffB / CLOCKS_PER_SEC);
    return 0;
}

void fastTranspose(Term a[], Term b[])
{
    int rowTerms[400] = {}, startingPos[400] = {};
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
        if (*totalD < 400)
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
    Term newB[400];
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
}