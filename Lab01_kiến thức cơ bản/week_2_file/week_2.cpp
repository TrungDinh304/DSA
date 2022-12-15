#include <iostream>
#include<sstream>
#include<string.h>
#include<fstream>
#include<vector>
using namespace std;


struct Examinee
{
    string id;
    float maths, literature, physics, chemistry, biology, history, geography, civic_education, natural_science, social_science, foreign_language;
};

/*vector<Examinee>*/
Examinee readExaminee(string line_info)
{
    Examinee inf;
    stringstream S(line_info);
    vector<float> diem;
    string buffer;
    getline(S, buffer, ',');
    inf.id = buffer;
    getline(S, buffer, ',');
    for (int i = 0; i < 11; i++)
    {
        getline(S, buffer, ',');
        if (!buffer.empty())
        {
            diem.push_back(stof(buffer));
        }
        else
            diem.push_back(0);
    }
    getline(S, buffer, ',');
    getline(S, buffer, '\n');
    inf.maths = diem[0];
    inf.literature = diem[1];
    inf.physics = diem[2];
    inf.chemistry = diem[3];
    inf.biology = diem[4];
    inf.history = diem[5];
    inf.geography = diem[6];
    inf.civic_education = diem[7];
    inf.natural_science = diem[8];
    inf.social_science = diem[9];
    inf.foreign_language = diem[10];

    return inf;
}

//2. Read the information of a list of examinees:
vector<Examinee> readExamineeList(string file_name)
{
    //mở file
    vector <Examinee> result;
    ifstream fin;
    fin.open(file_name,ios::in);
    if (!fin.is_open())
    {
        cout << "Mo file khong thanh cong." << endl;
        return result;
    }
    else
        cout << "Mo file thanh cong." << endl;

    //đọc file
    string line_info;

    getline(fin, line_info, '\n');
    while (!fin.eof())
    {
        getline(fin, line_info, '\n');
        result.push_back(readExaminee(line_info));
    }

    //đóng file
    fin.close();

    return result;
}


void print_an_Examinee(Examinee a)
{
    cout << a.id << ' ';
    cout << a.maths << ' ';
    cout << a.literature << ' ';
    cout << a.physics << ' ';
    cout << a.chemistry << ' ';
    cout << a.biology << ' ';
    cout << a.history << ' ';
    cout << a.geography << ' ';
    cout << a.civic_education << ' ';
    cout << a.natural_science << ' ';
    cout << a.social_science << ' ';
    cout << a.foreign_language << endl;
}


void printListExaminee(vector<Examinee> a)
{
    int n = a.size();
    for (int i = 0; i < n; i++)
    {
        cout << a[i].id << ' ';
        cout << a[i].maths << ' ';
        cout << a[i].literature << ' ';
        cout << a[i].physics << ' ';
        cout << a[i].chemistry << ' ';
        cout << a[i].biology << ' ';
        cout << a[i].history << ' ';
        cout << a[i].geography << ' ';
        cout << a[i].civic_education << ' ';
        cout << a[i].natural_science << ' ';
        cout << a[i].social_science << ' ';
        cout << a[i].foreign_language << endl;
    }
}


void write_To_Test(vector<Examinee> examinee_list, string out_file_name)
{
    ofstream fout;
    fout.open(out_file_name, ios::out);
    int n = examinee_list.size();
    for (int i = 0; i < n; i++)
    {
        fout << examinee_list[i].id << ' ';
        fout << examinee_list[i].maths << ' ';
        fout << examinee_list[i].literature << ' ';
        fout << examinee_list[i].physics << ' ';
        fout << examinee_list[i].chemistry << ' ';
        fout << examinee_list[i].biology << ' ';
        fout << examinee_list[i].history << ' ';
        fout << examinee_list[i].geography << ' ';
        fout << examinee_list[i].civic_education << ' ';
        fout << examinee_list[i].natural_science << ' ';
        fout << examinee_list[i].social_science << ' ';
        fout << examinee_list[i].foreign_language << endl;
    }
    fout.close();
}

//3. Write the total score of examinees to file:
void writeScores(vector<Examinee> examinee_list, string out_file_name)
{
    ofstream fout;
    fout.open(out_file_name, ios::out);
    int n = examinee_list.size();
    fout << "SBD BB KHTN KHXH TK" << endl;
    for (int i = 0; i < n; i++)
    {
        float BB = examinee_list[i].maths + examinee_list[i].literature + examinee_list[i].foreign_language;
        float KHTN = examinee_list[i].physics + examinee_list[i].chemistry + examinee_list[i].biology;
        float KHXH = examinee_list[i].geography + examinee_list[i].history + examinee_list[i].civic_education;
        fout << examinee_list[i].id << ' ';
        fout << BB << ' ';
        fout << KHTN << ' ';
        fout << KHXH << ' ';
        fout << BB + KHTN + KHXH << endl;
    }
    fout.close();
}


int main()
{
    //test phần file
   /* vector<Examinee>List = readExamineeList("data.txt");
    write_To_Test(List, "ghi.txt");
    writeScores(List, "Diemtongket.txt");*/
    return 0;
}