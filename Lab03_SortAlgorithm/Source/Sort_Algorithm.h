#include <iostream>

using namespace std;

//Selection Sort
void SelectionSort(int* a, int n)
{
    int min_pos;

    for (int i = 0; i < n; i++)
    {
        min_pos = i;
        for (int j = i + 1; j < n; j++)
        {
            if (a[j] < a[min_pos])
                min_pos = j;
        }
        swap(a[i], a[min_pos]);
    }
}

//Insertion Sort
void InsertionSort(int* a, int n) {
    //khởi tạo mảng đã sắp xếp có 1 phần tử a[0]
    //với i chạy từ 1 đến n-1
    for (int i = 1; i < n; i++) {
        //biến cur so sánh phần tử thứ i với mảng đã sắp xếp
        int cur = a[i];

        int j = i - 1; //phần tử thứ j đứng trước i 
        while (j >= 0 && a[j] > cur) { //duyệt qua mảng sorted
            //nếu phần tử đang xét nhỏ hơn phần tử thứ j của dãy sorted
            a[j + 1] = a[j]; //di chuyển các phần tử lớn hơn lên một đơn vị
            j--; //tiếp tục xét với phần tử phía trước
        }

        a[j + 1] = cur; //chèn phần tử đang xét vào ô trống
    }
}


// Quick Sort
int partition(int* a, int l, int r)
{
    int pivot = a[(l + r) / 2];
    int i = l, j = r;
    while (i <= j)
    {
        while (a[i] < pivot)
            i++;
        while (a[j] > pivot)
            j--;
        if (i <= j)
        {
            swap(a[i], a[j]);
            i++;
            j--;
        }
    }
    return i;
}

void QuickSort(int* a, int l, int r)
{
    if (l >= r)
        return;
    int pivot = partition(a, l, r);
    QuickSort(a, l, pivot - 1);
    QuickSort(a, pivot, r);
}

//Heap Sort
void heapify(int* a, int n, int i)
{
    int Largest = i;
    int Left = 2 * i + 1;
    int Right = 2 * i + 2;
    if (Left<n && a[Left]>a[Largest])
        Largest = Left;
    if (Right<n && a[Right]>a[Largest])
        Largest = Right;

    if (Largest == i) return;
    swap(a[i], a[Largest]);
    heapify(a, n, Largest);
}

void CreateMaxHeap(int* a, int n)
{
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(a, n, i);
}

void HeapSort(int* a, int n)
{
    CreateMaxHeap(a, n);
    for (int i = n - 1; i >= 0; i--)
    {
        swap(a[0], a[i]);
        heapify(a, i, 0);
    }
}


//Merge sort
void Merge(int* a, int l, int mid, int r)
{
    //số phần tử của mảng bên trái
    int na = mid - l + 1;
    int nb = r - mid;

    int* L = new int[na];
    for (int i = 0; i < na; i++)
        L[i] = a[l + i];

    int* R = new int[nb];
    for (int i = 0; i < nb; i++)
        R[i] = a[mid + i + 1];

    int i = 0, j = 0, k = l;
    while (i < na && j < nb)
    {
        if (L[i] < R[j])
            a[k++] = L[i++];
        else
            a[k++] = R[j++];
    }
    while (i < na)
        a[k++] = L[i++];
    while (j < nb)
        a[k++] = R[j++];
    delete[] L;
    delete[] R;

}
void MergeSort(int* a, int l, int r)
{
    if (l >= r)
        return;
    int mid = (l + r) / 2;
    MergeSort(a, l, mid);
    MergeSort(a, mid + 1, r);
    Merge(a, l, mid, r);
}


//Radix Sort
void RadixSort(int* a, int n)
{
    int* b = new int[n];
    int m = a[0], exp = 1;

    for (int i = 0; i < n; i++)
        if (a[i] > m)
            m = a[i];

    while (m / exp > 0)
    {
        int bucket[10] = { 0 };
        for (int i = 0; i < n; i++)
            bucket[a[i] / exp % 10]++;
        for (int i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
        for (int i = n - 1; i >= 0; i--)
        {
            int pos_output = --bucket[a[i] / exp % 10];
            b[pos_output] = a[i];
        }
        for (int i = 0; i < n; i++)
            a[i] = b[i];
        exp *= 10;
    }
    delete[] b;
}
// Countint Sort
int getMax(int* a, int n)
{
    int pos_max = 0;
    for (int i = 0; i < n; i++)
        if (a[i] > a[pos_max])
            pos_max = i;
    return a[pos_max];
}
void CountingSort(int* a, int n)
{
    int max = getMax(a, n);
    int* count = new int[max + 1]{ 0 };
    int* output = new int[n];
    for (int i = 0; i < n; i++)
        count[a[i]]++;
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--)
        output[--count[a[i]]] = a[i];
    for (int i = 0; i < n; i++)
        a[i] = output[i];
    delete[] count;
    delete[] output;
}


//Shell Sort
void ShellSort(int* a, int n) {
    //bắt đầu với khoảng bằng một nửa kích thước, sau đó giảm một nửa
    for (int interval = n / 2; interval > 0; interval /= 2) {
        for (int i = interval; i < n; i += 1) { //duyệt từ giá trị interval đến n
            int temp = a[i]; //sao chép giá trị đang xét vào biến tạm
            int j;
            //các phần tử nằm trong khoảng n/2 sẽ được so sánh và hoán đổi vị trí nếu chúng không theo thứ tự
            for (j = i; j >= interval && a[j - interval] > temp; j -= interval) {// sử dụng thuật toán Insertion Sort
                a[j] = a[j - interval];
            }
            a[j] = temp;
        }
    }
    //khi khoảng = 1 thì các phần tử của mảng nằm trong khoảng 1 được sắp xếp
}
//bubble sort 
void BubbleSort(int* a, int n){
    for(int i=0;i<n-1;++i)    
        for(int j=0;j<n-i-1;++j)
            if(a[j]>a[j+1]) swap(a[j],a[j+1]);

}

//shaker sort
void ShakerSort(int *a, int n){
    int left=0, right=n-1;
    while(left<right){
        //đưa phần tử lớn nhất về cuối mảng 
        for(int i=left;i<right;++i){
            if(a[i]>a[i+1])
                swap(a[i],a[i+1]);   
        }
        //đưa phần tử nhỏ nhất về đầu mảng
        for(int i=right;i>left;--i)
            if(a[i]<a[i-1])
                swap(a[i],a[i-1]);
        left++;
        right--;
    }
}


// Flash Sort 
void FlashSort(int* a, int n)
{
	int minVal = a[0];
	int max = 0;
	int m = int(0.45 * n);
	int* l = new int[m];
	for (int i = 0; i < m; i++)
		l[i] = 0;
	for (int i = 1; i < n; i++)
	{
		if (a[i] < minVal)
			minVal = a[i];
		if (a[i] > a[max])
			max = i;
	}
	if (a[max] == minVal)
		return;
	double c1 = (double)(m - 1) / (a[max] - minVal);
	for (int i = 0; i < n; i++)
	{
		int k = int(c1 * (a[i] - minVal));
		++l[k];
	}
	for (int i = 1; i < m; i++)
		l[i] += l[i - 1];
	swap(a[max], a[0]);
	int nmove = 0;
	int j = 0;
	int k = m - 1;
	int t = 0;
	int flash;
	while (nmove < n - 1)
	{
		while (j > l[k] - 1)
		{
			j++;
			k = int(c1 * (a[j] - minVal));
		}
		flash = a[j];
		if (k < 0) break;
		while (j != l[k])
		{
			k = int(c1 * (flash - minVal));
			int hold = a[t = --l[k]];
			a[t] = flash;
			flash = hold;
			++nmove;
		}
	}
	delete[] l;
	InsertionSort(a, n);
}
