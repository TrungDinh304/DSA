// 21ctt3_graph.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
//các câu trên tương tự đề nhóm B và C ở đây chỉ code câu 3

#include <iostream>
#include<vector>
#include<queue>
using namespace std;


//chuyển cạnh thành đồ thị vô hướng
int** convertAdjacencyMatrix(vector<vector<int>> edges, int n)
{
	int** result = new int* [n];
	for (int i = 0; i < n; i++)
	{
		result[i] = new int[n] {};
	}

	for (vector<int> i : edges)
	{
		result[i[0]][i[1]] ++;
		result[i[1]][i[0]] ++;
	}
	return result;
}


void printMatrix(int** a, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << ' ';
		cout << endl;
	}
}





void DFSbefore(int** a, int n, int src, bool* vistted, int*before)
{
	vistted[src] = 1;
	for (int i = 0; i < n; i++)
	{
		if (a[src][i] && vistted[i] == 0)
		{
			before[i] = src;
			DFSbefore(a, n, i, vistted, before);
		}
	}

}


int* answer(vector<vector<int>> edges, int n)
{
	int* result = new int[n]{};
	int** a = convertAdjacencyMatrix(edges, n);
	printMatrix(a, n);
	bool* visitted = new bool[n] {};
	int* before = new int[n];


	
	for (int k = 0; k < n; k++)
	{
		int sum = 0;
		for (int j = 0; j < n; j++)
		{
			visitted[j] = 0;
			before[j] = -1;
		}
		DFSbefore(a, n, k, visitted, before);
		/*cout << "[" << k << "]: ";
		for (int j = 0; j < n; j++)
			cout << before[j] << ' ';
		cout << endl;*/
		for (int j = 0; j < n; j++)
		{
			int temp = j;
			while (before[temp] >= 0)
			{
				temp = before[temp];
				sum++;
			}
		}
		result[k] = sum;
	}
	return result;
}


int main()
{
	/*vector<vector<int>> edges = {
		{0,1},
		{0,2},
		{2,3},
		{2,4},
		{2,5},
	};*/
	vector<vector<int>> edges = {
		{0,1},
		{0,2},
		{2,5},
		{1,4},
		{1,3},
	};
	int n = 6;


	int* a = answer(edges, n);
	for (int i = 0; i < n; i++)
		cout << a[i] << ' ';


	return 0;

}

