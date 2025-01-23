#include <stdio.h>
#include <stdbool.h>

int check[100];

int find(int n);

bool unions(int i, int j);

int main(int argc, char const *argv[])
{
    int graph[100][100];
    bool visited[100][100];
    int n = 0, edge = 0, tempI = 0, tempJ = 0, k = 0, m = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            visited[i][j] = false;
        }
    }
    for (int j = 0; j < n; j++)
    {
        check[j] = -1;
    }
    while (edge < n - 1)
    {
        int min = 999;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (graph[i][j] < min && visited[i][j] == false && graph[i][j] != 0)
                {
                    min = graph[i][j];
                    tempI = i;
                    tempJ = j;
                    k = i;
                    m = j;
                }
            }
        }
        k = find(k);
        m = find(m);
        if (unions(k, m) == false)
        {
            edge++;
            printf("%d ", min);
        }
        visited[tempI][tempJ] = true;
        visited[tempJ][tempI] = true;
    }
    return 0;
}

int find(int n)
{
    while (check[n] != -1)
    {
        n = check[n];
    }
    return n;
}

bool unions(int i, int j)
{
    if (i != j)
    {
        check[i] = j;
        return false;
    }
    return true;
}