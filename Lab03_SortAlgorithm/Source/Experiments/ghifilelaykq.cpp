#include"GenarateData.h"
#include "counting_comparisions.h"
#include "Timing_Algorithm.h"
#include<fstream>
#include<iomanip>
#include<string>
using namespace std;


int datasize[6] = { 10000,30000, 50000, 100000, 300000, 500000 };
string data_Order[] = { "Random", "Sorted","Reverse","Nearly Sorted" };
string Algor_typ[] = { "Selection Sort","Insertion Sort","Bubble Sort", "Heap Sort",
                        "Merge sort","Quick Sort", "Radix Sort","Shaker Sort","Shell Sort","Counting Sort","Flash Sort" };


//void printArr(int* a, int n)
//{
//    cout << "Array Have " << n << " Elements:" << endl;
//    for (int i = 0; i < n; i++)
//    {
//        cout << a[i] << ' ';
//    }
//    cout << endl;
//}

void Experiments()
{
    ofstream fout;
    fout.open("ouput.csv");
    //data type
    for (int j = 0; j < 4; j++)
    {
        fout << '\n' << data_Order[j] << '\n';

        //in dòng data size
        fout << "Data size: ,";
        for (int i = 0; i < 6; i++)
            fout << datasize[i] << ',' << ',';
        fout << '\n';

        fout << "Resulting statics ,";
        for (int i = 0; i < 6; i++)
            fout << "Running time,Comparisions,";
        fout << '\n';

        //sort Algorithm
        for (int k = 1; k <= 1; k++)
        {
            fout << Algor_typ[k - 1] << ',';
            //chạy từng data size
            for (int i = 0; i < 6; i++)
            {
                int* a = new int[datasize[i]];
                int* b = new int[datasize[i]]{};
                
                GenerateData(a, datasize[i], j);
                for (int o = 0; o < datasize[i]; o++)
                    b[o] = a[o];
                
                duration<double, milli> time_taken = time_Sort_Algorithm(a, datasize[i], k);
                fout << time_taken.count() << ',';
                switch (k)
                {
                case 1:
                    fout << com_SelectionSort(b, datasize[i]) << ',';
                    break;
                case 2: 
                    fout << com_InsertionSort(b, datasize[i]) << ','; break;
                case 3:
                    fout << com_BubbleSort(b, datasize[i]) << ','; break;
                case 4:
                    fout << com_HeapSort(b, datasize[i]) << ','; break;
                case 5:
                    fout << com_MergeSort(b, 0, datasize[i] - 1) << ',';
                    break;
                case 6:
                    fout << com_QuickSort(b, 0, datasize[i] - 1) << ','; break;
                case 7:
                    fout << com_RadixSort(b, datasize[i]) << ','; break;
                case 8: 
                    fout << com_ShakerSort(b, datasize[i]) << ','; break;
                case 9:
                    fout << com_ShellSort(b, datasize[i]) << ','; break;
                case 10:
                    fout << com_CountingSort(b, datasize[i]) << ','; break;
                case 11: 
                    fout << com_FlashSort(b, datasize[i]) << ','; break;
                default:
                    break;
                }
            }
            fout << '\n';
        }
    }
    fout.close();
}


int main()
{
    /*int a[] = { 86, 198, 466, 709, 973, 981, 974 };
    int n = sizeof(a) / sizeof(int);*/
    
    //int* a = new int[1000];
    //int n = 1000;
    //GenerateRandomData(a, 1000);
    //printArr(a, n);
    //MergeSort(a, 0, n - 1);
    //RadixSort(a, n);
    //CountingSort(a, n);
    //printArr(a, n);
   
    Experiments();
    

    return 1;
}
