#include<iostream>
#include<vector>
#include<fstream>
#include<string>
#include<queue>


using namespace std;

struct Animal
{
	string en;
	string vn;
	string ph;
	int loai;
};

struct AVLNode
{
	int key;
	AVLNode* pLeft;
	AVLNode* pRight;
	int height;
};

//struct list them vao de tao hash table
struct ListNode {
    Animal key;
    ListNode* pNext;
};


struct List {
    ListNode* pHead = NULL;
    ListNode* pTail = NULL;
};

//cau 1:
//================================================================
//1.1
//----------------------------------------------------------------
AVLNode* createNode(int data)
{
	AVLNode* Nw = new AVLNode;
	Nw->key = data;
	Nw->pLeft = Nw->pRight = NULL;
	Nw->height = 1;
	return Nw;
}

int Height(AVLNode* proot)
{
    if (proot == NULL)
        return 0;
    return proot->height;
}

void leftRotation(AVLNode*& proot)
{
    AVLNode* temp = proot;
    proot = proot->pRight;
    temp->pRight = proot->pLeft;
    proot->pLeft = temp;

    temp->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
    proot->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
}


void rightRotation(AVLNode*& proot)
{
    AVLNode* temp = proot;
    proot = proot->pLeft;
    temp->pLeft = proot->pRight;
    proot->pRight = temp;

    temp->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
    proot->height = max(Height(temp->pLeft), Height(temp->pRight)) + 1;
}

int get_Balance(AVLNode* p)
{
    if (p == NULL)
        return 0;
    return Height(p->pLeft) - Height(p->pRight);
}

//Add a node with given value x into a given AVL tree(Notify if the given value existed) :
void Insert(AVLNode*& pRoot, int x)
{
    if (pRoot == NULL)
    {
        AVLNode* add = createNode(x);
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

AVLNode* createAVL(int* arr, int n)
{
    AVLNode* tree = NULL;
    for (int i = 0; i < n; i++)
    {
        Insert(tree, arr[i]);
    }
    return tree;
}
//---------------------------------------------------------------------------


//1.2
//---------------------------------------------------------------------------

bool isAVL(AVLNode* pRoot)
{
    if (pRoot == NULL)
        return 1;
    if (get_Balance(pRoot) < -1 || get_Balance(pRoot) > 1)
        return 0;
    return isAVL(pRoot->pLeft) && isAVL(pRoot->pRight);
}
//-------------------------------------------------------------------------


void LNR(AVLNode* p)
{
    if (!p)
        return;
    LNR(p->pLeft);
    cout << p->key << ' ';
    LNR(p->pRight);
}

void NLR(AVLNode* p)
{

    if (!p)
        return;
    cout << p->key << ' ';
    NLR(p->pLeft);
    NLR(p->pRight);

}


//=================================================================



//Bai 2
//==================================================================





ListNode* createNode(Animal data)
{
    ListNode* newNode = new ListNode;
    newNode->key = data;
    newNode->pNext = NULL;
    return newNode;
}


bool IsEmptyList(List l)
{
    return l.pHead == NULL && l.pTail == NULL;
}


//4. Insert an integer to the tail of a given List:
bool addTail(List& L, Animal data)
{
    ListNode* add = createNode(data);
    if (add == NULL) return 0;
    if (IsEmptyList(L))
    {
        L.pHead = L.pTail = add;
        return 1;
    }
    L.pTail->pNext = add;
    L.pTail = add;
    return 1;
}

//2.1
//---------------------------------------------------------------------
vector<Animal> readAnimals(string filename)
{
    vector<Animal> result;
    ifstream fin;
    fin.open(filename);
    if (!fin)
    {
        cout << "Loi mo file." << endl;
        return result;
    }

    Animal buffer;
    while (!fin.eof())
    {
        getline(fin, buffer.en);
        getline(fin, buffer.ph);
        getline(fin, buffer.vn);
        string tloai;
        getline(fin, tloai);
        
        buffer.loai = stoi(tloai);
        
        result.push_back(buffer);
    }
    fin.close();
    return result;
}
//-------------------------------------------------------------------------------------

//2.2
//--------------------------------------------------------------------------------
List* Hash_table(vector<Animal>a, int& n)
{
    n = 'Z' - 'A' + 1;
    List* res = new List[n];
    for (Animal i : a)
    {
        int index = (int)i.en[0] - (int)'A';
        addTail(res[index], i);
    }
    return res;
}
//---------------------------------------------------------------------------------



//Bai 3:
//=================================================================================
//ham tra ve danh sach ke tu ma tran ke
vector<int>* MatrixToList(int** a, int na, int& nb)
{
    vector<int>* list = NULL;
    if (a == NULL || na == 0) return list;
    nb = na;
    list = new vector<int>[nb];
    for (int i = 0; i < nb; i++)
        for (int j = 0; j < nb; j++)
            if (a[i][j])
                list[i].push_back(j);
    return list;

}

//thuat toan BFS tim 1 thanh phan lien thong cua do thi qua cac dinh chua di qua
//mang visitted luu trang thai cua cac dinh: da di qua = 1 va chua di qua = 0
//Visitted_vertices luu so dinh da di qua de lam dieu kien dung cho thuan toan tim cac thanh phan lien thong
vector<int> BFS(vector<int>* list, int n, int vertex, bool* visitted, int& Visitted_vertices)
{
    vector<int>result;
    visitted[vertex] = 1;
    result.push_back(vertex);
    Visitted_vertices++;
    queue<int> travels;
    travels.push(vertex);
    //tien hanh di qua cac dinh cho den khi khong con dinh ke nao => het 1 thanh phan lien thong
    while (!travels.empty())
    {
        int k = travels.front();
        travels.pop();
        int n_aj = list[k].size();
        for (int j = 0; j < n_aj; j++)
        {
            if (visitted[list[k][j]] == 0)
            {
                travels.push(list[k][j]);
                visitted[list[k][j]] = 1;
                result.push_back(list[k][j]);
                Visitted_vertices++;
            }
        }
    }
    return result;
}


//trả về danh sách các thành phần liên thông của đồ thị 
vector<vector<int>>connection_Component(vector<int>* list, int n)
{
    //danh sách lưu kết quả các thanh phần liên thông
    vector<vector<int>>result;
    if (list == NULL || n == 0)return result;

    //mảng động lưu trạng thái của các đỉnh
    //tại vị trí các đỉnh chưa đi qua sẽ có giá trị bằng 0
    bool* visitted = new bool[n] {};
    //số đỉnh đã đi qua
    int Visitted_vertices = 0;

    while (Visitted_vertices < n)
    {
        for (int i = 0; i < n; i++)
        {
            if (visitted[i] == 0)
            {
                //dùng thuật toán BFS để tìm thành phần liên thông
                vector<int> component = BFS(list, n, i, visitted, Visitted_vertices);
                result.push_back(component);
            }
        }
    }
    delete[]visitted;
    return result;
}


int minimumEdges(int** graph, int n, int k)
{
    int res = 0;
    int nl = 0;
    //tao 1 danh sach ke de duyet BFS nhanh hon
    vector<int>* listke = MatrixToList(graph, n, nl);

    //danh sach cac thanh phan lien thong cua do thi
    vector<vector<int>>connected_comp = connection_Component(listke, nl);

    //xet tung thanh phan lien thong 
    int n_c_comp = connected_comp.size();
    for (int i = 0; i < n_c_comp; i++)
    {
        //so dinh cua thanh phan lien thong
        int vert = connected_comp[i].size();
        //do day la do thi don vo huong
        //so canh to da ma thanh phan lien thong co the tao ra tu dinh cua minh
        int maxEdge = vert * (vert - 1) / 2;
        int edge = 0;
        //tinh tong bac cua cac dinh trong thanh phan lien thong
        for (int j = 0; j < vert; j++)
        {
            edge += listke[j].size();
        }
        //so canh = tong bac/2
        edge /= 2;
        //sa canh toi thieu can them de so canh cua thanh phan lien thong chia het cho k
        int them = (k - edge % k) % k;
        //neu so canh cua thanh phan lien thong khong chia het cho k 
        //va so dinh toi thieu can them vao lai qua qui dinh thi ko the thuc hien => tra ve -1
        if (edge + them > maxEdge)
        {
            delete[] listke;
            return -1;
        }
        //cong don vao ket qua yeu cau
        res += them;
    }
    //giai phong vung nho list
    delete[] listke;
    return res;

}




int main()
{
    //mo comment de test ket qua
    //==================== TEST CAU 1 =============================
    /*int a[] = { 2,6,1,8,2,9,2,0,3 };
    int n = sizeof(a) / sizeof(int);
    AVLNode* t = createAVL(a, n);
    LNR(t); cout << endl;
    NLR(t); cout << endl;

    cout << "Cay T la cay AVL: ";
    if (isAVL(t))
        cout << "Yes." << endl;
    else
    {
        cout << "No." << endl;
    }*/



    //mo comment de test ket qua
    //=================== TEST CAU 2 ==================================
    /*string filename = "data.txt";
    vector<Animal>li = readAnimals(filename);
    int count = 0;
    for (auto j : li)
    {
        cout << count++ << ": ";
        cout << "English: " << j.en << endl;
        cout << "Phien am: " << j.ph << endl;
        cout << "Viet Nam: " << j.vn << endl;
        cout << "Loai: " << j.loai << endl << endl;
    }
    int n = 26;
    List* h = Hash_table(li, n);
    
    count = 0;
    cout << "==============================================" << endl;
    cout << "\t\tHASH TABLE" << endl;
    for (int i = 0; i < n; i++)
    {
        ListNode* c = h[i].pHead;
        while (c)
        {
            cout << count++ << "[index: " << i << "]: " << c->key.en << endl;
            c = c->pNext;
        }
        cout << "--------------------" << endl;
    }*/
   
    //mo comment de test ket qua
    //===================== TEST CAU 3 =====================
    /*int g[][7] = {
        {0,1,1,0,0,0,0},
        {1,0,0,0,0,0,0},
        {1,0,0,0,0,0,0},
        {0,0,0,0,1,1,1},
        {0,0,0,1,0,0,0},
        {0,0,0,1,0,0,1},
        {0,0,0,1,0,1,0}
    };
    int ng = 7;
    int** graph = new int* [ng];
    for (int i = 0; i < ng; i++)
    {
        graph[i] = new int[ng];
        for (int j = 0; j < ng; j++)
        {
            graph[i][j] = g[i][j];
            cout << graph[i][j] << ' ';
        }
        cout << endl;
    }
    
    int k = 2;
    cout << minimumEdges(graph, ng, k) << endl;*/


    return 0;
}





