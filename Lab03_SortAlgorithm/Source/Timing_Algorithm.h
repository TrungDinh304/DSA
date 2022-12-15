#include <iostream>
#include <chrono>
#include "Sort_Algorithm.h"

using namespace std;
using namespace std::chrono;
using namespace std::literals::chrono_literals;





duration<double, std::milli> time_Sort_Algorithm(int* a, int n, int typeOfSA)
{
    //lấy thời điểm bắt đầu
    auto start = steady_clock::now();
    //chạy thuật toán
    switch (typeOfSA)
    {
    case 1:
        SelectionSort(a, n); break;
    case 2: 
        InsertionSort(a, n); break;
    case 3:
        BubbleSort(a, n); break;
    case 4:
        HeapSort(a, n); break;
    case 5:
        MergeSort(a, 0, n - 1); break;
    case 6:
        QuickSort(a, 0, n - 1); break;
    case 7:
        RadixSort(a, n); break;
    case 8:
        ShakerSort(a, n); break;
    case 9:
        ShellSort(a, n); break;
    case 10:
        CountingSort(a, n); break;
    case 11:
        FlashSort(a, n); break;
    default:
        break;
    }
    // lấy thời điểm kết thúc
    auto end = steady_clock::now();
    // lấy quãng thời gian end - start, tự động ép kiểu nó về kiểu giá trị số thực double,
    //kiểu đơn vị mili giây (std::milli hoặc std::ratio<1, 1000>)
    duration<double, std::milli> elapsed1 = end - start;
    return elapsed1;
}




