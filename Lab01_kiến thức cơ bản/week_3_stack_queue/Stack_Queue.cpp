#include <iostream>
using namespace std;

struct NODE {
	int key;
	NODE* pNext;
};


NODE* createNODE(int data)
{
	NODE* newNode = new NODE;
	newNode->key = data;
	newNode->pNext = NULL;
	return newNode;
}


struct Stack
{
	NODE* pTop = NULL;
};

Stack initstack(int data)
{
	Stack init;
	NODE* newnode = createNODE(data);
	newnode->pNext = NULL;
	init.pTop = newnode;
	return init;
}


void Push(Stack &a, int x)
{
	NODE* add = createNODE(x);
	if (a.pTop == NULL)
	{
		a.pTop = add;
		return;
	}
	add->pNext = a.pTop;
	a.pTop = add;
}

//Pop an element out of a given stack, return the key’s value.
int Pop(Stack& a)
{
	int x = a.pTop->key;
	NODE* temp = a.pTop;
	a.pTop = a.pTop->pNext;
	delete temp;
	return x;
}

int NumofStack(Stack a)
{
	if (a.pTop == NULL)
		return 0;
	int count = 0;
	NODE* temp = a.pTop;
	while (temp != NULL)
	{
		count++;
		temp = temp->pNext;
	}
	return count;
}


bool IsEmptyStack(Stack a)
{
	return a.pTop == NULL;
}

//hàm để test
void InputStack(Stack &a)
{
	int n = 0;
	cout << "Nhap so phan tu can nhap vao stack: ";
	cin >> n;
	while (n <= 0)
	{
		cout << "So phan tu khong hop le xin vui long nhap lai: ";
		cin >> n;
	}
	cout << "Nhap cac phan tu: " << endl;
	while (n != 0)
	{
		int input = 0;
		cin >> input;
		Push(a, input);
		n--;
	}
}
//sao khi in ra màn hình stack rỗng để test hàm pop
void printStack(Stack &a)
{
	cout << "Ngan xep: " << endl;
	if (IsEmptyStack(a))
	{
		cout << "\tStack rong: " << endl;
		return;
	}
	while (a.pTop != NULL)
	{
		cout << Pop(a) << ' ';
	}
	cout << endl;
}



struct Queue
{
	NODE* front = NULL;
	NODE* tail = NULL;
};

Queue initQueue(int data)
{
	NODE* nnode = createNODE(data);
	nnode->pNext = NULL;
	Queue a;
	a.front = a.tail = nnode;
	return a;
}


//Determine if a given queue is empty.
bool IsEmptyQueue(Queue a)
{
	return a.front == NULL && a.tail == NULL;
}


void Enqueue(Queue& a, int data)
{
	NODE* add = createNODE(data);
	if (IsEmptyQueue(a))
	{
		a.front = a.tail = add;
		return;
	}
	a.tail->pNext = add;
	a.tail = add;
}


//Dequeue an element out of a given queue, return the key’s value.
int Dequeue(Queue& a)
{

	int x = a.front->key;
	NODE* temp = a.front;
	a.front = a.front->pNext;
	delete temp;
	return x;
}

//Count the number of element of a given queue.
int countNumOfqueue(Queue a)
{
	int count = 0;
	NODE* curr = a.front;
	while (curr != NULL)
	{
		count++;
		curr = curr->pNext;
	}
	return count;
}

//hàm nhập xuất hàng đợi 
void inputQueue(Queue& a)
{
	int n = 0;
	cout << "Nhap so phan tu can nhap vao hang doi: ";
	cin >> n;
	while (n <= 0)
	{
		cout << "So phan tu khong hop le xin vui long nhap lai: ";
		cin >> n;
	}
	cout << "Nhap cac phan tu: " << endl;
	while (n > 0)
	{
		int input = 0;
		cin >> input;
		Enqueue(a, input);
		n--;
	}
}

//sau khi xuất ra màn hình queue rỗng để test hàm dequeue
void printQueue(Queue a)
{
	cout << "Hang doi:" << endl;
	if (IsEmptyQueue(a))
	{
		cout << "\tHang doi rong." << endl;
		return;
	}
	while (a.front != NULL)
	{
		cout << Dequeue(a) << ' ';
	}
	cout << endl;
}


int main()
{
	//mở commnet để test.
	/*Stack a;
	InputStack(a);
	cout << "Stack a co " << NumofStack(a) << " phan tu" << endl;
	printStack(a);
	cout << "Stack a co " << NumofStack(a) << " phan tu" << endl;

	Stack b = initstack(1);
	cout << "Stack b co " << NumofStack(b) << " phan tu" << endl;
	printStack(b);
	Stack c;
	c.pTop = NULL;
	cout << "Stack c co " << NumofStack(c) << " phan tu" << endl;*/


	/*Queue a;
	a = initQueue(1);
	cout << "Queue a co " << countNumOfqueue(a) << " phan tu" << endl;
	printQueue(a);
	Queue b;
	inputQueue(b);
	cout << "Queue b co " << countNumOfqueue(b) << " phan tu" << endl;
	printQueue(b);
	Queue c;
	cout << "Queue c co " << countNumOfqueue(c) << " phan tu" << endl;
	printQueue(c);*/



	return 0;
}

