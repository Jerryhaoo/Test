#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode
{
    int data;
    struct treeNode *leftChild;
    struct treeNode *rightChild;
} TreeNode;

TreeNode *insertNode(TreeNode *root, int value);

int minNode(TreeNode *root);

TreeNode *deleteNode(TreeNode *root, int key);

void preOrder(TreeNode *root);

int main(int argc, char const *argv[])
{
    TreeNode *root = NULL;
    int n = 0, data = 0, searchNum = 0, newNum = 0;
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        root = insertNode(root, data);
    }
    scanf("%d", &searchNum);
    scanf("%d", &newNum);
    deleteNode(root, searchNum);
    root = insertNode(root, newNum);
    preOrder(root);
    return 0;
}

TreeNode *insertNode(TreeNode *root, int value)
{
    TreeNode *newNode, *currentNode, *parentNode;
    newNode = malloc(sizeof(TreeNode));
    newNode->data = value;
    newNode->leftChild = NULL;
    newNode->rightChild = NULL;
    if (root == NULL)
    {
        return newNode;
    }
    else
    {
        currentNode = root;
        while (currentNode != NULL)
        {
            parentNode = currentNode;
            if (value < currentNode->data)
            {
                currentNode = currentNode->leftChild;
            }
            else if (value > currentNode->data)
            {
                currentNode = currentNode->rightChild;
            }
        }
        if (value < parentNode->data)
        {
            parentNode->leftChild = newNode;
        }
        else if (value > parentNode->data)
        {
            parentNode->rightChild = newNode;
        }
    }
    return root;
}

int minNode(TreeNode *root)
{
    TreeNode *temp = root;
    while (temp->leftChild != NULL)
    {
        temp = temp->leftChild;
    }
    return temp->data;
}

TreeNode *deleteNode(TreeNode *root, int key)
{
    if (root == NULL)
    {
        return root;
    }
    if (key < root->data)
    {
        root->leftChild = deleteNode(root->leftChild, key);
    }
    else if (key > root->data)
    {
        root->rightChild = deleteNode(root->rightChild, key);
    }
    else
    {
        if (root->leftChild == NULL)
        {
            TreeNode *temp = root->rightChild;
            free(root);
            return temp;
        }
        else if (root->rightChild == NULL)
        {
            TreeNode *temp = root->leftChild;
            free(root);
            return temp;
        }
        else
        {
            if (root->leftChild->rightChild == NULL)
            {
                int min = minNode(root->rightChild);
                root->data = min;
                root->rightChild = deleteNode(root->rightChild, min);
            }
            else
            {
                root->data = root->leftChild->rightChild->data;
                root->leftChild->rightChild = deleteNode(root->leftChild->rightChild, root->leftChild->rightChild->data);
            }
        }
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