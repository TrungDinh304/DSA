#include"GenarateData.h"
#include "counting_comparisions.h"
#include "Timing_Algorithm.h"
#include<fstream>
#include<string>

using namespace std;


int datasize[6] = { 10000,30000, 50000, 100000, 300000, 500000 };
string data_Order[] = { "Random", "Sorted","Reverse","Nearly Sorted" };
string Algor_typ[] = { "Selection Sort","Insertion Sort","Bubble Sort", "Heap Sort",
                        "Merge sort","Quick Sort", "Radix Sort","Shaker Sort","Shell Sort","Counting Sort","Flash Sort" };

long long NumberOfComparisions(int SortAlgorithm_type, int* a, int n)
{
	long long comparisions = 0;
	switch (SortAlgorithm_type)
	{
	case 1:
		comparisions = com_SelectionSort(a, n);
		break;
	case 2:
		comparisions = com_InsertionSort(a, n);
		break;
	case 3:
		comparisions = com_BubbleSort(a, n);
		break;
	case 4:
		comparisions = com_HeapSort(a, n);
		break;
	case 5:
		comparisions = com_MergeSort(a, 0, n - 1);
		break;
	case 6:
		comparisions = com_QuickSort(a, 0, n - 1);
		break;
	case 7:
		comparisions = com_RadixSort(a, n);
		break;
	case 8:
		comparisions = com_ShakerSort(a, n);
		break;
	case 9:
		comparisions = com_ShellSort(a, n);
		break;
	case 10:
		comparisions = com_CountingSort(a, n);
		break;
	case 11:
		comparisions = com_FlashSort(a, n);
		break;
	default:
		break;
	}
	return comparisions;
}


void experiments()
{
    for(int i=0;i<4;i++)
        for(int j=0;j<6;j++)
            for (int k = 1; k <= 11; k++)
            {
                int* a = new int[datasize[j]];
                GenerateData(a, datasize[j], i);
                int* b = new int[datasize[j]];
                for (int l = 0; l < datasize[j]; l++)
                    b[l] = a[l];
                cout << "- Data Order: " << data_Order[i] << '.' << endl;
                cout << "- Data Size: " << datasize[j] << '.' << endl;
                cout << "- Sort Algorithm: " << Algor_typ[k - 1] << '.' << endl;
				cout << "- Runtime: " << time_Sort_Algorithm(a, datasize[j], k).count() << " ms." << endl;
				cout << "- Comparisions: " << NumberOfComparisions(k, b, datasize[j]) << '.' << endl;
				cout << endl;
				delete[]a;
				delete[]b;
            }
}

int main()
{
	experiments();
	return 1;
}

