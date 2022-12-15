#include <iostream>

using namespace std;

//Selection Sort
long long com_SelectionSort(int* a, int n)
{
    int min_pos;
    long long comparisions = 0;
    for (int i = 0; ++comparisions && i < n - 1; i++)
    {
        min_pos = i;
        for (int j = i + 1; ++comparisions && j < n; j++)
        {

            if (++comparisions && a[j] < a[min_pos])
                min_pos = j;
        }
        swap(a[i], a[min_pos]);
    }
    return comparisions;
}




//QuickSort
int com_partition(int* a, int l, int r, long long& comparisions)
{
    int pivot = a[(l + r) / 2];
    int i = l, j = r;
    while (++comparisions && i <= j)
    {
        while (++comparisions && a[i] < pivot)
            i++;
        while (++comparisions && a[j] > pivot)
            j--;
        if (++comparisions && i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

long long com_QuickSort(int* a, int l, int r)
{

    if (l >= r)
        return 1;
    long long b = 0;
    int pivot = com_partition(a, l, r, b);
    long long c = com_QuickSort(a, l, pivot - 1);
    long long d = com_QuickSort(a, pivot, r);
    return b + c + d;
}


//HeapSort
long long com_heapify(int* a, int n, int i)
{
    int Largest = i;
    int Left = 2 * i + 1;
    int Right = 2 * i + 2;
    //trong if này tính là 3
    int b = 1;
    if (Left<n && a[Left]>a[Largest])
    {
        Largest = Left;
        b += 1;
    }
    //trong if này tính là 3
    b++;
    if (Right<n && a[Right]>a[Largest])
    {
        b += 1;
        Largest = Right;
    }

    if (Largest == i) return b;

    swap(a[i], a[Largest]);
    long long sub = com_heapify(a, n, Largest);
    //3 lần so sánh trong if và lấy sub
    return b + sub;
}

long long com_CreateMaxHeap(int* a, int n)
{
    long long comparisions = 0;
    for (int i = n / 2 - 1; ++comparisions && i >= 0; i--)
        comparisions += com_heapify(a, n, i);
    return comparisions;
}

long long com_HeapSort(int* a, int n)
{
    long long comparisions = com_CreateMaxHeap(a, n);
    for (int i = n - 1; ++comparisions && i >= 0; i--)
    {
        swap(a[0], a[i]);
        comparisions += com_heapify(a, i, 0);
    }
    return comparisions;
}

//Merge Sort
long long com_Merge(int* a, int l, int mid, int r)
{
    int na = mid - l + 1;
    int nb = r - mid;
    long long comparisions = 0;
    int* L = new int[na];
    for (int i = 0; ++comparisions && i < na; i++)
        L[i] = a[l + i];

    int* R = new int[nb];
    for (int i = 0; ++comparisions && i < nb; i++)
        R[i] = a[mid + i + 1];

    int i = 0, j = 0, k = l;
    while (++comparisions && i < na && j < nb)
    {
        comparisions += 2;
        if (L[i] < R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }

    while (++comparisions && i < na)
        a[k++] = L[i++];

    while (++comparisions && j < nb)
        a[k++] = R[j++];

    delete[] L;
    delete[] R;
    return comparisions;
}
long long com_MergeSort(int* a, int l, int r)
{
    if (l >= r)
        return 1;
    int mid = (l + r) / 2;
    long long L = com_MergeSort(a, l, mid);
    long long R = com_MergeSort(a, mid + 1, r);
    long long m = com_Merge(a, l, mid, r);
    return L + R + m;
}

//Radix Sort
long long com_RadixSort(int* a, int n)
{
    int* b = new int[n];
    int m = a[0], exp = 1;

    long long comparisions = 0;
    for (int i = 0; ++comparisions, i < n; i++)
        if (++comparisions, a[i] > m)
            m = a[i];

    while (++comparisions, m / exp > 0)
    {
        int bucket[10] = { 0 };
        for (int i = 0; ++comparisions, i < n; i++)
            bucket[a[i] / exp % 10]++;
        for (int i = 1; ++comparisions, i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; ++comparisions, i >= 0; i--)
        {
            int pos_output = --bucket[a[i] / exp % 10];
            b[pos_output] = a[i];
        }

        for (int i = 0; ++comparisions, i < n; i++)
            a[i] = b[i];
        exp *= 10;
    }
    delete[] b;
    return comparisions;
}


//Counting Sort
int com_getMax(int* a, int n, long long& comparisions)
{
    int pos_max = 0;
    for (int i = 0; ++comparisions && i < n; i++)
        if (++comparisions && a[i] > a[pos_max])
            pos_max = i;
    return a[pos_max];
}
long long com_CountingSort(int* a, int n)
{
    long long comparisions = 0;
    int max = com_getMax(a, n, comparisions);
    int* count = new int[max + 1]{ 0 };
    int* output = new int[n];
    for (int i = 0; ++comparisions && i < n; i++)
        count[a[i]]++;
    for (int i = 1; ++comparisions && i <= max; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; ++comparisions && i >= 0; i--)
        output[--count[a[i]]] = a[i];
    for (int i = 0; ++comparisions && i < n; i++)
        a[i] = output[i];
    delete[] count;
    delete[] output;
    return comparisions;
}

//Insertion Sort
long long com_InsertionSort(int* a, int n) {
    long long compar = 0;
    for (int i = 1;++compar, i < n; i++) {
        int cur = a[i];
        int j = i - 1; 
        while ((++compar, j >= 0) && (++compar,a[j] > cur)) {
            a[j + 1] = a[j]; 
            j--; 
        }
        a[j + 1] = cur;
    }
    return compar;
}

//Shell Sort
long long com_ShellSort(int* a, int n) {
    long long compar = 0;
    for (int interval = n / 2; ++compar, interval > 0; interval /= 2) {
        for (int i = interval;++compar, i < n; i += 1) { 
            int temp = a[i]; 
            int j;
            for (j = i;(++compar, j >= interval) && (++compar, a[j - interval] > temp); j -= interval) {
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
    return compar;
}

//shaker sort
long long com_ShakerSort(int *a, int n){
    long long comp=0;
    int left=0, right=n-1;
    while(++comp && left<right){
        
        for(int i=left;++comp && i<right;++i){
            if(++comp && a[i]>a[i+1])
                swap(a[i],a[i+1]);   
        }
     
        for(int i=right;++comp && i>left;--i)
            if(++comp && a[i]<a[i-1])
                swap(a[i],a[i-1]);
        left++;
        right--;
    }
    return comp;
}

//bubble sort 
long long com_BubbleSort(int* a, int n){
    long long comp=0;
    for(int i=0;++comp && i<n-1;++i)    
        for(int j=0;++comp && j<n-i-1;++j)
            if(++comp && a[j]>a[j+1]) swap(a[j],a[j+1]);
	return comp;
}

// Flash Sort
long long com_FlashSort(int* a, int n)
{
	long long comparisions = 0;
	int minVal = a[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0;++comparisions && i < m; i++)
		l[i] = 0;
	for (int i = 1;++comparisions &&  i < n; i++)
	{
		if (++comparisions && a[i] < minVal)
			minVal = a[i];
		if (++comparisions && a[i] > a[max])
			max = i;
	}
	if (++comparisions && a[max] == minVal)
		return comparisions;
	double c1 = (double)(m - 1) / (a[max] - minVal);
	for (int i = 0;++comparisions &&  i < n; i++)
	{
		int k = int(c1 * (a[i] - minVal));
		++l[k];
	}
	for (int i = 1;++comparisions && i < m; i++)
		l[i] += l[i - 1];
	swap(a[max], a[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (++comparisions && nmove < n - 1)
	{
		while (++comparisions && j > l[k] - 1)
		{
			j++;
			k = int(c1 * (a[j] - minVal));
		}
		flash = a[j];
		if (++comparisions && k < 0) break;
		while (++comparisions && j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	return comparisions + com_InsertionSort(a, n);
}
