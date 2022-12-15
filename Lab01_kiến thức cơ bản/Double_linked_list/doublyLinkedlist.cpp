#include<iostream>
using namespace std;

struct DNODE {
	int key;
	DNODE* pNext = NULL;
	DNODE* pPrev = NULL;
};


struct DList {
	DNODE* pHead = NULL;
	DNODE* pTail = NULL;
};

//1. Initialize a NODE from a given integer:
DNODE* createNode(int data)
{
	DNODE* newNode = new DNODE;
	newNode->key = data;
	newNode->pNext = newNode->pPrev = NULL;
	return newNode;
}

//2. Initialize a List from a give NODE :
DList* createList(DNODE* pNode)
{
	DList* L = new DList;
	L->pHead = L->pTail = pNode;
	return L;
}

bool IsEmptyList(DList* L)
{
	return L->pHead == NULL && L->pTail == NULL;
}

//3. Insert an integer to the head of a given List :
bool addHead(DList*& L, int data)
{
	DNODE* add = createNode(data);
	if (L == NULL)
	{
		L = createList(add);
		if (L != NULL)
			return 1;
		return 0;
	}
	if (IsEmptyList(L))
	{
		L->pHead = L->pTail = add;
		return 1;
	}
	add->pNext = L->pHead;
	L->pHead->pPrev = add;
	L->pHead = add;
	return 1;
}



//4. Insert an integer to the tail of a given List:
bool addTail(DList*& L, int data)
{
	DNODE* add = createNode(data);
	if (add == NULL) return 0;
	if (L == NULL)
	{
		L = createList(add);
		if (L != NULL)
			return 1;
		return 0;
	}
	if (IsEmptyList(L))
	{
		L->pHead = L->pTail = add;
		return 1;
	}
	L->pTail->pNext = add;
	add->pPrev = L->pTail;
	L->pTail = add;
	return 1;
}


//5. Remove the first NODE of a given List:
void removeHead(DList*& L)
{
	if (IsEmptyList(L) || L == NULL) return;
	if (L->pHead == L->pTail)
	{
		delete L->pHead;
		L->pHead = L->pTail = NULL;
		return;
	}
	DNODE* temp = L->pHead->pNext;
	temp->pPrev = NULL;
	delete L->pHead;
	L->pHead = temp;
}


//6. Remove the last NODE of a given List :
void removeTail(DList*& L)
{
	if (IsEmptyList(L) || L == NULL) return;
	if (L->pHead == L->pTail)
	{
		delete L->pHead;
		L->pHead = L->pTail = NULL;
		return;
	}

	DNODE* temp = L->pTail;
	L->pTail = L->pTail->pPrev;
	L->pTail->pNext = NULL;
	delete temp;
}


//Remove all NODE from a given List:
void removeAll(DList*& L)
{
	if (IsEmptyList(L))
	{
		return;
	}
	DNODE* cur1 = L->pHead;
	while (cur1 != NULL)
	{
		DNODE* prev = cur1->pPrev;
		cur1 = cur1->pNext;
		delete prev;
	}
	L->pHead = L->pTail = NULL;
}

//8. Remove node before the node has val value in a given List :
void removeBefore(DList* L, int val)
{
	if (IsEmptyList(L) || L == NULL)
	{
		return;
	}
	DNODE* cur1 = L->pHead;
	DNODE* previous = NULL;
	DNODE* prev2 = NULL;
	//đưa cur1 đến node có giá trị là val hoặc đi hết danh sách nếu danh sách ko có node có trị bằng val
	while (cur1->key != val && cur1 != NULL)
	{
		prev2 = previous;
		previous = cur1;
		cur1 = cur1->pNext;
	}
	if (previous == L->pHead)
	{
		removeHead(L);
		return;
	}
	if(cur1==L->pHead)
	{
		cout << "Day la phan tu dau tien cua danh sach nen khong co phan tu truoc no." << endl;
		return;
	}
	if (cur1 != NULL)
	{
		prev2->pNext = cur1;
		cur1->pPrev = prev2;
		delete previous;
		return;
	}
	cout << "Khong tim thay node co chua gia tri can tim" << endl;
}


//9. Remove node after the node has val value in a given List :
void removeAfter(DList* L, int val)
{
	if (IsEmptyList(L))
	{
		return;
	}
	DNODE* curr = L->pHead;
	//cho con trỏ curr đi đến node có giá trị = val hoặc đi hết danh sách liên kết nếu không tồn tại node nào có giá trị bằng val
	while (curr->key != val && curr != NULL)
	{
		curr = curr->pNext;
	}
	if (curr != L->pTail && curr != NULL)
	{
		DNODE* after1 = curr->pNext;//node đứng ngay sau curr
		curr->pNext = after1->pNext;//nối pnext của cur với node sau node cần xóa
		after1->pNext->pPrev = curr;//gán con con trỏ prev của node sau after1 vào curr
		delete after1;
	}
	if (curr == L->pTail)
	{
		cout << "Day la phan tu cuoi cua danh sach nen khong co phan tu sau." << endl;
		return;
	}
	cout << "Khong tim thay phan tu co gia tri can tim." << endl;
}


//10. Insert an integer at a position of a given List:
int countElements(DList* L);

bool addPos(DList*& L, int data, int pos)
{
	if (IsEmptyList(L))
		return 0;

	if (pos > (countElements(L) - 1))
		return 0;
	if (pos == 0)
	{
		addHead(L, data);
		return 1;
	}

	DNODE* curr = L->pHead;
	for (int i = 0; i < pos - 1; i++)
	{
		curr = curr->pNext;
	}
	DNODE* add = createNode(data);
	DNODE* after = curr->pNext;
	add->pNext = after;//nối node add vào sau node curr
	add->pPrev = curr;
	after->pPrev = add;
	curr->pNext = add;
	return 1;
}


//Remove an integer at a position of a given List :
void removePos(DList*& L, int pos)
{
	if (IsEmptyList(L))
		return;

	if (pos > (countElements(L) - 1))
		return;
	if (pos == 0)
	{
		removeHead(L);
		return;
	}

	DNODE* curr = L->pHead;
	for (int i = 0; i < pos - 1; i++)//do khi xóa ta dùng phần tử curr trỏ đến phần tử sau cách 2 Node nghĩa là curr là phần tử đứng trước pos
	{
		curr = curr->pNext;
	}
	DNODE* after = curr->pNext;
	curr->pNext = after->pNext;
	after->pNext->pPrev = curr;
	delete after;

}



//12. Insert an integer before a value of a given List:
bool addBefore(DList* L, int data, int val)
{
	if (IsEmptyList(L))
		return 0;
	if (L->pHead->key == val)
	{
		int success = addHead(L, data);
		if (success)
			return 1;
		return 0;
	}
	DNODE* curr = L->pHead;
	while (curr->key != val && curr != NULL)
	{
		curr = curr->pNext;
	}
	if (curr != NULL)
	{
		DNODE* previous = curr->pPrev;
		DNODE* add = createNode(data);
		previous->pNext = add;
		add->pNext = curr;
		curr->pPrev = add;
		add->pPrev = previous;
		return 1;
	}
	return 0;
}


//13. Insert an integer after a value of a given List :
bool addAfter(DList* L, int data, int val)
{
	if (IsEmptyList(L))
		return 0;
	if (L->pTail->key == val)
	{
		int success = addTail(L, data);
		if (success)
			return 1;
		return 0;
	}
	DNODE* curr = L->pHead;
	while (curr->key != val && curr != NULL)
	{
		curr = curr->pNext;
	}
	if (curr != NULL)
	{
		DNODE* after = curr->pNext;
		DNODE* add = createNode(data);
		curr->pNext = add;
		add->pNext = after;
		after->pPrev = add;
		add->pPrev = curr;
		return 1;
	}
	return 0;
}

//14. Print all elements of a given List:
void PrintList(DList* L)
{
	DNODE* curr = L->pHead;
	cout << "Danh Sach Lien Ket:" << endl;
	while (curr != NULL)
	{
		cout << ' ' << curr->key;
		curr = curr->pNext;
	}
	if (L->pHead == NULL || L == NULL)
		cout << "Empty List.";
	cout << endl;
}


//15. Count the number of elements List:
int countElements(DList* L)
{
	DNODE* curr = L->pHead;
	int length = 0;
	while (curr != NULL)
	{
		curr = curr->pNext;
		length++;
	}
	return length;
}

//16. Create a new List by reverse a given List :
DList* reverseList(DList* L)
{
	if (IsEmptyList(L) || L == NULL) return NULL;
	DList* result = createList(NULL);
	DNODE* curr = L->pHead;
	while (curr != NULL)
	{
		addHead(result, curr->key);
		curr = curr->pNext;
	}
	return result;
}


//17. Remove all duplicates from a given List :
void removeDuplicate(DList*& L)
{
	if (IsEmptyList(L) || L == NULL) return;

	DNODE* curr1 = L->pHead;
	while (curr1 != NULL)
	{
		DNODE* curr2 = curr1->pNext;
		while (curr2 != NULL)
		{
			if (curr2->key == curr1->key)
			{
				DNODE* prevOfcurr2 = curr2->pPrev;
				DNODE* afterOf2 = curr2->pNext;
				delete curr2;
				prevOfcurr2->pNext = afterOf2;
				afterOf2->pPrev = prevOfcurr2;
				curr2 = afterOf2;
				continue;
			}
			curr2 = curr2->pNext;
		}
		curr1 = curr1->pNext;
	}
}



//18. Remove all key value from a given List:
bool removeElement(DList*& L, int key)
{
	if (IsEmptyList(L) || L == NULL) return 0;

	while (L->pHead->key == key)
	{
		removeHead(L);
	}

	DNODE* curr = L->pHead;
	while (curr != NULL)
	{
		if (curr->key == key)
		{
			DNODE* prev = curr->pPrev;
			DNODE* after = curr->pNext;
			prev->pNext = after;
			after->pPrev = prev;			
			delete curr;
			curr = prev->pNext;
			continue;
		}
		curr = curr->pNext;
	}
	return 1;
}

//Input List
void InputList(DList*& l)
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
	//Mớ comment để test các hàm.
	DList* L = NULL;
	L = createList(NULL);
	InputList(L);
	PrintList(L);
	//hàm createNode, createList, addTail đã được kiểm tra qua hàm InputList


	//hàm addHead sẽ được kiểm tra qua hàm revreseList

	//5. Remove the first NODE of a given List:
  /*  removeHead(L);
	PrintList(L);*/

	//6. Remove the last NODE of a given List :
    /*removeTail(L);
	PrintList(L);*/

	//7. Remove all NODE from a given List :
	/* removeAll(L);
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
	/*int a = addPos(L, 6, 3);
	if (!a)
		cout << "Do dai cua danh sach khong du de them vao vi tri nay." << endl;
	PrintList(L);*/

	 //11. Remove an integer at a position of a given List:
	 /*removePos(L, 3);
	 PrintList(L);*/

	 //12.Insert an integer before a value of a given List:
	 /*addBefore(L, 6, 3);
	 PrintList(L);*/

	 //13. Insert an integer after a value of a given List:
	 /*addAfter(L, 6, 3);
	 PrintList(L);*/

	 //14. Print all elements of a given List :
	 /*PrintList(L);*/

	 //15. Count the number of elements List :
	 /*cout << countElements(L) << endl;*/

	 //16. Create a new List by reverse a given List:
	 /*DList* rev = reverseList(L);
	 PrintList(rev);
	 removeAll(rev);
	 delete rev;
	 rev = NULL;*/

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
