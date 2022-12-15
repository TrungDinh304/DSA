#include<iostream>
#include<vector>

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

LinkedList* readBabyNames(string filename)
{
    //CODE HERE
}

LinkedList* splitBabyNames(LinkedList* list, int year)
{
    //CODE HERE
}

LinkedList* mergeLinkedList(LinkedList* list1, LinkedList* list2)
{
	//CODE HERE
}


void printPaths(int** matrix, vector<int> &route, int len_route,  int i, int j, int M, int N)
{
    // MxN matrix
    if(M == 0 || N == 0)
    {
        return;
    }

    // if the last cell is reached
    if(i == M-1 && j == N-1)
    {
        // print the route
        for (int k = 0; k < len_route; k++)
        {
            cout << route[k] << " ";
        }
        cout << matrix[i][j] << endl;
        return;
    }

    // add the current cell to route
    route.push_back(matrix[i][j]);
    len_route += 1;

    // move down
    if (i + 1 < M)
    {
        printPaths(matrix, route, len_route, i+1, j, M, N);
    }
    
    // move right
    if (j + 1 < N)
    {
        printPaths(matrix, route, len_route, i, j+1, M, N);
    }

    // move diagonally
    if (i + 1 < M && j + 1 < N)
    {
        printPaths(matrix, route, len_route,  i+1, j+1, M, N);
    }

    // backtrack
    route.pop_back();
}


void CountAssignmentandComparision()
{
    int M = 3, N=3;
    int** matrix = new int*[M];

    for(int i =0; i < M; i++)
    {
        matrix[i] = new int[N];
    }

    for (int i = 0; i < M*N; i++)
    {
        matrix[i/N][i%N] = i;
    }

    vector<int> route;
    int len_route = 0;
    int i = 0, j = 0;
    
    // Goi ham printPaths
    printPaths(matrix, route, len_route, i, j, M, N); // Ban co the thay doi dong nay neu co thay doi tham so cua ham
    
    // In ra so phep gan và so phep so sanh
    // CODE HERE
}

int countPairs(int* arr, int n, int k)
{
    //CODE HERE
}

int main()
{

    // Cau 1
    string filename = "data.txt";
    // 1.1
    LinkedList* list = readBabyNames(filename);
    // 1.2
    LinkedList* babyNames1880 = splitBabyNames(list, 1880);
    LinkedList* babyNames1881 = splitBabyNames(list, 1881);
    
    // 1.3 
    mergedList = mergeLinkedList(babyNames1880, babyNames1881)
    
    // Cau 2
    CountAssignmentandComparision();

    // Cau 3

    int n = 5;
    int * arr = new int[n]{3, 1, 4, 1, 5};
    int k = 2;

    int res = countPairs(arr, n, k);
    cout << res << endl;
    
    return -1;
}
