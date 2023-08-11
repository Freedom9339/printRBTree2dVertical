#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct node{
    char color;
    int  value;
    struct node *parent;
    struct node *left;
    struct node *right;
} NODE;

NODE* newNode(NODE* root, int value);
NODE* insertBST(NODE* root, NODE* node);
NODE* balanceTree(NODE* root, NODE* node);
NODE* rotateLeft(NODE* root, NODE* x);
NODE* rotateRight(NODE* root, NODE* x);
void freeTree(NODE* root);
void printNChar(char* buff, char* str, int n);
int getDepth(NODE* root, int level);
void print2dWork(NODE* root, char p, char out[][2000], int levels, int level,int spaces);
void print2d(NODE* root);

int main()
{
    //Root node
    NODE* root = NULL;

    //Insert random number between 1 and 100
    srand(time(NULL));
    for (int i = 0; i < 40; i++) {
        root = newNode(root, rand() % 100 + 1);
    }

    //Print tree
    print2d(root);

    //Free memory
    freeTree(root);

    return 0;
}


NODE* newNode(NODE* root, int value)
{
    //Create new node
    NODE* newNode = (NODE*)malloc(sizeof(NODE));
    newNode->color = 'R';
    newNode->value = value;
    newNode->left = NULL;
    newNode->right = NULL;
    
    //Insert new node and balance the tree
    return balanceTree(insertBST(root, newNode), newNode);
}

NODE* insertBST(NODE* root, NODE* node)
{
    //If the tree is empty, return the new node
    if(root == NULL)
    {
        return node;
    }
    
    //Recursively find where the node belongs in the tree
    if(root->value > node->value)
    {
        root->left = insertBST(root->left, node);
        root->left->parent = root;
    }
    
    if(root->value < node->value)
    {
        root->right = insertBST(root->right, node);
        root->right->parent = root;
    }
    
    return root;
}

NODE* balanceTree(NODE* root, NODE* node)
{
    NODE* parent = NULL;
    NODE* grandParent = NULL;
 
    while ((node != root) && (node->color != 'B') && (node->parent) && (node->parent->color == 'R'))
    {
        parent = node->parent;
        grandParent = node->parent->parent;
        
        if(!grandParent)
            break;
        //Parent is left child of Grand-parent
        if (parent == grandParent->left)
        {
 
            NODE* uncle = grandParent->right;
 
            //Uncle is also red
            if (uncle != NULL && uncle->color == 'R')
            {
                grandParent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                node = grandParent;
            }
 
            else {
                //Node is right child of its parent
                if (node == parent->right) {
                    root = rotateLeft(root, parent);
                    node = parent;
                    parent = node->parent;
                }
 
                //Node is left child of its parent
                root = rotateRight(root, grandParent);
                char t = parent->color;
                parent->color = grandParent->color;
                grandParent->color = t;
                node = parent;
            }
        }
 
        //Parent is right child of Grand-parent
        else {
            NODE* uncle = grandParent->left;
 
            //Uncle is also red
            if ((uncle != NULL) && (uncle->color == 'R'))
            {
                grandParent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                node = grandParent;
            }
            else {
                //Node is left child of its parent
                if (node == parent->left) {
                    root = rotateRight(root, parent);
                    node = parent;
                    parent = node->parent;
                }
 
                //Node is right child of its parent
                root = rotateLeft(root, grandParent);
                char t = parent->color;
                parent->color = grandParent->color;
                grandParent->color = t;
                node = parent;
            }
        }
    }

    return root;
}

//Rotate Left on X node
NODE* rotateLeft(NODE* root, NODE* x)
{
    NODE* y = x->right;

    x->right = y->left;
    
    if(x->right)
    {
        x->right->parent = x;
    }
    
    y->parent = x->parent;
    
    if(!x->parent)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    
    y->left = x;
    x->parent = y;

    return root;
}

//Rotate right on X node
NODE* rotateRight(NODE* root, NODE* x)
{
    NODE* y = x->left;

    x->left = y->right;
    
    if(x->left)
    {
        x->left->parent = x;
    }
    
    y->parent = x->parent;
    
    if(!x->parent)
    {
        root = y;
    }
    else if(x == x->parent->left)
    {
        x->parent->left = y;
    }
    else
    {
        x->parent->right = y;
    }
    
    y->right = x;
    x->parent = y;

    return root;
}

//Free tree from memory
void freeTree(NODE* root)
{
    if(root)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

//Print a string n times
void printNChar(char* buff, char* str, int n)
{
    for(int i=0; i < n; i++)
    {
        strcat(buff, str);
    }
}

//Get the deepest depth of a tree
int getDepth(NODE* root, int level)
{
    if(!root)
        return level;
        
    int left = getDepth(root->left, level + 1);
    int right = getDepth(root->right, level + 1);    
    return (left >= right ? left : right);
}

void print2dWork(NODE* root, char p, char out[][2000], int levels, int level,int spaces)
{
    if(!root)
    {
        //If the node is not on the last level
        if(level / 2 < levels)
        {
            //Print spaces for node line
            strcat(out[level], " ");
            printNChar(out[level]," ", spaces);

            int spacesLeft = spaces / 2;
            int spacesRight = spaces + spacesLeft + 1;
            //Print spaces for arrow line depending on side of node
            if(p == 'L')
            {
                strcat(out[level-1], " ");
                printNChar(out[level-1], " ", spacesLeft);
            } else if (p == 'R')
            {
                strcat(out[level-1], " ");
                printNChar(out[level-1], " ", spacesRight);    
            }

            //Loop until we reach the last level
            level = level + 2;
            while((level / 2) < levels) 
            {
                //Print spaces for current node line
                spaces = spaces / 2;
                strcat(out[level], " ");
                printNChar(out[level], " ", spaces);
                
                strcat(out[level], " ");
                printNChar(out[level], " ", spaces);

                spacesLeft = spacesLeft / 2 ;
                spacesRight = spaces + spacesLeft + 1;

                //Print spaces for current arrow line for both L and R
                strcat(out[level-1], " ");
                printNChar(out[level-1], " ", spacesLeft);

                strcat(out[level-1], " ");
                printNChar(out[level-1], " ", spacesRight);
                level = level + 2;
            }    
        }
        return;
    }
    
    //Recursive call for Left child
    print2dWork(root->left, 'L', out, levels, level + 2, spaces / 2);
    
    //Print value and prep spaces for next node
    char buff[10];
    sprintf(buff,"%d", root->value);
    strcat(out[level], buff);
    printNChar(out[level], " ", spaces-(strlen(buff) - 1));

    //Print arrow and prep spaces for next arrow
    int spacesLeft = spaces / 2;
    int spacesRight = spaces + spacesLeft + 1;
    if(root->parent)
    {
        if(root->parent->left == root)
        {
            strcat(out[level-1], "/");
            printNChar(out[level-1], " ", spacesLeft);
        } else 
        {
            strcat(out[level-1], "\\");
            printNChar(out[level-1], " ", spacesRight);
        }
    }
    
    //Recursive call for Right child
    print2dWork(root->right,'R', out, levels, level + 2, spaces / 2);
}

void print2d(NODE* root)
{
    //Get how many levels the tree has
    int levels = getDepth(root, 0);
    
    //Create a line for every node and arrows
    char out[levels*2][2000];    
    memset(out, 0, sizeof(out));

    //Print initial spaces for each line
    int spaces = 0;
    for(int i = (levels * 2) - 1; i >= 0; i--)
    {
        int arrow = (spaces / 2) + (spaces / 4);
        printNChar(out[i], " ", arrow);
        
        i--;
        printNChar(out[i], " ", spaces);
        spaces = (spaces + 1) * 2;
    }

    //At this point, we should have the number of spaces needed for the root level
    //Call the work function to print to each line
    print2dWork(root, '0', out, levels, 0, spaces);

    //Write out each line to stdout
    for(int i=0; i < levels * 2; i++)
    {
        puts(out[i]);
    }
}
