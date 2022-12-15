#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>
#include<queue>

using namespace std;


// Các hàm đọc file, in ma trận, in danh sách, chuyển đổi ma trận thành danh sách kề và ngược lại
//===============================================================================================
//Đọc file lấy ma trận kề
int** readMatrix(char* filename, int& n)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Loi mo file.!!!\n";
		n = 0;
		return NULL;
	}

	fin >> n;
	int** a = new int* [n];

	for (int i = 0; i < n; i++)
	{
		a[i] = new int[n];
		for (int j = 0; j < n; j++)
			fin >> a[i][j];
	}
	return a;
}

//đọc các đỉnh kề của 1 đỉnh
vector<int> Listline(string line)
{
	vector<int>a;
	if (line.empty()) return a;
	stringstream S(line);
	while (!S.eof())
	{
		string buffer;
		getline(S, buffer, ' ');
		a.push_back(stoi(buffer));
	}
	return a;
}
//đọc file lấy danh sách kề
vector<int>* readList(char* filename, int& n)
{
	ifstream fin;
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Loi mo file.!!!\n";
		n = 0;
		return NULL;
	}
	string t;
	getline(fin, t);
	n = stoi(t);
	vector<int>* a = new vector<int>[n];
	for (int i = 0; i < n; i++)
	{
		string buffer;
		getline(fin, buffer);
		a[i] = Listline(buffer);
	}
	return a;
}


//chuyển đổi ma trận kề thành danh sách kề
vector<int>* MatrixToList(int** a, int na,int &nb)
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
//chuyển đổi danh sách kề thành ma trận kề
int** List_toMatrix(vector<int>* a, int n)
{
	if (a == NULL || n == 0) return NULL;
	int** result = new int* [n];

	for (int i = 0; i < n; i++)
	{
		result[i] = new int[n] {};
		for (int j = 0; j < a[i].size(); j++)
			result[i][a[i][j]] ++;
	}
	return result;
}

//in ma trận
void printMatrix(int** a, int n)
{
	if (a == NULL || n == 0)return;
	cout << "\nMatrix " << n << " X " << n << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "[" << i << "]: ";
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}
//in danh sách kề
void printlist(vector<int>* a, int n)
{
	cout << "\nList with " << n << "  vertices." << endl;
	for (int i = 0; i < n; i++)
	{
		cout << "[" << i << "]: ";
		int nai = a[i].size();
		for (int j = 0; j < nai; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}

//hàm in danh sách cạnh của đồ thị
void print_EdgeList(vector<pair<int, int>>list)
{
	cout << "Edge list cua do thi: " << endl;
	int n = list.size();
	for (int i = 0; i < n; i++)
		cout << "<" << list[i].first << ',' << list[i].second << ">" << endl;		
}


//in danh sách vector<vector<int>>
void printListvector_2(vector<vector<int>>list)
{
	int n = list.size();
	for (int i = 0; i < n; i++)
	{
		int len = list[i].size();
		cout << "\t[" << i << "]: ";
		for (int j = 0; j < len; j++)
		{
			cout << list[i][j] << ' ';
		}
		cout << endl;
	}
}
//=============================================================================================





//Câu 3:
// ============================================================================================
// 
// Directed or Undirected Graph.
// ----------------------------------------------------------------------
//hàm kiểm tra ma trận có hướng
//trả về 1: có hướng.
//trả về 0: vô hướng
bool Direction(int** a, int n)
{
	if (a == NULL || n == 0) return 0;

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			if (a[i][j] != a[j][i])
				return 1;
	return 0;
}
//-----------------------------------------------------------------

//The number of edges and number of vertices.
// ----------------------------------------------------------------
//hàm trả về số đỉnh của ma trận kề
int No_vertices(int** a, int n)
{
	return n;
}

//hàm trả về số cạnh của ma trận kề
int No_edges(int** a, int n)
{
	//nếu độ thị có hướng thì duyệt hết ma trận 
	if (Direction(a, n))
	{
		int count = 0;
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				count += a[i][j];
		return count;
	}
	//nếu đồ thị vô hướng thì chỉ xét một nữa ma trận trên từ đường chéo chính
	int count = 0;
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			count += a[i][j];
	return count;
}

//----------------------------------------------------------------------------------------------


//Degree of each vertices for undirected graph. In-degree and Out-degree for directed graph.
// ----------------------------------------------------------------------------------------------
//trả về mảng động lưu danh sách bậc của các đỉnh của đồ thị vô hướng
int* List_degree_undirected(int** a, int n)
{
	if (a == NULL || n == 0) return NULL;
	int* result = new int[n];
	int count = 0;
	for (int i = 0; i < n; i++)
	{
		count = 0;
		for (int j = 0;j < n; j++)
			count += a[i][j];
		result[i] = count;
	}
	return result;
}

//trả về danh sách bậc trong bậc ngoài của đồ thị có hướng
//trả về vector pair gồm 2 phần tử, phần tử thứ nhất trả về bậc ngoài, p tử thứ 2 trả về bật trong
pair<int, int>* List_degree_directed(int** a, int n)
{
	if (a == NULL || n == 0) return NULL;
	pair<int, int>* result = new pair<int, int>[n];
	int count_out = 0, count_in = 0;
	for (int i = 0; i < n; i++)
	{
		count_out = 0;
		//đếm dòng để tìm bậc ngoài 
		for (int j = 0; j < n; j++)
		{
			count_out += a[i][j];
		}
		count_in = 0;
		//đếm cột tìm bậc trong
		for (int j = 0; j < n; j++)
		{
			count_in += a[j][i];
		}
		result[i] = { count_out,count_in };		
	}
	return result;
}
//----------------------------------------------------------------------------------------

//• List of isolated vertices / leaf vertices.
//----------------------------------------------------------------------------------------
//trả về mảng các đỉnh cô lập
vector<int>iso_vertices(int** a, int n)
{
	vector<int>result;
	if (a == NULL || n == 0) return result;

	pair<int, int>* temp = List_degree_directed(a, n);
	for (int i = 0; i < n; i++)
	{
		if (temp[i].first + temp[i].second == 0)
			result.push_back(i);
	}
	return result;
}

//trả về mảng các đỉnh treo
vector<int>leaf_vertices(int** a, int n)
{
	vector<int> result;
	if (a == NULL || n == 0) return result;

	pair<int, int>* temp = List_degree_directed(a, n);

	if (Direction(a, n))
	{
		for (int i = 0; i < n; i++)
		{
			if (temp[i].first + temp[i].second == 1)
				result.push_back(i);
		}
	}
	else
	{
		for (int i = 0; i < n; i++)
		{
			if (temp[i].first + temp[i].second == 2)
				result.push_back(i);
		}
	}
	return result;
}
//--------------------------------------------------------------------------





// • Is the given graph special: Complete graph, Circular graph, Bigraph, Complete bigraph
//---------------------------------------------------------------------------
//kiểm tra xem đồ thị có phải là đồ thị K đủ hay không
bool isCompleteGraph(int** a, int n)
{
	if (a == NULL || n == 0)
		return 1;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i != j)
			{
				if (a[i][j] != 1)
					return 0;
			}
			else if (i == j)
				if (a[i][j] != 0)
					return 0;
		}
	}
	return 1;
}


//kiểm tra đồ thị có phải đồ thị lưỡng phân hay không
//sử dụng phương pháp tô màu
//các đỉnh kề nhau thì không cùng màu với nhau
bool isBigraph(int** a, int n, int first = 0)
{
	int* color = new int[n];
	//đỉnh i chưa được tô màu có giá trị bằng -1
	for (int i = 0; i < n; i++)
		color[i] = -1;
	color[first] = 1;

	queue<int> travel;
	travel.push(first);


	while(!travel.empty())
	{
		int i = travel.front();
		travel.pop();


		if (a[i][i] != 0)
		{
			delete[]color;
			return 0;
		}
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] != 0 && color[j] == -1)
			{
				color[j] = 1 - color[i];
				travel.push(j);
			}
			if (a[i][j] != 0 && color[i] == color[j])
			{
				delete[]color;
				return 0;
			}
		}
	}
	delete[]color;
	return 1;
}


//hàm kiểm tra đồ thị lưỡng phân đủ
//là đồ thị lưỡng phân mà có số cạnh = số đỉnh màu n * số đỉnh màu m
//Ở đây hàm chỉ xét với đồ thị đơn vô hướng.
bool isComplete_BiGraph(int** a, int n, int first = 0)
{
	int* color = new int[n];
	//đỉnh i chưa được tô màu có giá trị bằng -1
	for (int i = 0; i < n; i++)
		color[i] = -1;
	color[first] = 1;

	queue<int> travel;
	travel.push(first);


	while (!travel.empty())
	{
		int i = travel.front();
		travel.pop();


		if (a[i][i] != 0)
			return 0;
		for (int j = 0; j < n; j++)
		{
			if (a[i][j] > 1)
				return 0;
			if (a[i][j] != 0 && color[j] == -1)
			{
				color[j] = 1 - color[i];
				travel.push(j);
			}
			if (a[i][j] != 0 && color[i] == color[j])
				return 0;
		}
	}

	int color0 = 0;
	int color1 = 0;
	for (int i = 0; i < n; i++)
	{
		if (color[i] == 1)
			color1++;
		else if (color[i] == 0)
			color0++;
	}
	delete[]color;
	int sumedge = No_edges(a, n);
	return sumedge == color0 * color1;
}

//kiểm tra xem đồ thị có phải đồ thị vòng hay không 
//đồ thị vòng có:\
	-số cạnh = số đỉnh\
  	-Nếu đồ thị vô hướng thị mỗi đỉnh có bậc đúng = 2 \
	-Nếu đồ thị có hướng thì mỗi đỉnh có bậc trong = bậc ngoài = 1
int No_connectedComponent(vector<int>* list, int n, bool* visitted = NULL);
bool isCircularGraph(int** a, int n)
{
	if (No_edges(a, n) != n)
		return 0;
	int nlist = 0;
	vector<int>* list = MatrixToList(a, n, nlist);
	if (No_connectedComponent(list, nlist) > 1)
		return 0;
	//đối với đồ thị có hướng
	if (Direction(a, n))
	{
		pair<int, int>* degree = List_degree_directed(a, n);
		for (int i = 0; i < n; i++)
		{
			if (degree[i].first != 1 || degree[i].second != 1)
				return 0;
		}
		return 1;
	}
	//đối với đồ thị đơn vô hướng
	else
	{
		int* degree = List_degree_undirected(a, n);
		for (int i = 0; i < n; i++)
		{
			if (degree[i] != 2)
				return 0;
		}
		return 1;
	}
}

//--------------------------------------------------------------------------------------------------


//The number of Connected components. How many of them are trees?
//--------------------------------------------------------------------------------------------------
int No_connectedComponent(vector<int>* list, int n, bool* visitted)
{
	if (list == NULL || n == 0)return 0;

	//mảng động lưu trạng thái của các đỉnh
	//tại vị trí các đỉnh chưa đi qua sẽ có giá trị bằng 0
	if (visitted == NULL)
		visitted = new bool[n] {};
	//số đỉnh đã đi qua
	int Visitted_vertices = 0;
	for (int i = 0; i < n; i++)
		Visitted_vertices += visitted[i];

	//số thành phần liên thông
	int connection_com = 0;

	while (Visitted_vertices < n)
	{
		for (int i = 0; i < n; i++)
		{
			if (visitted[i] == 0)
			{
				visitted[i] = 1;
				Visitted_vertices++;
				queue<int> travels;
				travels.push(i);
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
							Visitted_vertices++;
						}
					}
				}
				connection_com++;
			}
		}
	}
	return connection_com;
}


//Thuật toán BFS để tìm thành phần liên thông
vector<int> BFS_Connected(vector<int>* list, int n, int vertex, bool* visitted, int &Visitted_vertices)
{
	vector<int>result;
	visitted[vertex] = 1;
	result.push_back(vertex);
	Visitted_vertices++;
	queue<int> travels;
	travels.push(vertex);
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
vector<vector<int>>connection_Component_BFS(vector<int>* list, int n)
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
				vector<int> component = BFS_Connected(list, n, i, visitted, Visitted_vertices);
				result.push_back(component);
			}
		}
	}
	delete[]visitted;
	return result;
}

//Thuật toán DFS để tìm thành phần liên thông
vector<int> DFS(vector<int>* list, int n, bool* visitted, int cur_vertex,int &visited_vertex)
{
	vector<int> travel;
	travel.push_back(cur_vertex);
	visitted[cur_vertex] = 1;
	visited_vertex++;
	for (int i = 0; i < list[cur_vertex].size(); i++)
	{
		if (visitted[list[cur_vertex][i]] == 0)
		{
			vector<int> a = DFS(list, n, visitted, list[cur_vertex][i],visited_vertex);
			travel.insert(travel.end(), a.begin(), a.end());
		}
	}
	return travel;
}

//trả về các thành phần liên thông của đồ thị thông qua thuật toàn DFS
vector<vector<int>>connection_Component_DFS(vector<int>* list, int n)
{
	vector<vector<int>>result;
	bool* visitted = new bool[n] {};
	int Visitted_vertex = 0;
	while (Visitted_vertex < n)
	{
		for (int i = 0; i < n; i++)
		{
			if (visitted[i] == 0)
			{
				vector<int> component = DFS(list, n, visitted, i, Visitted_vertex);
				result.push_back(component);
			}
		}
	}
	delete[]visitted;
	return result;
}



//hàm trả về các thành phần liên thông là cây của đồ thị có hướng
vector<vector<int>> Tree_C_Component_Direc(vector<int>* list, int n)
{
	vector<vector<int>>comp_list = connection_Component_DFS(list, n);
	vector<vector<int>> result;
	int numof_conne_comp = comp_list.size();
	for (int i = 0; i < numof_conne_comp; i++)
	{
		vector<int>edge;
		int len = comp_list[i].size();
		for (int j = 0; j < len; j++)
		{
			int len_aj_Of_vert = list[comp_list[i][j]].size();
			for (int k = 0; k < len_aj_Of_vert; k++)
			{
				edge.push_back(list[comp_list[i][j]][k]);
			}
		}
		int len_of_edge = edge.size();
		bool* apear = new bool[len_of_edge] {};
		for (int j = 0; j < len_of_edge; j++)
		{
			for (int k = 0; k < len; k++)
			{
				if (edge[j] == comp_list[i][k])
					apear[j] = 1;
				break;
			}
		}
		int No_edge_comp = 0;
		for (int j = 0; j < len_of_edge; j++)
			No_edge_comp += apear[j];
		int** mtrix = List_toMatrix(list, n);

		if (No_edge_comp == len - 1)
		{
			result.push_back(comp_list[i]);
		}		
		
		delete[]apear;
	}
	return result;
}
//hàm trả về các thành phần liên thông là cây của đồ thị vô hướng
vector<vector<int>> Tree_C_Component_UnDirec(vector<int>* list, int n)
{
	vector<vector<int>>con_comp_list = connection_Component_DFS(list, n);
	vector<vector<int>> result;
	int numof_conne_comp = con_comp_list.size();
	for (int i = 0; i < numof_conne_comp; i++)
	{
		int len_con_compi = con_comp_list[i].size();
		vector<int>edge;
		for (int j = 0; j < len_con_compi; j++)
		{
			int len_aj_Of_vert = list[con_comp_list[i][j]].size();
			for (int k = 0; k < len_aj_Of_vert; k++)
			{
				edge.push_back(list[con_comp_list[i][j]][k]);
			}
		}
		if (edge.size() == len_con_compi * 2 - 2)
			result.push_back(con_comp_list[i]);
	}
	return result;
}

//tổng hợp của 2 hàm đếm số cây trong các thành phần liên thông vô hướng và có hướng
vector<vector<int>> Tree_C_Component(vector<int>* list, int n)
{
	int** matrix = List_toMatrix(list, n);
	vector<vector<int>>result;
	if (Direction(matrix, n))
	{
		result = Tree_C_Component_Direc(list, n);
	}
	else
		result = Tree_C_Component_UnDirec(list, n);
	for (int i = 0; i < n; i++)
		delete[]matrix[i];
	delete[]matrix;
	return result;		
}
//----------------------------------------------------------------------------------------------------------------------





//The number of Cut vertices and Bridge edges.
//--------------------------------------------------------------------------------------------------------------------

//trả về danh sách các đỉnh treo của đồ thị
vector<int> Cut_vertices(vector<int>* list, int n)
{
	//số thành phần liên thông ban đầu lúc chưa xóa đỉnh nào 
	int inital_connected_comp = No_connectedComponent(list, n);
	//tạo mảng đánh dấu các đỉnh đã đi qua
	bool* visitted = new bool[n] {};
	vector<int>cut_vertices;

	//
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			visitted[j] = false;
		visitted[i] = true;
		int connected_comp_Skipi = No_connectedComponent(list, n, visitted);
		if (connected_comp_Skipi > inital_connected_comp)
			cut_vertices.push_back(i);
	}
	delete[]visitted;
	return cut_vertices;
}

//trả về danh sách cạnh từ danh sách kề
vector<pair<int, int>>Edge_List(vector<int>* list, int n)
{
	vector<pair<int, int>>result;
	for (int i = 0; i < n; i++)
	{
		int len_li = list[i].size();
		for (int j = 0; j < len_li; j++)
		{
			result.push_back({ i,list[i][j] });
		}
	}
	return result;
}


//Hàm trả về danh sách cạnh cầu của đồ thị
vector<pair<int, int>>Brige_Edge(vector<int>* list, int n)
{
	int inital_connected_comp = No_connectedComponent(list, n);
	vector<pair<int, int>>result;
	vector<pair<int, int>>edge_list = Edge_List(list, n);
	int len_edgeList = edge_list.size();
	bool* visitted = new bool[n] {};

	//xét từng cạnh của đồ thị, duyệt BFS để tìm số tành phần liên thông của đồ thị khi xóa cạnh đó
	for (int i = 0; i < len_edgeList; i++)
	{
		//danh sách kề mới dùng để lưu danh sách khi xóa cạnh đang xét
		vector<int>* temp = new vector<int>[n];
		for (int j = 0; j < n; j++)
			temp[j] = list[j];

		//xóa cạnh thứ i ra khỏi danh sách kề 
		for (int j = 0; j < temp[edge_list[i].first].size(); j++)
		{
			if (temp[edge_list[i].first][j] == edge_list[i].second)
				temp[edge_list[i].first].erase(temp[edge_list[i].first].begin() + j);
		}
		//xóa cạnh thứ i ra khỏi danh sách kề 
		for (int j = 0; j < temp[edge_list[i].second].size(); j++)
		{
			if (temp[edge_list[i].second][j] == edge_list[i].first)
				temp[edge_list[i].second].erase(temp[edge_list[i].second].begin() + j);
		}


		//tái thiết lập trạng thái của các đỉnh về trạng thái chưa đi qua
		for (int j = 0; j < n; j++)
			visitted[j] = false;

		//tìm số thành phần liên thông của đồ thị sau khi xóa cạnh
		int connected_comp_skipEdge_i = No_connectedComponent(temp, n, visitted);

		//nếu số thành phần liên thông sau > số thành phần liên thông trước thì cạnh đó là cầu
		if (connected_comp_skipEdge_i > inital_connected_comp)
			result.push_back(edge_list[i]);
		//giải phóng vùng nhớ của danh sách sau khi sử dụng
		delete[]temp;
	}
	delete[]visitted;
	return result;
}









//--------------------------------------------------------------------------------------------------------------------






int main()
{

	//======================================TEST ĐÔ THỊ CÓ HƯỚNG=============================================
	int** a = NULL;
	int na = 0;
	
	//======== TEST CÂU 1 =====
	//đọc ma trận kề của đồ thị 1 từ file
	char graph1[] = "graph1.txt";
	a = readMatrix(graph1, na);
	//in ma trận vừa đọc được
	printMatrix(a, na);
	

	//test hàm chuyển ma trận kề thành danh sách kề
	int nb = 0;
	vector<int>* b = MatrixToList(a, na, nb);
	printlist(b, nb);


	//======= TEST  CÂU 2 =======
	//int m = 0;
	////đọc danh sách kề của đồ thị cho sẵn từ file
	//char graph2[] = "graph2.txt";
	//vector<int>* list_aj = readList(graph2,m);
	////in danh sách kề vừa đọc được
	//printlist(list_aj, m);
	//int nmatrix = m;
	////test hàm chuyển danh sách kề thành ma trận kề
	//int** matrix = List_toMatrix(list_aj, m);
	//printMatrix(matrix, m);


	//======= Câu 3 =======
	//kiểm tra ma trận là vô hướng hay có hướng
	if (Direction(a, na))
	{
		cout << "-Do thi vua doc la do thi co huong." << endl;
	}
	else
		cout << "-Do thi vua doc la do thi vo huong." << endl;
	//In ra số cạnh của đồ thị
	cout << "-Do thi co so canh: " << No_edges(a, na) << endl;

	//in ra danh sách bậc trong và bậc ngoài của đồ thị có hướng
	/*pair<int, int>* degree = List_degree_directed(a, na);
	for (int i = 0; i < na; i++)
	{
		cout << "[" << i << "]: ";
		cout << "Out-degree: " << degree[i].first << "; In-degree: " << degree[i].second << endl;
	}*/

	//in ra danh sách đỉnh cô lập của đồ thị
	vector<int> isolist1 = iso_vertices(a, na);
	cout << "-Cac dinh co lap trong do thi: (" << isolist1.size() << " dinh)." << endl << '\t';
	for (int i = 0; i < isolist1.size(); i++)
	{
		cout << isolist1[i] << ' ';
	}
	cout << endl;

	//in ra danh sách đỉnh treo của đồ thị
	vector<int> leaflist1 = leaf_vertices(a, na);
	cout << "-Cac dinh treo trong do thi: (" << leaflist1.size() << " dinh)." << endl << '\t';
	for (int i = 0; i < leaflist1.size(); i++)
	{
		cout << leaflist1[i] << ' ';
	}
	cout << endl;

	//test hàm kiểm tra các dạng đồ thị đặc biệt
	int complete[][4] = { {0, 1, 1, 1},
	   {1, 0, 1, 1},
	   {1, 1, 0, 1},
	   {1, 1, 1, 0}
	};
	int** G = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		G[i] = new int[4];
		for (int j = 0; j < 4; j++)
			G[i][j] = complete[i][j];
	}
	cout << "Graph G";
	printMatrix(G, 4);
	cout << "Graph G";
	printMatrix(G, 4);
	cout << "-Graph G is Circular graph: ";
	isCircularGraph(G, 4) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Complete graph: ";
	isCompleteGraph(G, 4) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Bigraph: ";
	isBigraph(G, 4, 0) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Complete-Bigraph: ";
	isComplete_BiGraph(G, 4, 0) ? cout << "Yes" : cout << "No";
	cout << endl;

	//test hàm BiGraph: kiểm tra xem đồ thị đó có phải là đồ thị lưỡng phân hay không từ một ma trận cho trước
	int A[][4] = { {0, 1, 0, 1},
				   {1, 0, 1, 0},
				   {0, 1, 0, 1},
				   {1, 0, 1, 0}
	};
	//						0
	//					  /   \
	//					1       2
	//					  \   /	
	//						3

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
			G[i][j] = A[i][j];
	}
	cout << "Graph G";
	printMatrix(G, 4);
	cout << "-Graph G is Circular graph: ";
	isCircularGraph(G, 4) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Complete graph: ";
	isCompleteGraph(G, 4) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Bigrap: ";
	isBigraph(G, 4, 0) ? cout << "Yes" : cout << "No";
	cout << endl;
	cout << "-Graph G is Complete-Bigraph: ";
	isComplete_BiGraph(G, 4, 0) ? cout << "Yes" : cout << "No";
	cout << endl;

	//Test hàm in trả về số thành phần liên thông của ma trận. ở đây ta xét liên thông 1 phía.
	cout << "-The number of connected components: " << No_connectedComponent(b, nb) << endl;

	//in ra các thành phần liên thông của đồ thị với 2 các duyệt đồ thị 
	cout << "-Cac thanh phan lien thong(BFS): " << endl;
	vector<vector<int>> connectioncomponent = connection_Component_BFS(b, nb);
	printListvector_2(connectioncomponent);


	cout << "-Cac thanh phan lien thong(DFS): " << endl;
	vector<vector<int>> connectioncomponent_DFS = connection_Component_DFS(b, nb);
	printListvector_2(connectioncomponent_DFS);


	vector<vector<int>> connection_comp_tree = Tree_C_Component(b, nb);
	//in ra số thành phần liên thông là cây và các thành phần liên thông đó.
	cout << "-So thanh phan lien thong la cay cua do thi: " << connection_comp_tree.size() << endl;
	cout << "\t Cac thanh phan lien thong la cay: " << endl;
	printListvector_2(connection_comp_tree);


	//danh sách các đỉnh khớp của đồ thị
	vector<int>cutV1 = Cut_vertices(b, nb);
	cout << "-Do thi co so Dinh Khop: " << cutV1.size() << endl << '\t';
	for (int i = 0; i < cutV1.size(); i++)
		cout << cutV1[i] << ' ';
	cout << endl;
	//danh sách các cầu của đồ thị
	vector<pair<int, int>>Bridge1 = Brige_Edge(b, nb);
	cout << "-Do thi co so canh cau: " << Bridge1.size() << endl;
	for (int i = 0; i < Bridge1.size(); i++)
		cout << "\t<" << Bridge1[i].first << ',' << Bridge1[i].second << ">" << endl;
	

	//=============================================================================================================================




	//==================================TEST ĐỒ THỊ VÔ HƯỚNG=================================================================
	char undirected[] = "Graph_undirected1.txt";
	int n_undi = 0;
	vector<int>* undirec = readList(undirected, n_undi);
	printlist(undirec, n_undi);
	int** matrix_undi = List_toMatrix(undirec, n_undi);
	printMatrix(matrix_undi, n_undi);
	if (Direction(matrix_undi, n_undi))
	{
		cout << "Do thi vua doc la do thi co huong." << endl;
	}
	else
		cout << "Do thi vua doc la do thi vo huong." << endl;


	cout << "Cac thanh phan lien thong(DFS): " << endl;
	vector<vector<int>> connectioncomponent_DFS2 = connection_Component_DFS(undirec, n_undi);
	printListvector_2(connectioncomponent_DFS2);



	vector<vector<int>> connection_comp_tree2 = Tree_C_Component(undirec, n_undi);
	cout << "So thanh phan lien thong la cay cua do thi: " << connection_comp_tree2.size() << endl;
	cout << "\t Cac thanh phan lien thong la cay: " << endl;
	printListvector_2(connection_comp_tree2);
	cout << "So canh cua do thi: " << No_edges(matrix_undi,n_undi) << endl;


	return 0;
}