#include <iostream>
#include<fstream>
using namespace std;


int somesum(int n, int& counta, int& countc)
{
    int sum = 0, i = 1, j; counta += 2;
    while (i <= n && ++countc)
    {
        j = n - i; counta++;
        while (j <= i * i && ++countc) {
            sum = sum + i * j; counta++;
            j += 1; counta++;
        }
        i += 1; counta++;
    }
    return sum;
}

int squaresum_recursion(int n, int& a, int& c)
{

    if (n < 1)
    {
        c += 1;
        return 0;
    }
    else
    {
        a += 1;
        c += 1;
        return n * n + squaresum_recursion(n - 1, a, c);
    }
}

int main()
{
    //mở comment để xem các giá trị xuất ra màn hình console
    /*cout << "assign\t\tcompare\t\tvalue" << endl;
    for (int i = 0; i <= 500; i += 25)
    {
        int a = 0, c = 0;
        somesum(i, a, c);
        cout << i << '\t' << a <<'\t' << c << '\n';
    }
    cout << "recurse" << endl;
    for (int i = 0; i <= 500; i += 25)
    {
        int a = 0, c = 0;
        int v = squaresum_recursion(i, a, c);
        cout << a << "\t\t" << c << "\t\t" << v << endl;
    }*/


    //ghi ra file .csv


    ofstream of;
    of.open("test.csv");
    of << "n,assignments,comparisons" << endl;
    for (int i = 0; i <= 500; i += 25)
    {
        int a = 0, c = 0;
        somesum(i, a, c);
        of << i << ',' << a << ',' << c << '\n';
    }
    of << endl << endl << "recurse" << endl;;
    for (int i = 0; i <= 500; i += 25)
    {
        int a = 0, c = 0;
        int v = squaresum_recursion(i, a, c);
        of << a << ',' << c << ',' << v << endl;
    }
    of.close();

    return 0;
}