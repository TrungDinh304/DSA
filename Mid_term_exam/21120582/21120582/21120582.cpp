#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>

using namespace std;

struct BabyName
{
    string name;
    string gender;
    int year;
    int count;
};

struct Node
{
    BabyName data;
    Node* pnext;
};

struct LinkedList
{
    Node* pHead;
    Node* pTail;
};

Node* createNode(BabyName data)
{
    Node* newNode = new Node;
    newNode->data = data;
    newNode->pnext = NULL;
    return newNode;
}


bool IsEmptyList(LinkedList l)
{
    return l.pHead == NULL && l.pTail == NULL;
}

//2. Initialize a List from a give NODE:
LinkedList* createList()
{
    LinkedList* newlist = new LinkedList;
    newlist->pHead = newlist->pTail = NULL;
    return newlist;
}

//4. Insert an integer to the tail of a given List:
void addTail(LinkedList*L,BabyName data)
{
    
    if (L->pHead==NULL)
    {
        L->pHead = L->pTail = createNode(data);
        return;
    }
    Node* add = createNode(data);
    L->pTail->pnext = add;
    L->pTail = add;
    return;
}

BabyName Babyline(string line)
{
    stringstream S(line);
    BabyName A;
    string buffer;
    while (!S.eof())
    {
        getline(S, A.name, ' ');
        getline(S, buffer, ' ');
        A.year = stoi(buffer);
        getline(S, A.gender, ' ');
        getline(S, buffer, ' ');
        A.count = stoi(buffer);
    }
    return A;
}

LinkedList* readBabyNames(string filename)
{
    //CODE HERE
    ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        cout << "Loi mo file.\n";
        return NULL;
    }
    else
        cout << "Mo file thanh cong\n";
    LinkedList* L = createList();
    string line;
    getline(fin, line);
    while (!fin.eof())
    {
        getline(fin, line);
        BabyName A = Babyline(line);
        addTail(L, A);
    }
    return L;
}

void printABB(BabyName a)
{
    cout << a.name << '\t' << a.year << '\t' << a.gender << '\t' << a.count << endl;
}

void printList(LinkedList* L)
{
    Node* cur = L->pHead;
    while (cur != NULL)
    {
        printABB(cur->data);
        cur = cur->pnext;
    }
}

LinkedList* splitBabyNames(LinkedList* list, int year)
{
    //CODE HERE
    LinkedList* res = createList();
    Node* cur = list->pHead;
    while (cur != NULL)
    {
        if (cur->data.year == year)
            addTail(res, cur->data);
        cur = cur->pnext;
    }
    return res;
}

LinkedList* mergeLinkedList(LinkedList* list1, LinkedList* list2)
{
    //CODE HERE
    LinkedList* res = createList();
    Node* cur1 = list1->pHead;
    
    while (cur1 != NULL)
    {
        Node* cur2 = list2->pHead;
        while (cur2 != NULL)
        {
            if ((cur1->data.name == cur2->data.name) && (cur1->data.gender == cur2->data.gender))
            {
                BabyName a;
                a.count = cur1->data.count + cur2->data.count;
                a.name = cur1->data.name;
                a.year = 0;
                a.gender = cur1->data.gender;
                addTail(res, a);
            }
            cur2 = cur2->pnext;
        }
        cur1 = cur1->pnext;
    }

    return res;
}


void printPaths(int** matrix, vector<int>& route, int len_route, int i, int j, int M, int N, int& com, int& ag)
{
    // MxN matrix
    if ((++com && M == 0) || (++com && N == 0))
    {
        return;
    }

    // if the last cell is reached
    if ((++com && i == M - 1) && (++com && j == N - 1))
    {
        // print the route
        ag++;
        for (int k = 0; ++com && k < len_route; k++, ++ag)
        {
            cout << route[k] << " ";
        }
        cout << matrix[i][j] << endl;
        return;
    }

    // add the current cell to route
    route.push_back(matrix[i][j]);
    len_route += 1; ++ag;

    // move down
    if (++com && i + 1 < M)
    {
        printPaths(matrix, route, len_route, i + 1, j, M, N, com, ag);
    }

    // move right
    if (++com && j + 1 < N)
    {
        printPaths(matrix, route, len_route, i, j + 1, M, N, com, ag);
    }

    // move diagonally
    if ((++com && i + 1 < M)  && (++com && j + 1 < N))
    {
        printPaths(matrix, route, len_route, i + 1, j + 1, M, N,  com, ag);
    }

    // backtrack
    route.pop_back();
}


void CountAssignmentandComparision()
{
    
    int M = 3, N = 3;
    int** matrix = new int* [M];
    

    
    for (int i = 0; i < M; i++)
    {
        matrix[i] = new int[N];
    }
    for (int i = 0;  i < M * N; i++)
    {
        matrix[i / N][i % N] = i;
    }

    vector<int> route;
    int len_route = 0;
    int i = 0, j = 0;
    int com = 0;
    int ag = 0;

    // Goi ham printPaths
    printPaths(matrix, route, len_route, i, j, M, N, com, ag); // Ban co the thay doi dong nay neu co thay doi tham so cua ham

    // In ra so phep gan và so phep so sanh
    // CODE HERE
    cout << "So phep so sanh: " << com << endl;
    cout << "So phep gan: " << ag << endl;
}

void heapify(int* a, int n, int i)
{
    int Largest = i;
    int Left = 2 * i + 1;
    int Right = 2 * i + 2;
    if (Left<n && a[Left]>a[Largest])
        Largest = Left;
    if (Right<n && a[Right]>a[Largest])
        Largest = Right;

    if (Largest == i) return;
    swap(a[i], a[Largest]);
    heapify(a, n, Largest);
}

void CreateMaxHeap(int* a, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

void HeapSort(int* a, int n)
{
    CreateMaxHeap(a, n);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}




int countPairs(int* arr, int n, int k)
{
    //CODE HERE
    HeapSort(arr, n);
    int count = 0;
    for (int i = 0; i < n - 1; i++)
    {
        if (i > 0 && arr[i] == arr[i - 1])
            continue;
        for (int j = i + 1; j < n; j++)
        {
            if (arr[j] == arr[i] + k)
                count++;
        }
    }
    return count;
}

int main()
{

    //Cau 1
    string filename = "data.txt";
    // 1.1
    LinkedList* list = readBabyNames(filename);
    //printList(list);
    //// 1.2
    LinkedList* babyNames1880 = splitBabyNames(list, 1880);
    //cout << "=====Baby names 1880=====" << endl;
    //printList(babyNames1880);
    LinkedList* babyNames1881 = splitBabyNames(list, 1881);
    //cout << "=====Baby names 1881=====" << endl;
    //printList(babyNames1881);


    // 1.3 
    LinkedList* mergedList = mergeLinkedList(babyNames1880, babyNames1881);
    //cout << "Baby have same name and gender: " << endl;
    //printList(mergedList);

    // Cau 2
    CountAssignmentandComparision();

    // Cau 3

    int n = 5;
    int* arr = new int[n] {3, 1, 4, 1, 5};
    int k = 2;

    int res = countPairs(arr, n, k);
    cout << res << endl;

    return -1;
}
