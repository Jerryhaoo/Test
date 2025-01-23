#include <stdio.h>
#include <stdbool.h>

bool graph[10][10];
bool visited[10];

void travel(int n);

void dfs(int i, int n);

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }
    travel(n);
    return 0;
}

void travel(int n)
{
    for (int i = 0; i < n; i++)
    {
        visited[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i] == false)
        {
            printf("%d ", i);
            visited[i] = true;
            dfs(i, n);
        }
    }
}

void dfs(int i, int n)
{
    for (int j = 0; j < n; j++)
    {
        if (graph[i][j] == 1 && visited[j] == false)
        {
            printf("%d ", j);
            visited[j] = true;
            dfs(j, n);
        }
    }
}