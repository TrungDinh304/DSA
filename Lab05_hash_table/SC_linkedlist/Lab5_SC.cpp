#include <iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
using namespace std;

#define m 1000000009
#define p 31

struct Company
{
    string name;
    string tax_code;
    string address;
};

struct ListNode {
	Company key;
	ListNode* pNext;
};


struct List {
	ListNode* pHead = NULL;
	ListNode* pTail = NULL;
};


ListNode* createNode(Company data)
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
bool addTail(List& L, Company data)
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


Company Lineinfor(string line)
{
	stringstream S(line);
	Company result;
	getline(S, result.name, '|');
	getline(S, result.tax_code, '|');
	getline(S, result.address, '|');
	return result;
}

vector<Company> ReadCompanyList(string file_name)
{
	vector<Company> list;
	ifstream fin;
	fin.open(file_name);
	if (!fin.is_open())
	{
		cout << "==Loi mo file.==" << endl;
		return list;
	}
	Company temp;
	string buffer;
	getline(fin, buffer);
	while (!fin.eof())
	{
		getline(fin, buffer);
		temp = Lineinfor(buffer);
		list.push_back(temp);
	}
	fin.close();
	return list;
}


void writefile(string file_name, List* list, int n)
{
	ofstream fout;
	fout.open(file_name);
	if (!fout.is_open())
	{
		cout << "==Mo file ghi that bai.==" << endl;
		return;
	}
	fout << "Ten cong ty|MST|Dia chi" << endl;
	for (int i = 0; i < n; i++)
	{
		ListNode* cur = list[i].pHead;
		while (cur != NULL)
		{
			fout << cur->key.name << ' ' << i << endl;
			cur = cur->pNext;
		}
	}
	fout.close();
}


long long HashString(string company_name)
{
	long long hash = 0;
	int company_size = company_name.size();
	string substring = company_name;
	if (company_size > 20)
	{
		substring = company_name.substr(company_size - 20, 20);
	}
	for (int i = 0; i < substring.size(); i++)
	{
		//hash += (((long long)int(substring[i]) % m) * pow_pWithMod(i)) % m;
		long long a = 0;
		a = (((long long)pow(p, i / 2) % m) * ((long long)pow(p, i / 2 + (i % 2)) % m)) % m;
		hash += (((long long)int(substring[i]) % m) * a) % m;

	}

	return hash % m;
}


List* CreateHashTable(vector<Company> list_company)
{
	int n = 2000;
	int list_size = list_company.size();
	List* hashtable = new List[n];
	for (int i = 0; i < list_size; i++)
	{
		long long hashx = HashString(list_company[i].name);
		long long index = hashx % n;
		addTail(hashtable[index], list_company[i]);
	}
	return hashtable;
}







int main()
{
	vector<Company> list;
	list = ReadCompanyList("MST.txt");

	List* Hash = CreateHashTable(list);
	writefile("output.txt", Hash, 2000);
	return 0;
}
