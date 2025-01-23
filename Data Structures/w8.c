#include <stdio.h>
#include <stdlib.h>

typedef struct listNode
{
    int data;
    struct listNode *nextNode;
} Node;

int main(int argc, char const *argv[])
{
    int n = 0, searchNum = 0, count = 0;
    Node *head, *currentNode, *previous, *newNode;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        currentNode = malloc(sizeof(Node));
        scanf("%d", &(currentNode->data));
        if (i == 0)
        {
            head = currentNode;
            previous = currentNode;
        }
        else
        {
            previous->nextNode = currentNode;
            currentNode->nextNode = NULL;
            previous = currentNode;
        }
    }
    currentNode = head;
    scanf("%d", &searchNum);
    for (int i = 0; i < n; i++)
    {
        if (currentNode->data == searchNum)
        {
            newNode = malloc(sizeof(Node));
            scanf("%d", &(newNode->data));
            newNode->nextNode = currentNode->nextNode;
            currentNode->nextNode = newNode;
            break;
        }
        else
        {
            currentNode = currentNode->nextNode;
            count++;
        }
    }
    printf("%d\n", count);
    currentNode = head;
    for (int i = 0; i <= n; i++)
    {
        printf("%d ", currentNode->data);
        currentNode = currentNode->nextNode;
    }
    return 0;
}