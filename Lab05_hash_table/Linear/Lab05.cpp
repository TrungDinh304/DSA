#include <iostream>
#include <string>
#include <vector>
#include<fstream>
#include<sstream>
#include<math.h>
using namespace std;

#define m 1000000009
#define p 31

struct Company
{
	string name;
	string tax_code;
	string address;
};

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


void writefile(string file_name, Company* list, int n)
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
		fout << list[i].name << '|' << list[i].tax_code << '|' << list[i].address << endl;
	}
	fout.close();
}





//long long pow_pWithMod(int j)
//{
//	int a = j / 3;
//	int b = j / 3 + (j % 3 == 1);
//	int f = j / 3 + (j % 3 == 2);
//	long long c = (long long)pow(p, a) % m;
//	long long d = (long long)pow(p, b) % m;
//	long long g = (long long)pow(p, f) % m;
//	long long e = (c * d * g) % m;
//	return e;
//}



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

//// 2. Hash a string (company name) function
//long long HashString(string company_name)
//{
//	// long long positive integer
//	long long hash_num = 0;
//
//	// Take 20 last characters of company name to hash
//	 // if company name size < 20, take the whole company name to hash
//	string hash_str;
//	if (company_name.size() >= 20)
//	{
//		for (int i = 20; i >= 1; i--)
//			hash_str += company_name[company_name.size() - i];
//	}
//
//	else
//	{
//		hash_str = company_name;
//	}
//	// cout << hash_str << endl;
//	for (int i = 0; i < hash_str.size(); i++)
//	{
//		// pow(p , i) // Ex : (31^9) % m = ((31^4) % m * (31^5) % m) % m
//		long long power = 0;
//		power = (((long long)pow(p, i / 2) % m) * ((long long)pow(p, i / 2 + (i % 2)) % m)) % m;
//
//		hash_num += (((long long)int(hash_str[i]) % m) * power) % m;
//	}
//	return hash_num % m;
//}



Company* CreateHashTable(vector<Company> list_company)
{
	int n = 2000;
	int list_size = list_company.size();
	Company* Hashtable = new Company[n];
	for (int i = 0; i < list_size; i++)
	{
		long long hashx = HashString(list_company[i].name);
		long long index = hashx % n;
		int solandungdo = 0;
		while (!Hashtable[index].name.empty())
		{
			solandungdo++;
			index = ((hashx % n) + solandungdo) % n;
			if (solandungdo >= 2000)
				return Hashtable;
		}
		
		Hashtable[index] = list_company[i];
	}
	return Hashtable;
}


void Insert(Company* hash_table, Company company)
{
	int n = 2000;
	long long hash_co = HashString(company.name);
	long long index = hash_co % n;
	int solandungdo = 0;
	while (!hash_table[index].name.empty())
	{
		solandungdo++;
		index = ((hash_co % n) + ((solandungdo) % n)) % n;
		if (solandungdo >= 2000)
			return;
	}
	hash_table[index] = company;	
}



Company* Search(Company* hash_table, string company_name)
{
	if (hash_table == NULL)
		return NULL;

	int n = 2000;
	long long hash_co = HashString(company_name);
	long long index = hash_co % n;
	int solandungdo = 0;
	while (!hash_table[index].address.empty())
	{
		if (hash_table[index].name == company_name)
			return &hash_table[index];
		solandungdo++;
		index = ((hash_co % n) + solandungdo) % n;
		
		if (solandungdo >= 2000)
			return NULL;
	}
	return NULL;
}


int main()
{
	vector<Company> list;
	list = ReadCompanyList("MST.txt");
	
	Company* Hash = CreateHashTable(list);
	int count = 0;
	for (int i = 0; i < 2000; i++)
		if (!Hash[i].name.empty())
			count++;
	cout << "Hash table have " << count << " Company." << endl;
	writefile("output.txt", Hash, 2000);
	Company* a = Search(Hash, "CONG TY TNHH CO DIEN LANH SLINE VIET NAM");
	if (a == NULL)
		cout << "khong thay\n";
	else
		cout << a->name << '|' << a->tax_code << '|' << a->address << endl;
	Company b;
	b.name = "1";
	b.address = "2";
	b.tax_code = "3";
	Insert(Hash, b);
	count = 0;
	for (int i = 0; i < 2000; i++)
		if (!Hash[i].name.empty())
			count++;
	cout << "After Insert Hash table have " << count << " Company." << endl;

	return 0;
}

