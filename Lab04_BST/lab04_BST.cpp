#include <iostream>
using namespace std;


struct BSTNode {
	int key;
	BSTNode* pLeft;
	BSTNode* pRight;
};

//1. Initialize a NODE from a given value:
BSTNode* createNode(int data)
{
	BSTNode* newNode = new BSTNode;
	newNode->key = data;
	newNode->pLeft = newNode->pRight = NULL;
	return newNode;
}

//2. Add a NODE with given value into a given Binary Search Tree:
void Insert(BSTNode*& proot, int x)
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

//3. Pre-order Traversal:
void NLR(BSTNode* pRoot)
{
	if (pRoot == NULL) return;
	cout << pRoot->key << ' ';
	NLR(pRoot->pLeft);
	NLR(pRoot->pRight);
}

//4. In-order Traversal:
void LNR(BSTNode* pRoot)
{
	if (pRoot == NULL) return;
	LNR(pRoot->pLeft);
	cout << pRoot->key << ' ';
	LNR(pRoot->pRight);
}

//5. Post - order Traversal :
void LRN(BSTNode* pRoot)
{
	if (pRoot == NULL) return;
	LRN(pRoot->pLeft);
	LRN(pRoot->pRight);
	cout << pRoot->key << ' ';
}


int Height(BSTNode* proot);
void print_i_level(BSTNode* proot, int i);
//6. Level - order Traversal :
void LevelOrder(BSTNode* pRoot)
{
	int h = Height(pRoot);
	for (int i = 0; i <= h; i++)
	{
		print_i_level(pRoot, i);
	}
}

//7. Calculate the height of a given Binary Tree;
int Height(BSTNode* proot)
{
	if (proot == NULL) return 0;
	return 1 + max(Height(proot->pLeft), Height(proot->pRight));
}

//8. Count the number of NODE from a given Binary Tree :
int countNode(BSTNode* pRoot)
{
	if (pRoot == NULL) return 0;
	return 1 + countNode(pRoot->pLeft) + countNode(pRoot->pRight);
}

//9. Calculate the total value of all NODEs from a given Binary Tree :
int sumNode(BSTNode* pRoot)
{
	if (pRoot == NULL) return 0;
	return pRoot->key + sumNode(pRoot->pLeft) + sumNode(pRoot->pRight);
}

//10. Find and return a NODE with given value from a given Binary Search Tree :
BSTNode* Search(BSTNode* pRoot, int x)
{
	if (pRoot == NULL) 
		return NULL;
	if (pRoot->key == x)
		return pRoot;
	if (x > pRoot->key) 
		return Search(pRoot->pRight, x);
	return Search(pRoot->pLeft, x);

}


int getMax(BSTNode* pRoot);
//11. Remove a NODE with given value from a given Binary Search Tree :
void Remove(BSTNode*& pRoot, int x)
{
	if (pRoot == NULL)
		return;

	if (x < pRoot->key)
	{
		Remove(pRoot->pLeft, x);
		return;
	}

	if (x > pRoot->key)
	{
		Remove(pRoot->pRight, x);
		return;
	}

	BSTNode* temp = pRoot;
	if (pRoot->pLeft == NULL)
	{
		pRoot = pRoot->pRight;
		delete temp;
		return;
	}
	if (pRoot->pRight == NULL)
	{
		pRoot = pRoot->pLeft;
		delete temp;
		return;
	}
	else
	{
		int themang = getMax(pRoot->pLeft);
		pRoot->key = themang;
		Remove(pRoot->pLeft, themang);
	}
}

//12. Initialize a Binary Search Tree from a given array :
BSTNode* createTree(int a[], int n)
{
	BSTNode* New_tree = NULL;
	for (int i = 0; i < n; i++)
		Insert(New_tree, a[i]);
	return New_tree;
}

//13. Completely remove a given Binary Search Tree :
void removeTree(BSTNode*& pRoot)
{
	if (pRoot == NULL)
		return;
	removeTree(pRoot->pLeft);
	removeTree(pRoot->pRight);
	delete pRoot;
}

//14. Calculate the height of a NODE with given value : (return -1 if value not exist)
int heightNode(BSTNode* pRoot, int value)
{
	if (pRoot == NULL)
		return -1;
	if (pRoot->key == value)
		return Height(pRoot);
	int Left = heightNode(pRoot->pLeft, value);
	int Right = heightNode(pRoot->pRight, value);
	if (Left == -1 && Right == -1)
		return -1;
	return max(Left, Right);	
}

//15. * Calculate the level of a given NODE :
int Level(BSTNode* pRoot, BSTNode* p)
{
	if (pRoot == NULL)
		return -1;
	if (p == NULL)
		return -1;
	if (pRoot == p)
		return 1;
	int Left = Level(pRoot->pLeft, p);
	int Right = Level(pRoot->pRight, p);
	if (Left == -1 && Right == -1)
		return -1;
	return 1 + max(Left, Right);
}

//16. * Count the number leaves from a given Binary Tree :
int countLeaf(BSTNode* pRoot)
{
	if (pRoot == NULL)
		return 0;
	if (pRoot->pLeft == NULL && pRoot->pRight == NULL)
		return 1;
	
	int L_Leaf = countLeaf(pRoot->pLeft);
	int R_Leaf = countLeaf(pRoot->pRight);
	return L_Leaf + R_Leaf;
}

//17. * Count the number of NODE from a given Binary Search Tree which key value is less than a given value :
int countLess(BSTNode* pRoot, int x)
{
	if (pRoot == NULL)
		return 0;
	return (pRoot->key < x) + countLess(pRoot->pLeft, x) + countLess(pRoot->pRight, x);
}

//18. * Count the number of NODE from a given Binary Search Tree which key value is greater than a given value :
int countGreater(BSTNode* pRoot, int x)
{
	if (pRoot == NULL)
		return 0;
	int l = countGreater(pRoot->pLeft, x);
	int r = countGreater(pRoot->pRight, x);
	if (pRoot->key > x)
		return 1 + l + r;
	else
		return l + r;
}


//19. * Determine if a given Binary Tree is Binary Search Tree :
int max_value(BSTNode* pRoot);
int min_value(BSTNode* pRoot);
bool isBST(BSTNode* pRoot)
{
	if (pRoot == NULL)
		return 1;
	if (pRoot->pLeft && max_value(pRoot->pLeft) > pRoot->key)
		return 0;
	if (pRoot->pRight && min_value(pRoot->pRight) < pRoot->key)
		return 0;

	return isBST(pRoot->pLeft) && isBST(pRoot->pRight);
}

//20. * Determine if a given Binary Tree is a Full Binary Search Tree :
bool isFullBST(BSTNode* pRoot)
{
	if (pRoot == NULL)
		return 1;
	if (!isBST(pRoot))
		return 0;
	int h = Height(pRoot);
	int LeafOfTree = countLeaf(pRoot);
	if (LeafOfTree == pow(2, h - 1))
		return 1;
}

void print_i_level(BSTNode* proot, int i)
{
	if (proot == NULL) return;
	if (i == 1)
		cout << proot->key << ' ';
	if (i > 1)
	{
		print_i_level(proot->pLeft, i - 1);
		print_i_level(proot->pRight, i - 1);
	}
}

int getMax(BSTNode* pRoot)
{
	if (pRoot->pRight == NULL)
		return pRoot->key;
	return getMax(pRoot->pRight);
}

int max_value(BSTNode* pRoot)
{
	if (pRoot == NULL)
		return INT_MIN;
	int val = pRoot->key;
	int L_max = max_value(pRoot->pLeft);
	int R_max = max_value(pRoot->pRight);

	return max(val, max(L_max, R_max));
}

int min_value(BSTNode* pRoot)
{
	if (pRoot == NULL)
		return INT_MAX;
	int val = pRoot->key;
	int L_min = min_value(pRoot->pLeft);
	int R_min = min_value(pRoot->pRight);

	return min(val, min(L_min, R_min));
}






int main()
{
	int a[] = { 10,6,18,4,8,14,25,3,5,7,9,12,16,23,27,40,29,52 };
	int na = sizeof(a) / sizeof(int);
	BSTNode* tree = NULL;
	// nếu duyệt thứ tự đúng như mong đợi: Hàm Insert và hàm CreateTree đúng
	tree = createTree(a, na);
	/*
						 _10_
					   /      \
					  /        \
					 /          \
				    6            18
				  /  \          /  \
				 /    \        /    \
				4      8      14    25
			   / \    / \    / \    / \
			  3   5  7   9  12 16  23 27
				 			   		   \
							   		   40
							   		   / \
							   		  29 52

	*/
	//kết quả mong đợi sau khi duyệt cây: 10 6 4 3 5 8 7 9 18 14 12 16 25 23 27 40 29 52
	cout << "NLR: ";
	NLR(tree);
	cout << endl;
	// kết quả duyệt mong đợi: 3 4 5 6 7 8 9 10 12 14 16 18 23 25 27 29 40 52
	cout << "LNR: ";
	LNR(tree);
	cout << endl;
	//Kết quả duyệt mong đợi: 3 5 4 7 9 8 6 12 16 14 23 29 52 40 27 25 18 10
	cout << "LRN: ";
	LRN(tree);
	cout << endl;
	//kết quả duyệt mong đợi: 10 6 18 4 8 14 25 3 5 7 9 12 16 23 27 40 29 52
	cout << "Level Order: ";
	LevelOrder(tree);
	cout << endl;

	//Chiều cao cây: 6
	cout << "Height: " << Height(tree) << endl;
	// Số node: 18
	cout << "Number of Node: " << countNode(tree) << endl;
	//SUM: 308
	cout << "SUM Node: " << sumNode(tree) << endl;
	//Search node: 16
	cout << "Search node value: " << Search(tree, 16)->key << endl;

	//Remove Node 40
	//Remove(tree, 40);
	//cout << "Remove node have value: 40." << endl;
	////kết quả mong đợi sau khi duyệt cây: 10 6 4 3 5 8 7 9 18 14 12 16 25 23 27 29 52
	//cout << "NLR: ";
	//NLR(tree);
	//cout << endl;
	//// kết quả duyệt mong đợi: 3 4 5 6 7 8 9 10 12 14 16 18 23 25 27 29 52
	//cout << "LNR: ";
	//LNR(tree);
	//cout << endl;
	////kết quả duyệt mong đợi: 10 6 18 4 8 14 25 3 5 7 9 12 16 23 27 29 52
	//cout << "Level Order: ";
	//LevelOrder(tree);
	//cout << endl;
	/*
						 _10_
					   /      \
					  /        \
					 /          \
					6            18
				  /  \          /  \
				 /    \        /    \
				4      8      14    25
			   / \    / \    / \    / \
			  3   5  7   9  12 16  23 27
									   \
									   29
									     \
									     52

	*/

	//Remove Tree:
	//kết quả mong đợi: không in ra bất cứ giá trị nào
	/*cout << "Remove tree:" << endl;
	removeTree(tree);
	cout << "NLR: ";
	NLR(tree);*/
	
	//in chiều cao của node có giá trị 15 và 40
	/*cout << "Height of Node have 40-value and 15-value: " << heightNode(tree, 40) << " and " << heightNode(tree, 15) << endl;*/
	//in mức của node có giá trị 15 và 40
	/*cout << "Level of Node have 40-value and 15-value: " << Level(tree, Search(tree, 40)) << " and " << Level(tree, Search(tree, 15)) << endl;*/

	//Số lá của cây: 9
	cout << "Number leaves of tree: " << countLeaf(tree) << endl;
	//số node có value nhỏ hơn 19: 12
	cout << "Number of Node have value less than 19: " << countLess(tree, 19) << endl;
	//số node có value lớn hơn 19: 6
	cout << "Number of Node have value greater than 19: " << countGreater(tree, 19) << endl;
	//is BST: cây tree
	cout << "tree is BST: " << isBST(tree) << endl;
	// is BST: cây ctree
	BSTNode* temp1 = createNode(10);
	BSTNode* temp2 = createNode(15);
	BSTNode *ctree= new BSTNode;
	ctree->key = 5;
	ctree->pLeft = temp1;
	ctree->pRight = temp2;
	cout << "ctree is BST: " << isBST(ctree) << endl;
	//Cây full: 
	/*
						 _10_
					   /      \
					  /        \
					 /          \
					6            18
				  /  \          /  \
				 /    \        /    \
				4      8      14    25
			   / \    / \    / \    / \
			  3   5  7   9  12 16  23 27
									   

	*/
	int b[] = { 10,6,18,4,8,14,25,3,5,7,9,12,16,23,27 };
	BSTNode* full = createTree(b, sizeof(b) / sizeof(int));
	cout << "Is full BST: " << isFullBST(full) << endl;
	//Isn't Full BST
	cout << "Is full BST: " << isFullBST(tree) << endl;


	return 1;
}


