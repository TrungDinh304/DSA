#include "GenarateData.h"
#include "counting_comparisions.h"
#include "Timing_Algorithm.h"
#include <fstream>


// Read file
int* read_File(char filename[], int& n)
{
	ifstream fin(filename);
	if (!fin)
	{
		cout << "Mo file khong thanh cong!";
		return NULL;
	}
	fin >> n;
	int* a = new int[n];
	for (int i = 0; i < n; i++)
	{
		fin >> a[i];
	}
	fin.close();
	return a;
}

// Write File
int write_File(const char* filename, int* a, int n)
{
	ofstream fout(filename);
	if (!fout)
	{
		cout << "Mo file khong thanh cong!";
		return 0;
	}
	fout << n << endl;
	for (int i = 0; i < n; i++)
	{
		fout << a[i] << " ";
	}
	fout.close();
	return 1;
}

// Xác định loại thuật toán sắp xếp
int SortAlgorithm_type(char Algorithm[])
{
	int SortAlgorithm_type = 0;
	if (strcmp(Algorithm, "selection-sort") == 0)
		SortAlgorithm_type = 1;
	else if (strcmp(Algorithm, "insertion-sort") == 0)
		SortAlgorithm_type = 2;
	else if (strcmp(Algorithm, "bubble-sort") == 0)
		SortAlgorithm_type = 3;
	else if (strcmp(Algorithm, "heap-sort") == 0)
		SortAlgorithm_type = 4;
	else if (strcmp(Algorithm, "merge-sort") == 0)
		SortAlgorithm_type = 5;
	else if (strcmp(Algorithm, "quick-sort") == 0)
		SortAlgorithm_type = 6;
	else if (strcmp(Algorithm, "radix-sort") == 0)
		SortAlgorithm_type = 7;
	else if (strcmp(Algorithm, "shaker-sort") == 0)
		SortAlgorithm_type = 8;
	else if (strcmp(Algorithm, "shell-sort") == 0)
		SortAlgorithm_type = 9;
	else if (strcmp(Algorithm, "counting-sort") == 0)
		SortAlgorithm_type = 10;
	else if (strcmp(Algorithm, "flash-sort") == 0)
		SortAlgorithm_type = 11;
	return SortAlgorithm_type;
}

// Đếm số phép so sánh 
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

// Xác định input order
int Order(char inputOrder[])
{
	int order = 0; // Tuong duong -rand
	if (strcmp(inputOrder, "-sorted") == 0)
	{
		order = 1;
	}
	if (strcmp(inputOrder, "-rev") == 0)
	{
		order = 2;
	}
	if (strcmp(inputOrder, "-nsorted") == 0)
	{
		order = 3;
	}
	return order;
}
// Command 1:
void Command1(char Algorithm[], char inputGiven[], char output_parameter[])
{
	int n = 0;

	//đọc file lưu số phần tử và lưu phần tử vào mản động.
	int* a = read_File(inputGiven, n);
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;
	cout << "Input file: " << inputGiven << endl;
	cout << "Input size: " << n << endl;
	cout << "--------------------------------" << endl;

	//phân loại thuật toán sắp xếp để chạy switch case
	int Algorithm_type = SortAlgorithm_type(Algorithm);



	if (strcmp(output_parameter, "-both") == 0)
	{
		int* b = new int[n];
		for (int i = 0; i < n; i++)
			b[i] = a[i];
		duration<double, milli> time_taken = time_Sort_Algorithm(a, n, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;

		long long comparisions = NumberOfComparisions(Algorithm_type, b, n);

		cout << "Comparisions (if required): " << comparisions << endl;
		delete[] b;
	}
	else if (strcmp(output_parameter, "-time") == 0)
	{
		duration<double, milli> time_taken = time_Sort_Algorithm(a, n, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;
	}
	else if (strcmp(output_parameter, "-comp") == 0)
	{
		long long comparisions = NumberOfComparisions(Algorithm_type, a, n);

		cout << "Comparisions (if required): " << comparisions << endl;
	}
	
	write_File("output.txt", a, n);

	delete[] a;
}

// Command 2: 
void Command2(char Algorithm[], int inputSize, char inputOrder[], char output_parameter[])
{
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;
	cout << "Input size: " << inputSize << endl;
	cout << "Input order: " << inputOrder << endl;
	cout << "--------------------------------" << endl;

	int Algorithm_type = SortAlgorithm_type(Algorithm);
	// Input order
	int dataType = Order(inputOrder);

	// Tao du lieu
	int* a = new int[inputSize];
	int* b = new int[inputSize];
	GenerateData(a, inputSize, dataType);
	GenerateData(b, inputSize, dataType);

	// Ghi file input
	write_File("input.txt", a, inputSize);

	//output_parameter
	if (strcmp(output_parameter, "-comp") == 0) {
		long long comparisions = NumberOfComparisions(Algorithm_type, a, inputSize);
		cout << "Running time (if required): " << endl;
		cout << "Comparisions (if required): " << comparisions << endl;
	}
	else if (strcmp(output_parameter, "-time") == 0) {
		duration<double, milli>runtime = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << runtime.count() << endl;
		cout << "Comparisions (if required): " << endl;
	}
	else if (strcmp(output_parameter, "-both") == 0) {
		duration<double, milli>runtime = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		long long comparisions = NumberOfComparisions(Algorithm_type, b, inputSize);
		cout << "Running time (if required): " << runtime.count() << endl;
		cout << "Comparisions (if required): " << comparisions << endl;
	}
	// Ghi file output
	write_File("output.txt", a, inputSize);
}

// Command 3:
void Command3(char Algorithm[], int inputSize, char output_parameter[])
{
	cout << "ALGORITHM MODE" << endl;
	cout << "Algorithm: " << Algorithm << endl;
	cout << "Input size: " << inputSize << endl << endl;


	int Algorithm_type = SortAlgorithm_type(Algorithm);
	int* a = new int[inputSize];
	// --------------- Random-----------------------------
	cout <<"Input Order: Randomize" << endl;
	cout << "-------------------------------" << endl;
	// Tao du lieu

	GenerateData(a, inputSize, 0);
	// Ghi file input
	write_File("input_1.txt", a, inputSize);


	if (strcmp(output_parameter, "-both") == 0)
	{
		int* b = new int[inputSize];
		for (int i = 0; i < inputSize; i++)
			b[i] = a[i];
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;

		long long comparisions = NumberOfComparisions(Algorithm_type, b, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
		delete[] b;
	}
	else if (strcmp(output_parameter, "-time") == 0)
	{
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;
	}
	else if (strcmp(output_parameter, "-comp") == 0)
	{
		long long comparisions = NumberOfComparisions(Algorithm_type, a, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
	}
	cout << endl;
	// --------------- Sorted -----------------------------
	cout << "Input Order: Sorted" << endl;
	cout << "-------------------------------" << endl;
	// Tao du lieu
	GenerateData(a, inputSize, 1);
	// Ghi file input
	write_File("input_3.txt", a, inputSize);


	if (strcmp(output_parameter, "-both") == 0)
	{
		int* b = new int[inputSize];
		for (int i = 0; i < inputSize; i++)
			b[i] = a[i];
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;

		long long comparisions = NumberOfComparisions(Algorithm_type, b, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
		delete[] b;
	}
	else if (strcmp(output_parameter, "-time") == 0)
	{
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;
	}
	else if (strcmp(output_parameter, "-comp") == 0)
	{
		long long comparisions = NumberOfComparisions(Algorithm_type, a, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
	}
	cout << endl;
	// --------------- Nearly Sorted -----------------------------
	cout << "Input Order: Randomize" << endl;
	cout << "-------------------------------" << endl;
	// Tao du lieu
	GenerateData(a, inputSize, 3);
	// Ghi file input
	write_File("input_2.txt", a, inputSize);


	if (strcmp(output_parameter, "-both") == 0)
	{
		int* b = new int[inputSize];
		for (int i = 0; i < inputSize; i++)
			b[i] = a[i];
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;

		long long comparisions = NumberOfComparisions(Algorithm_type, b, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
		delete[] b;
	}
	else if (strcmp(output_parameter, "-time") == 0)
	{
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;
	}
	else if (strcmp(output_parameter, "-comp") == 0)
	{
		long long comparisions = NumberOfComparisions(Algorithm_type, a, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
	}
	cout << endl;
	// --------------- Reversed -----------------------------
	cout << "Input Order: Reversed" << endl;
	cout << "-------------------------------" << endl;
	// Tao du lieu
	GenerateData(a, inputSize, 2);
	// Ghi file input
	write_File("input_4.txt", a, inputSize);


	if (strcmp(output_parameter, "-both") == 0)
	{
		int* b = new int[inputSize];
		for (int i = 0; i < inputSize; i++)
			b[i] = a[i];
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;

		long long comparisions = NumberOfComparisions(Algorithm_type, b, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
		delete[] b;
	}
	else if (strcmp(output_parameter, "-time") == 0)
	{
		duration<double, milli> time_taken = time_Sort_Algorithm(a, inputSize, Algorithm_type);
		cout << "Running time (if required): " << time_taken.count() << " ms." << endl;
	}
	else if (strcmp(output_parameter, "-comp") == 0)
	{
		long long comparisions = NumberOfComparisions(Algorithm_type, a, inputSize);

		cout << "Comparisions (if required): " << comparisions << endl;
	}
	cout << endl;
}

// Command 4:
void Command4(char Algorithm1[], char Algorithm2[], char givenInput[])
{
	int n = 0;
	int* a = read_File(givenInput, n);
	cout << "COMPARE MODE" << endl;
	cout << "Algorithm: " << Algorithm1 << " | " << Algorithm2 << endl;
	cout << "Input file: " << givenInput << endl;
	cout << "Input size: " << n << endl;
	cout << "--------------------------------" << endl;
	int Algorithm_type1 = SortAlgorithm_type(Algorithm1);
	int Algorithm_type2 = SortAlgorithm_type(Algorithm2);
	// Running time:
	// Tao mang a1, b, b1 copy mang a:
	int* a1 = new int[n];
	int* b = new int[n];
	int* b1 = new int[n];
	for (int i = 0; i < n; i++)
	{
		a1[i] = a[i];
		b[i] = a[i];
		b1[i] = a[i];
	}
	duration<double, milli> time_taken1 = time_Sort_Algorithm(a, n, Algorithm_type1);
	duration<double, milli> time_taken2 = time_Sort_Algorithm(b, n, Algorithm_type2);
	// Comparisions:
	long long comparisions1 = NumberOfComparisions(Algorithm_type1, a1, n);
	long long comparisions2 = NumberOfComparisions(Algorithm_type2, b1, n);

	cout << "Running time: " << time_taken1.count() << " ms" << " | " << time_taken2.count() << " ms" << endl;
	cout << "Comparisions: " << comparisions1 << " | " << comparisions2 << endl;

}

// Command 5:
void Command5(char Algorithm1[], char Algorithm2[], int inputSize, char inputOrder[])
{
	cout << "COMPARE MODE" << endl;
	cout << "Algorithm: " << Algorithm1 << " | " << Algorithm2 << endl;
	cout << "Input size: " << inputSize << endl;
	cout << "Input order: " << inputOrder << endl;
	cout << "--------------------------------" << endl;
	// Input order
	int dataType = Order(inputOrder);
	// Tao du lieu
	int* a = new int[inputSize];
	GenerateData(a, inputSize, dataType);
	// Ghi xuong file input.txt
	write_File("input.txt", a, inputSize);

	// Tao mang a1, b, b1 copy mang a:
	int* a1 = new int[inputSize];
	int* b = new int[inputSize];
	int* b1 = new int[inputSize];
	for (int i = 0; i < inputSize; i++)
	{
		a1[i] = a[i];
		b[i] = a[i];
		b1[i] = a[i];
	}
	int Algorithm_type1 = SortAlgorithm_type(Algorithm1);
	int Algorithm_type2 = SortAlgorithm_type(Algorithm2);
	// Running time:
	duration<double, milli> time_taken1 = time_Sort_Algorithm(a, inputSize, Algorithm_type1);
	duration<double, milli> time_taken2 = time_Sort_Algorithm(b, inputSize, Algorithm_type2);
	// Comparisions:
	long long comparisions1 = NumberOfComparisions(Algorithm_type1, a1, inputSize);
	long long comparisions2 = NumberOfComparisions(Algorithm_type2, b1, inputSize);

	cout << "Running time: " << time_taken1.count() << " ms" << " | " << time_taken2.count() << " ms" << endl;
	cout << "Comparisions: " << comparisions1 << " | " << comparisions2 << endl;
}


int main(int argc, char* argv[])
{
	if (strcmp(argv[1], "-c") == 0)
	{
		if (argc == 5)
		{
			Command4(argv[2], argv[3], argv[4]);
		}
		else if (argc == 6)
		{
			Command5(argv[2], argv[3], atoi(argv[4]), argv[5]);
		}
	}
	else if (strcmp(argv[1], "-a") == 0)
	{
		if (argc == 6)
		{
			Command2(argv[2], atoi(argv[3]), argv[4], argv[5]);
		}
		else if (argc == 5)
		{
			if (atoi(argv[3]))
			{
				Command3(argv[2], atoi(argv[3]), argv[4]);
			}
			else
				Command1(argv[2], argv[3], argv[4]);
		}
	}
}