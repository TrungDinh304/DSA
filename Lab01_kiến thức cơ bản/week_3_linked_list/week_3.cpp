#include<iostream>
using namespace std;


//linked list
//cấu trúc của 1 Node trong link list
struct NODE {
    int key;
    NODE* pNext = NULL;
};

struct List {
    NODE* pHead = NULL;
    NODE* pTail = NULL;
};

//1. Initialize a NODE from a given integer:
NODE* createNode(int data)
{
    NODE* newNode = new NODE;
    newNode->key = data;
    newNode->pNext = NULL;
    return newNode;
}


bool IsEmptyList(List l)
{
    return l.pHead == NULL && l.pTail == NULL;
}

//2. Initialize a List from a give NODE:
List* createList(NODE* pNode)
{
    List* newlist = new List;
    newlist->pHead = newlist->pTail = pNode;
    return newlist;
}

//3. Insert an integer to the head of a given List:
bool addHead(List*& L, int data)
{
    NODE* add = createNode(data);
    if (add == NULL) return 0;
    if (IsEmptyList(*L))
    {
        L->pHead = L->pTail = add;
        return 1;
    }
    add->pNext = L->pHead;
    L->pHead = add;
    return 1;
}

//4. Insert an integer to the tail of a given List:
bool addTail(List*& L, int data)
{
    NODE* add = createNode(data);
    if (add == NULL) return 0;
    if (IsEmptyList(*L))
    {
        L->pHead = L->pTail = add;
        return 1;
    }
    L->pTail->pNext = add;
    L->pTail = add;
    return 1;
}

//5. Remove the first NODE of a given List :
void removeHead(List*& L)
{
    if (IsEmptyList(*L)) return;
    if (L->pHead == L->pTail)
    {
        delete L->pHead;
        L->pHead = L->pTail = NULL;
        return;
    }
    NODE* temp = L->pHead;
    L->pHead = L->pHead->pNext;
    delete temp;
}

//6. Remove the last NODE of a given List :
void removeTail(List*& L)
{
    if (L->pHead == L->pTail)
    {
        delete L->pHead;
        L->pHead = L->pTail = NULL;
        return;
    }
    NODE* cur = L->pHead;
    while (cur->pNext != L->pTail)
    {
        cur = cur->pNext;
    }
    delete L->pTail;
    L->pTail = cur;
    cur->pNext = NULL;
}

//Remove all NODE from a given List:
void removeAll(List*& L)
{
    if (IsEmptyList(*L))
    {
        return;
    }
    NODE* cur1 = L->pHead;
    NODE* previous = NULL;
    while (cur1 != NULL)
    {
        previous = cur1;
        cur1 = cur1->pNext;
        delete previous;
    }
    L->pHead = L->pTail = NULL;
}


//8. Remove node before the node has val value in a given List :
void removeBefore(List* L, int val)
{
    if (IsEmptyList(*L))
    {
        return;
    }
    NODE* cur1 = L->pHead;
    NODE* previous = NULL;
    NODE* prev2 = NULL;
    while (cur1->key != val && cur1!=NULL)
    {
        prev2 = previous;
        previous = cur1;
        cur1 = cur1->pNext;
    }
    if (previous == L->pHead)
    {
        L->pHead = cur1;
        delete previous;
        return;
    }
    if (cur1 == L->pHead)
    {
        cout << "Day la phan tu dau tien cua danh sach nen khong co phan tu truoc no." << endl;
        return;
    }
    if (cur1 != NULL)
    {
        prev2->pNext = cur1;
        delete previous;
        return;
    }
    cout << "Khong tim thay node co chua gia tri can tim" << endl;
}


//9. Remove node after the node has val value in a given List :
void removeAfter(List* L, int val)
{
    if (IsEmptyList(*L))
    {
        return;
    }
    NODE* curr = L->pHead;
    while (curr->key != val && curr != NULL)
    {
        curr = curr->pNext;
    }
    if (curr != L->pTail)
    {
        NODE* after1 = curr->pNext;//node đứng ngay sau curr
        curr->pNext = after1->pNext;//nối pnext của cur với node sau node cần xóa
        delete after1;
    }
}




//10. Insert an integer at a position of a given List:
int countElements(List* L);

bool addPos(List*& L, int data, int pos)
{
    if (IsEmptyList(*L))
        return 0;

    if (pos > (countElements(L) - 1))
        return 0;
    if (pos == 0)
    {
        addHead(L, data);
        return 1;
    }

    NODE* curr = L->pHead;
    for (int i = 0; i < pos - 1; i++)
    {
        curr = curr->pNext;
    }
    NODE* add = createNode(data);
    add->pNext = curr->pNext;
    curr->pNext = add;
    return 1;
}

//Remove an integer at a position of a given List :
void removePos(List*& L, int pos)
{
    if (IsEmptyList(*L))
        return;

    if (pos > (countElements(L) - 1))
        return;
    if (pos == 0)
    {
        removeHead(L);
        return;
    }

    NODE* curr = L->pHead;
    for (int i = 0; i < pos - 1; i++)//do khi xóa ta dùng phần tử curr trỏ đến phần tử sau cách 2 Node nghĩa là curr là phần tử đứng trước pos
    {
        curr = curr->pNext;
    }
    NODE* after = curr->pNext;
    curr->pNext = after->pNext;
    delete after;
}

//12. Insert an integer before a value of a given List:
bool addBefore(List* L, int data, int val)
{
    if (IsEmptyList(*L))
        return 0;
    if (L->pHead->key == val)
    {
        int success = addHead(L, data);
        if (success)
            return 1;
        return 0;
    }
    NODE* curr = L->pHead;
    NODE* prev = NULL;
    while (curr->key != val && curr != NULL)
    {
        prev = curr;
        curr = curr->pNext;
    }
    if (curr != NULL)
    {
        NODE* add = createNode(data);
        add->pNext = curr;
        prev->pNext = add;
        return 1;
    }
    return 0;
}

//13. Insert an integer after a value of a given List :
bool addAfter(List* L, int data, int val)
{
    if (IsEmptyList(*L))
        return 0;
    if (L->pTail->key == val)
    {
        int success = addTail(L, data);
        if (success)
            return 1;
        return 0;
    }
    NODE* curr = L->pHead;
    while (curr->key != val && curr != NULL)
    {
        curr = curr->pNext;
    }
    if (curr != NULL)
    {
        NODE* after = curr->pNext;
        NODE* add = createNode(data);
        add->pNext = after;
        curr->pNext = add;
        return 1;
    }
    return 0;
}


//14. Print all elements of a given List:
void PrintList(List* L)
{
    NODE* curr = L->pHead;
    cout << "Danh Sach Lien Ket:" << endl;
    while (curr != NULL)
    {
        cout << ' ' << curr->key;
        curr = curr->pNext;
    }
    cout << endl;
}

//15. Count the number of elements List:
int countElements(List* L)
{
    NODE* curr = L->pHead;
    int length = 0;
    while (curr != NULL)
    {
        curr = curr->pNext;
        length++;
    }
    return length;
}

//16. Create a new List by reverse a given List :
List* reverseList(List* L)
{
    if (IsEmptyList(*L) || L == NULL) return NULL;
    List* result = createList(NULL);
    NODE* curr = L->pHead;
    while (curr != NULL)
    {
        addHead(result, curr->key);
        curr = curr->pNext;
    }
    return result;
}

//17. Remove all duplicates from a given List :
void removeDuplicate(List*& L)
{
    if (IsEmptyList(*L) || L == NULL) return;

    NODE* curr1 = L->pHead;
    while (curr1 != NULL)
    {
        NODE* curr2 = curr1->pNext;
        NODE* prevOfcurr2 = curr1;
        while (curr2 != NULL)
        {
            if (curr2->key == curr1->key)
            {
                prevOfcurr2->pNext = curr2->pNext;
                delete curr2;
                curr2 = prevOfcurr2->pNext;
                continue;
            }
            prevOfcurr2 = curr2;
            curr2 = curr2->pNext;
        }
        curr1 = curr1->pNext;
    }
}

//18. Remove all key value from a given List:
bool removeElement(List*& L, int key)
{
    if (IsEmptyList(*L) || L == NULL) return 0;

    while (L->pHead->key == key)
    {
        removeHead(L);
    }

    NODE* curr = L->pHead;
    NODE* prev = NULL;
    while (curr != NULL)
    {
        if (curr->key == key)
        {
            prev->pNext = curr->pNext;
            delete curr;
            curr = prev->pNext;
            continue;
        }
        prev = curr;
        curr = curr->pNext;
    }
    return 1;
}

//Input List
void InputList(List* &l)
{
    int n = 0;
    cout << "Nhap so phan tu: ";
    cin >> n;
    while (n <= 0)
    {
        cout << "So phan tu khong hop le vui long nhap lai: ";
        cin >> n;
    }
    for (int i = 0; i < n; i++)
    {
        int data = 0;
        cin >> data;
        addTail(l, data);
    }
}



int main()
{
    List* L = NULL;
    L = createList(NULL);
    InputList(L);
    PrintList(L);
    //hàm createNode, createList, addTail đã được kiểm tra qua hàm InputList


    //hàm addHead sẽ được kiểm tra qua hàm revreseList

    //5. Remove the first NODE of a given List:
   /* removeHead(L);
    PrintList(L);*/

    //6. Remove the last NODE of a given List :
   /* removeTail(L);
    PrintList(L);*/

   //7. Remove all NODE from a given List :
    /*removeAll(L);
    PrintList(L);*/

    //8. Remove node before the node has val value in a given List :
    //xóa phần tử trước phần tử có giá trị nhập vào
   /* int x = 0;
    cout << "Nhap gia tri muon xoa truoc no: ";
    cin >> x;
    removeBefore(L, x);
    PrintList(L);*/

    //9. Remove node after the node has val value in a given List :
    /*int x = 0;
    cout << "Nhap gia tri muon xoa sau no: ";
    cin >> x;
    removeAfter(L, x);
    PrintList(L);*/
    //10. Insert an integer at a position of a given List:
    /*addPos(L, 6, 3);
    PrintList(L);*/

    //11. Remove an integer at a position of a given List:
    /*removePos(L, 3);
    PrintList(L);*/

    //12.Insert an integer before a value of a given List:
    /*addBefore(L, 6, 3);
    PrintList(L);*/

    //13. Insert an integer after a value of a given List:
   /* addAfter(L, 6, 3);
    PrintList(L);*/

    //14. Print all elements of a given List :
    /*PrintList(L);*/

    //15. Count the number of elements List :
    /*cout << countElements(L) << endl;*/

    //16. Create a new List by reverse a given List:
    /*List* rev = reverseList(L);
    PrintList(rev);*/

    //17. Remove all duplicates from a given List:
    /*removeDuplicate(L);
    PrintList(L);*/

    //18.Remove all key value from a given List:
    /*removeElement(L, 0);
    PrintList(L);*/


    removeAll(L);
    delete L;
    L = NULL;

    return 0;
}

