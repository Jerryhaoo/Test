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

void preOrder(TreeNode *root);

void inOrder(TreeNode *root);

void postOrder(TreeNode *root);

int main(int argc, char const *argv[])
{
    TreeNode *root = NULL;
    int n = 0, data[100];
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data[i]);
    }
    for (int i = 0; i < n; i++)
    {
        root = insertNode(data, 0, n);
    }
    printf("%s", "DLR:");
    preOrder(root);
    printf("\n%s", "LDR:");
    inOrder(root);
    printf("\n%s", "LRD:");
    postOrder(root);
    return 0;
}

TreeNode *newNode(int value)
{
    TreeNode *newNode = malloc(sizeof(TreeNode));
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

void preOrder(TreeNode *root)
{
    if (root != NULL)
    {
        printf("%d ", root->data);
        preOrder(root->leftChild);
        preOrder(root->rightChild);
    }
}

void inOrder(TreeNode *root)
{
    if (root != NULL)
    {
        inOrder(root->leftChild);
        printf("%d ", root->data);
        inOrder(root->rightChild);
    }
}

void postOrder(TreeNode *root)
{
    if (root != NULL)
    {
        postOrder(root->leftChild);
        postOrder(root->rightChild);
        printf("%d ", root->data);
    }
}