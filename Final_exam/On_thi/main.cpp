#include<iostream>
#include<algorithm>
#include<vector>
using namespace std;


// Cau 1
// 1.a

void BuildMaxHeap(int arr[], int n) // Ham xay dung min heap
{
	// Todo 
}


// 1.b
void HeapSort(int arr[], int n) // Ham sap xep mang bang heap sort
{

}

// Cau 2

struct Node {
	int key;
	Node* left;
	Node* right;
};

//2.a
Node* createBST(int arr[], int n)
{
	return NULL;
}

//2.b 
int calHeight(Node* root)
{
	return 0;
}
//2.c
bool isAVL(Node* root)
{
	return false;
}


// Cau 3
bool DelimeterChecker(string expression)
{
	return false;
}

// Cau 4
string ds_loai[6] = { "vat nuoi", "dong vat hoang da", "con trung", "luong cu","dong vat duoi nuoc", "loai chim" };

struct Animal {
	string en;
	string ph;
	string vn;
	int loai;
};

//4.1
vector<Animal> readAnimals(string filename)
{
	return vector<Animal>();
}
//4.2
Animal* saveAnimals(vector<Animal> animals)
{
	return NULL;
}
//4.3
Animal* searchAnimal(string name)
{
	return NULL;
}

// Sinh vien khong thay doi doan code duoi day
vector<int> nodes;
void traverse(Node* root)
{
	if (root == NULL) {
		return;
	}
	traverse(root->left);
	nodes.push_back(root->key);
	traverse(root->right);
}

int main()
{
	int arr[11] = { 1, 3, 5, 4, 6, 13, 10, 9, 8, 15, 17 };
	int n = 11;

	int c_r[11] = { 17, 15, 13, 9, 6, 5, 10, 4, 8, 3,1 };
	BuildMaxHeap(arr, n);
	
	bool flag = true;
	for (int i = 0; i < n; i++)
	{
		if (arr[i] != c_r[i])
		{
			flag = false;
			break;
		}
	}
	if (flag == false) {
		cout << "Cau 1.a sai!" << endl;
	}
	else {
		cout << "Cau 1.a dung!" << endl;
	}

	HeapSort(arr, n);
	if (is_sorted(arr, arr + n))
	{
		cout << "Cau 1.b dung!" << endl;
	}
	else {
		cout << "Cau 1.b sai" << endl;
	}

	int arr_2[10] = { 5,2,7,1,4,6,5,3,9,6 };
	n = 10;

	Node* root = createBST(arr_2, n);
	traverse(root);
	int c_r_2[10] = { 1,2,3,4,5,6,7,9,15,16 };
	flag = true;
	for (int i = 0; i < nodes.size(); i++)
	{
		if (nodes[i] != c_r_2[i])
		{
			flag = false;
			break;
		}
	}
	if (flag == true && nodes.size() > 0)
	{
		cout << "Cau 2.a dung" << endl;
	}
	else {
		cout << "Cau 2.a sai" << endl;
	}

	int height = calHeight(root);
	if (height == 3)
	{
		cout << "Cau 2.b dung" << endl;
	}
	else {
		cout << "Cau 2.b sai" << endl;
	}

	bool is_avl = isAVL(root);
	if (is_avl == false)
	{
		cout << "Cau 2.c sai" << endl;
	}
	else {
		cout << "Cau 2.c dung" << endl;
	}


	

	cout << "\nCHUC CAC BAN LAM BAI TOT!" << endl;
}