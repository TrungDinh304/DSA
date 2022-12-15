#include <iostream>
using namespace std;


struct AVLNODE {
    int key;
    AVLNODE* pLeft;
    AVLNODE* pRight;
    int height;
};

//=====1.========
//Initialize a node with key is a given value:
AVLNODE* createNode(int data)
{
    AVLNODE* Nw = new AVLNODE;
    Nw->key = data;
    Nw->pLeft = Nw->pRight = NULL;
    Nw->height = 1;
    return Nw;
}







//rotate
/*
     y                               x
    / \     Right Rotation          /  \
   x   T3   - - - - - - - >        T1   y
  / \                                  / \
 T1  T2                               T2  T3
 
 
 */

/*

       x                               y
      / \       Left Rotation         / \
     T1  y      - - - - - - >        x  T3
        / \                         / \
       T2  T3                      T1 T2


*/
//==========2.====================
int Height(AVLNODE* proot)
{
    if (proot == NULL)
        return 0;
    return proot->height;
}

void leftRotation(AVLNODE*& proot)
{
    AVLNODE* temp = proot;
    proot = proot->pRight;
    temp->pRight = proot->pLeft;
    proot->pLeft = temp;

    temp->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
    proot->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
}


void rightRotation(AVLNODE*& proot)
{
    AVLNODE* temp = proot;
    proot = proot->pLeft;
    temp->pLeft = proot->pRight;
    proot->pRight = temp;

    temp->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
    proot->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
}

int get_Balance(AVLNODE* p)
{
    if (p == NULL)
        return 0;
    return Height(p->pLeft) - Height(p->pRight);
}

//Add a node with given value x into a given AVL tree(Notify if the given value existed) :
void Insert(AVLNODE*& pRoot, int x)
{
    if (pRoot == NULL)
    {
        AVLNODE* add = createNode(x);
        pRoot = add;
        return;
    }
    if (pRoot->key == x)
    {
        cout << "Node chua gia tri " << x << " da ton tai trong cay AVL." << endl;
        return;
    }

    if (x > pRoot->key)
        Insert(pRoot->pRight, x);
    else if (x < pRoot->key)
        Insert(pRoot->pLeft, x);

    pRoot->height = max(Height(pRoot->pLeft), Height(pRoot->pRight)) + 1;

    int balance = get_Balance(pRoot);
    //mất cân bằng trái trái
    if (balance > 1 && x < pRoot->pLeft->key)
    {
        rightRotation(pRoot);
        return;
    }
    //mất cây bằng trái phải
    if (balance > 1 && x > pRoot->pLeft->key)
    {
        leftRotation(pRoot->pLeft);
        rightRotation(pRoot);
        return;
    }
    // mất cân bằng phải phải
    if (balance<-1 && x>pRoot->pRight->key)
    {
        leftRotation(pRoot);
        return;
    }
    //mất cân bằng phải trái
    if (balance < -1 && x < pRoot->pRight->key)
    {
        rightRotation(pRoot->pRight);
        leftRotation(pRoot);
        return;
    }
}

//===========3.===================
int getAVLmax(AVLNODE* proot)
{
    if (proot == NULL)
        return 0;
    if (proot->pRight == NULL)
        return proot->key;
    return getAVLmax(proot->pRight);
}

void Remove(AVLNODE*& pRoot, int x)
{
    if (pRoot == NULL)
        return;
    if (x > pRoot->key)
        Remove(pRoot->pRight, x);
    else if (x < pRoot->key)
        Remove(pRoot->pLeft, x);


    if (x == pRoot->key)
    {
        AVLNODE* temp = pRoot;
        if (pRoot->pLeft == NULL)
        {
            pRoot = pRoot->pRight;
            delete temp;

        }

        else if (pRoot->pRight == NULL)
        {
            pRoot = pRoot->pLeft;
            delete temp;
        }
        else
        {
            int themang = getAVLmax(pRoot->pLeft);
            pRoot->key = themang;
            Remove(pRoot->pLeft, themang);
        }
    }

    if (pRoot == NULL)
        return;

    pRoot->height = max(Height(pRoot->pLeft), Height(pRoot->pRight)) + 1;

    int balance = get_Balance(pRoot);
    //mất cân bằng trái trái
    if (balance > 1 && x > pRoot->pLeft->key)
    {
        rightRotation(pRoot);
        return;
    }
    //mất cây bằng trái phải
    if (balance > 1 && x < pRoot->pLeft->key)
    {
        leftRotation(pRoot->pLeft);
        rightRotation(pRoot);
        return;
    }
    // mất cân bằng phải phải
    if (balance < -1 && x < pRoot->pRight->key)
    {
        leftRotation(pRoot);
        return;
    }
    //mất cân bằng phải trái
    if (balance < -1 && x > pRoot->pRight->key)
    {
        rightRotation(pRoot->pRight);
        leftRotation(pRoot);
        return;
    }
}

//=================4.===================
bool isAVL(AVLNODE* pRoot)
{
    if (pRoot == NULL)
        return 1;
    if (get_Balance(pRoot) < -1 || get_Balance(pRoot) > 1)
        return 0;
    return isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}



//==================các hàm hỗ trợ để test===============


//4. In-order Traversal:
void LNR(AVLNODE* pRoot)
{
    if (pRoot == NULL) return;
    LNR(pRoot->pLeft);
    cout << pRoot->key << ' ';
    LNR(pRoot->pRight);
}


void print_i_level(AVLNODE* proot, int i);
//6. Level - order Traversal :
void LevelOrder(AVLNODE* pRoot)
{
    int h = pRoot->height;
    for (int i = 0; i <= h; i++)
    {
        print_i_level(pRoot, i);
    }
}





void print_i_level(AVLNODE* proot, int i)
{
    if (proot == NULL) return;
    if (i == 0)
        cout << proot->key << ' ';
    if (i > 0)
    {
        print_i_level(proot->pLeft, i - 1);
        print_i_level(proot->pRight, i - 1);
    }
}

void InsertBST(AVLNODE*& proot, int x)
{
    if (proot == NULL)
    {
        proot = createNode(x);
        return;
    }
    if (proot->key == x) return;
    if (proot->key > x) Insert(proot->pLeft, x);
    else Insert(proot->pRight, x);
}

AVLNODE* createBSTTree(int a[], int n)
{
    AVLNODE* New_tree = NULL;
    for (int i = 0; i < n; i++)
        Insert(New_tree, a[i]);
    return New_tree;
}
int main()
{
    AVLNODE* root = NULL;

    /* Constructing tree given in
    the above figure */
    Insert(root, 10);
    Insert(root, 20);
    Insert(root, 30);
    Insert(root, 40);
    Insert(root, 50);
    Insert(root, 25);

    /* The constructed AVL Tree would be
          30
          / \
         20 40
         / \ \
        10 25 50
    */
    cout << "\nPreorder traversal of the "
        "constructed AVL tree is \n";
    //kết quả mong đợi: 1
    cout << "AVL (Y/N): " << isAVL(root) << endl;
    //kết quả mong đợi: 30, 20, 40, 10, 25, 50
    LevelOrder(root);
    cout << endl;
    //kết quả mong đợi: là một dãy số tăng dần.
    LNR(root);


    /* The constructed AVL Tree after Remove 50,40 would be
          20
          / \
         10 30
            /
           25 
    */ 
    cout << "\n\nPreorder traversal of the "
        "constructed AVL tree after remove 50 and 40 is \n";
    Remove(root, 50);
    Remove(root, 40);
    //kết quả mong đợi là 1 dãy số tăng dần
    LNR(root);
    cout << endl;
    //kết quả mong đợi: 20, 10, 30, 25
    LevelOrder(root);
    

    return 0;
}

