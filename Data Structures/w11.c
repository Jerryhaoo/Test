#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    int data;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
} TreeNode;

TreeNode *newNode(int value);

TreeNode *insertNode(int value[], int level, int nodeNum);

void preOrder(TreeNode *root, int key);

int main(int argc, char const *argv[])
{
    TreeNode *root = NULL;
    int n = 0, data[1000] = {0}, searchNum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < n; i++)
    {
        root = insertNode(data, 0, n);
    }
    scanf("%d", &searchNum);
    preOrder(root, searchNum);
    return 0;
}

TreeNode *newNode(int value)
{
    TreeNode *newNode = NULL;
    newNode = malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    return newNode;
}

TreeNode *insertNode(int value[], int level, int nodeNum)
{
    TreeNode *root = NULL;
    if (level < nodeNum)
    {
        root = newNode(value[level]);
        root->leftChild = insertNode(value, 2 * level + 1, nodeNum);
        root->rightChild = insertNode(value, 2 * level + 2, nodeNum);
    }
    return root;
}

void preOrder(TreeNode *root, int key)
{
    if (root != NULL && root->data != key)
    {
        printf("%d ", root->data);
        preOrder(root->leftChild, key);
        preOrder(root->rightChild, key);
    }
}