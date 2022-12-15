#include <iostream>
using namespace std;
//1: pointer
// -----------------------------------------------------------------------------
//Swap 2 given integers.
void swap(int* a, int* b)
{
    if (a == NULL || b == NULL) return;
    int temp = *a;
    *a = *b;
    *b = temp;
}

//Calculate the total value of 2 integers.
int* sum(int* a, int* b)
{
    int* tong = new int;
    *tong = *a + *b;
    return tong;
}

//Input an array with unknown size.
void inputArray(int*& a, int& n)
{
    cout << "Nhap so phan tu cua mang: ";
    cin >> n;
    while (n <= 0)
    {
        cout << "So phan tu khong hop le xin vui long nhap lai: ";
        cin >> n;
    }
    a = new int[n];
    for (int i = 0; i < n; i++)
    {
        cout << "Phan tu [" << i << "]: ";
        cin >> a[i];
    }
}

//Print a given array.
void printArray(int* a, int n)
{
    if (a == NULL)return;
    cout << "Array have " << n << " element:" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << "[" << i << "]: " << a[i] << endl;
    }
}
//Find the largest value from a given array.
int* findMax(int* arr, int n)
{
    if (arr == NULL) return NULL;
    int posmax = 0;//vi tri cua phantu lon nhat
    for (int i = 1; i < n; i++)
        if (arr[posmax] < arr[i])
            posmax = i;
    return &arr[posmax];
}
//Find the longest ascending subarray from a given array.
int* findLongestAscendingSubarray(int* a, int n, int& length)
{
    int FistposOfsubarray = 0;
    int kichthuocmangtang = 0;
    
    for (int i = 1; i <= n; i++)
    {
        kichthuocmangtang++;
        if (i == n)
            break;
        if ((a[i] < a[i - 1]))
        {
            if (kichthuocmangtang > length)
            {
                length = kichthuocmangtang;
                FistposOfsubarray = i - length;
            }
            kichthuocmangtang = 0;
        }
    }

    if (kichthuocmangtang >= length)
    {
        length = kichthuocmangtang;
        FistposOfsubarray = n - length;
    }
    
    return &a[FistposOfsubarray];
}


//Swap 2 given arrays.
void swapArrays(int*& a, int*& b, int& na, int& nb)
{
    int* c = a;
    a = b;
    b = c;
    swap(&na, &nb);
}

//Concatenate 2 given arrays.
int* concatenate2Arrays(int* a, int* b, int na, int nb, int& nc)
{
    if (a == NULL && b != NULL)
    {
        nc = nb;
        return b;
    }
    if (a != NULL && b == NULL)
    {
        nc = na;
        return a;
    }
    if (a == NULL && b == NULL)
        return NULL;
    nc = na + nb;
    int* result = new int[nc];
    for (int i = 0; i < na; i++)
        result[i] = a[i];
    for (int i = 0; i < nb; i++)
        result[na + i] = b[i];
    return result;

}

//Given 2 ascending arrays with distinguish elements.Generate a new ascending array with all elements from the given arrays.
int* merge2Arrays(int* a, int* b, int na, int nb, int& nc)
{
    if (a == NULL && b != NULL)
    {
        nc = nb;
        return b;
    }
    if (a != NULL && b == NULL)
    {
        nc = na;
        return a;
    }
    if (a == NULL && b == NULL)
        return NULL;
    nc = na + nb;
    int* result = new int[nc];
    int i = 0, j = 0, k = 0;
    while (i < na && j < nb)
    {
        if (a[i] >= b[j])
            result[k++] = b[j++];
        if (a[i] <= b[j])
            result[k++] = a[i++];
    }
    while (i < na)
        result[k++] = a[i++];
    while (j < nb)
        result[k++] = b[j++];
    return result;
}

//Generate a random matrix with keyboard input size.
void generateMatrix1(int**& a, int& length, int& width)
{
    cout << "Type the number of length in matrix: ";
    cin >> length;
    while (length <= 0)
    {
        cout << "the number of length is illegal please retype: ";
        cin >> length;
    }
    cout << "Type the number of width in matrix: ";
    cin >> width;
    while (width <= 0)
    {
        cout << "the number of width is illegal please retype: ";
        cin >> width;
    }

    a = new int* [length];
    for (int i = 0; i < length; i++)
    {
        a[i] = new int[width];
        for (int j = 0; j < width; j++)
            a[i][j] = rand() % 30;
    }
}
void printMatrix(int** a, int l, int w)
{
    cout << "Matrix:" << endl;
    for (int i = 0; i < l; i++) 
    {
        for (int j = 0; j < w; j++)
            cout << a[i][j] << ' ';
        cout << endl;
    }

}

//Given two 1D arrays a and b. Generate the matrix c that c[i][j] = a[i] * b[j].
int** generateMatrix2(int* a, int* b, int na, int nb, int& crow, int &col)
{
    if (a == NULL || b == NULL)
        return NULL;
    crow = na;
    col = nb;
    int** result = new int* [crow];
    for (int i = 0; i < crow; i++)
    {
        result[i] = new int[col];
        for (int j = 0; j < col; j++)
            result[i][j] = a[i] * b[j];
    }
    return result;
}

//Swap 2 columns / rows of a given matrix.
void swapRows(int** a, int length, int width, int ir1, int ir2)
{
    swapArrays(a[ir1], a[ir2],width,width);
}

void swapColumns(int** a, int length, int width, int ic1, int ic2)
{
    for(int i=0;i<length;i++)
        swap(a[i][ic1], a[i][ic2]);
}

//Generate the transpose matrix of a given matrix.
int** transposeMatrix(int** a, int length, int width)
{
    if (a == NULL)
        return NULL;
    int** trans = new int* [width];
    for (int i = 0; i < width; i++)
    {
        trans[i] = new int[length];
        for (int j = 0; j < length; j++)
            trans[i][j] = a[j][i];
    }
    return trans;
}
//Concatenate 2 given size-equal matrices, horizontally / vertically.
int** concatenate2MatricesH(int** a, int** b, int length, int width, int& lres, int& wres)
{
    lres = length; wres = width*2;
    int** result = new int* [lres];
    for (int i = 0; i < length; i++)
    {
        result[i] = new int [wres];
        for (int j = 0; j < width; j++)
        {
            result[i][j] = a[i][j];
            result[i][width + j] = b[i][j];
        }
    }
    return result;
}

int** concatenate2MatricesV(int** a, int** b, int length, int width, int& lres, int& wres)
{
    lres = length * 2;
    wres = width;
    int** result = new int* [lres];
    for (int i = 0; i < lres; i++)
    {
        result[i] = new int[wres];
        if (i < length)
        {
            for (int j = 0; j < wres; j++)
            {
                result[i][j] = a[i][j];
            }
        }
        else
        {
            for (int j = 0; j < wres; j++)
            {
                result[i][j] = b[i - length][j];
            }
        }
    }
    
    return result;
}


//Multiple 2 given matrices.
bool multiple2Matrices(int**& res, int** a, int** b, int& lengthr, int& widthr, int lengtha, int widtha, int lengthb, int widthb)
{
    if (widtha != lengthb || a == NULL || b == NULL)
        return 0;
    lengthr = lengtha;
    widthr = widthb;
    res = new int* [lengthr];
    for (int i = 0; i < lengthr; i++)
    {
        res[i] = new int[widthr];
        for (int j = 0; j < widthr; j++)
        {
            res[i][j] = 0;
            for (int k = 0; k < lengthb; k++)
                res[i][j] += (a[i][k] * b[k][j]);
        }
    }

    return 1;
}

int sumsubmaitrix(int** a, int length, int width, int& lres, int& wres, int curl, int curw)
{
    int SUm = 0;
    for (int i = 0; i < lres; i++)
        for (int j = 0; j < wres; j++)
            SUm += a[curl + i][curw + j];
    return SUm;
}

//Given a matrix a.Find the submatrix of a which satisfies keyboard input sizeand has the largest total value of its elements.
int** findSubmatrix(int** a, int length, int width, int& lres, int& wres)
{
    cout << "Type the number of length in result matrix: ";
    cin >> lres;
    while (lres <= 0 || lres > length)
    {
        cout << "the number of length is illegal please retype: ";
        cin >> lres;
    }
    cout << "Type the number of width in matrix: ";
    cin >> wres;
    while (wres <= 0 || wres > width)
    {
        cout << "the number of width is illegal please retype: ";
        cin >> wres;
    }
    if (lres == length && wres == width)
        return a;
    int MaxSum = 0;
    

    int isubmax = 0;
    int jsubmax = 0;


    for(int i=0;i<length;i++)
    {
        if (i > length - lres)
            break;
        for (int j = 0; j < width; j++)
        {
            if (j > width - wres)
                break;
            int cur = sumsubmaitrix(a, length, width, lres, wres, i, j);
            if (MaxSum < cur)
            {
                MaxSum = cur;
                isubmax = i;
                jsubmax = j;

            }
        }
    }

    int** resultMatrix = new int* [lres];
    for (int i = 0; i < lres; i++)
    {
        resultMatrix[i] = new int[wres];
        for (int j = 0; j < wres; j++)
        {
            resultMatrix[i][j] = a[isubmax + i][j + jsubmax];
        }
    }

    return resultMatrix;

}

//Sequential Search.
int LinearSearch(int* a, int n, int key)
{
    if (a == NULL)
        return -1;
    for (int i = 0; i < n; i++)
        if (a[i] == key)
            return i;
    return -1;
}

//Sequential Search uses flag.
int SentinelLinearSearch(int* a, int n, int key)
{
    a[n] = key;
    int flag = 0;
    while (a[flag] != key)
    {
        flag++;
    }
    if (flag == n)
        return -1;
    return flag;
}





//. Binary Search in sorted array a.
int BinarySearch(int* a, int n, int key)
{
    int l = 0, r = n - 1;
    int mid = (l + r) / 2;
    while (r > l)
    {
        if (a[mid] == key)
            return mid;
        else if (key > mid)
        {
            l = mid;
            mid = (l + r) / 2;
        }
        else
        {
            r = mid;
            mid = (l + r) / 2;
        }
    }
    return -1;
}



//Binary Search in sorted array a uses recursion.
int RecursiveBinarySearch(int* a, int left, int right, int key) {
    if (left <= right)
    {
        int mid = (left + right) / 2;
        if (a[mid] == key) return mid;

        if (key > a[mid]) return RecursiveBinarySearch(a, mid + 1, right, key);

        if (key < a[mid]) return RecursiveBinarySearch(a, left, mid - 1, key);
    }
    return -1;
}

//------------------------------------------------------------------------------------------


//phần 2 đệ qui 
//-------------------------------------------------------------------------------------------
//Calculate the sum of S = 1 + 2 + 3 + ... + n
int sumof_N(int n)
{
    if (n == 1) return 1;
    return n + sumof_N(n - 1);
}


//. Calculate the factorial n! = 1 ∗ 2 ∗ 3 ∗ ... ∗ n.
int factorial(int n)
{
    if (n == 1) return 1;
    return n * factorial(n - 1);
}


//Calculate x^n
int x_expN(double x,int n)
{
    if (n == 1) return x;
    return x * x_expN(x, n - 1);
}

//Count the number of digits of a given integer.
int count_Numofdigit(int n)
{
    if (n < 10) return 1;
    return 1 + count_Numofdigit(n / 10);
}


//Verify if every digits of given integer are even.
bool alldigitAreEven(int n)
{
    if (n % 2) return 0;
    else if (n < 10 && n % 2 == 0) return 1;
    return alldigitAreEven(n % 10);
}


//Count the number of common divisor of 2 given integers.
int count_NumOfDivisor(int a, int b, int divisor = 2)
{
    if (divisor > a)
        return 0;
    if (a % divisor == 0 && b % divisor == 0)
        return 1 + count_NumOfDivisor(a, b, divisor + 1);
    return count_NumOfDivisor(a, b, divisor + 1);

}


// Calculate the Greatest common divisorand Least common multiple of 2 given integers.
int gcd(int a, int b)
{
    if (a == 0) return b;
    if (b == 0) return a;
    if (a == b) return a;
    return gcd(b, a % b);
}

int lcm(int a, int b)
{
    return a * b / gcd(a, b);
}

int reverse_value(int a)
{
    int NumOfdigit = (int)log10(a);
    if (a < 10) {
        return a;
    }
    return a % 10 * pow(10, NumOfdigit) + reverse_value(a / 10);
}

//Calculate the i
//th Fibonacci number.
//• F0 = 0, F1 = 1
//• Fn = Fn−1 + Fn−2, (n ≥ 2)
int recur_fibonaci(int n)
{
    if (n == 1) return 1;
    if (n == 2) return 1;
    return recur_fibonaci(n - 1) + recur_fibonaci(n - 2);
}

//qui hoạch động 
int fibonaci(int n)
{
    int* fibo = new int[n];
    fibo[0] = 1;
    fibo[1] = 1;
    for (int i = 2; i < n; i++)
        fibo[i] = fibo[i - 1] + fibo[i - 2];
    int result = fibo[n - 1];
    for (int i = 0; i < n; i++)
        cout <<endl<< fibo[i] << "  "<<endl;
    delete[] fibo;
    return result;
}



void deleteMatrix(int**& a, int& length, int& width)
{
    for (int i = 0; i < length; i++)
        delete[]a[i];
    delete[]a;
    a = NULL;
    length = 0;
    width = 0;
}


//hoán vị chuỗi kí tự
void permute(string a, int l, int r)
{
    // Base case 
    if (l == r)
        cout << a << endl;
    else
    {
        // Permutations made 
        for (int i = l; i <= r; i++)
        {

            // Swapping done
            swap(a[l], a[i]);

            // Recursion called 
            permute(a, l + 1, r);

            //backtrack 
            swap(a[l], a[i]);
        }
    }
}
//-----------------------------------------------------------------------------------------



int main()
{
    //Swap 2 given integers.
    /*int a = 10, b = 2;
    swap(&a, &b);
    cout << "a = " << a << '\n' << "b = " << b << endl;*/


    //Calculate the total value of 2 integers.
    /*int a = 11, b = 22;
    cout << "a + b = " << *sum(&a, &b) << endl;*/


    //Input an array with unknown size.
    //Print a given array.
   /*int* a = NULL;
    int n = 0;
    inputArray(a, n);
    printArray(a, n);*/

    //Find the largest value from a given array.
   /* int a[] = { 3,5,7,9,6,4 };
    cout << "Max value of array a is: " << *findMax(a, sizeof(a) / sizeof(int)) << endl;*/


    //Find the longest ascending subarray from a given array.
    /*int a[] = { 3,5,7,9,6,4 };
    int b[] = { 0,1,2,0,1,2,3 };
    int nsubarray = 0;
    cout << "mang con tang dai nhat cua mang a: ";
    printArray(findLongestAscendingSubarray(a, sizeof(a) / sizeof(int),nsubarray),nsubarray);

    cout << "mang con tang dai nhat cua mang b: ";
    printArray(findLongestAscendingSubarray(b, sizeof(b) / sizeof(int), nsubarray), nsubarray);*/



    //Swap 2 given arrays.
    /*int* a;
    int na;
    inputArray(a, na);
    int* b;
    int nb;
    inputArray(b, nb);
    swapArrays(a, b, na, nb);
    printArray(a, na);
    printArray(b, nb);
    delete[]a;
    delete[]b;*/


    //Concatenate 2 given arrays.
    /*int a[] = { 3,5,7,9,6,4 };
    int b[] = { 0,1,2,0,1,2,3 };
    int nc = 0;
    int* c = concatenate2Arrays(a, b, sizeof(a) / sizeof(int), sizeof(b) / sizeof(int), nc);
    printArray( c, nc);
    delete[]c;
    nc = 0;*/



    //Given 2 ascending arrays with distinguish elements.Generate a new ascending array with all elements from the given arrays.
    /*int a[] = { 3,5,7,9 };
    int b[] = { 0,1,2,3 };
    int nc = 0;
    int* c = merge2Arrays(a, b, sizeof(a) / sizeof(int), sizeof(b) / sizeof(int), nc);
    printArray(c, nc);
    delete[]c;
    nc=0;*/


    //Generate a random matrix with keyboard input size.
    /*int** a = NULL;
    int l = 0, w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    deleteMatrix(a, l, w);*/

    
    
    //Given two 1D arrays a and b. Generate the matrix c that c[i][j] = a[i] * b[j].
    /*int a[] = { 3,5,7,9 };
    int b[] = { 0,1,2,3 };
    int** c = NULL;
    int r;
    int col;
    c = generateMatrix2(a, b, sizeof(a) / sizeof(int), sizeof(b) / sizeof(int), r, col);
    printMatrix(c,r,col);
    deleteMatrix(c, r, col);*/


    //Swap 2 columns / rows of a given matrix.
    /*int** a = NULL;
    int l = 0;
    int w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    swapRows(a, l, w, 1, 2);
    printMatrix(a, l, w);
    swapColumns(a, l, w, 1, 2);
    printMatrix(a, l, w);
    deleteMatrix(a, l, w);*/

    //Generate the transpose matrix of a given matrix.
    /*int** a = NULL;
    int l = 0;
    int w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    int**b=transposeMatrix(a, l, w);
    printMatrix(b, w, l);
    deleteMatrix(a, l, w);
    deleteMatrix(b, w, l);*/


    //Concatenate 2 given size-equal matrices, horizontally / vertically.
    /*int** a = NULL;   //test nối theo chiều ngang
    int l = 0;
    int w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    int** b = NULL;
    generateMatrix1(b, l, w);
    printMatrix(a, l, w);
    int** c = NULL;
    int lc = 0;
    int wc = 0;
    c = concatenate2MatricesH(a, b, l, w, lc, wc);
    printMatrix(c,lc,wc);
    int la = l, wa = w;
    deleteMatrix(a, la, wa);
    deleteMatrix(b, l, w);
    deleteMatrix(c, lc, wc);
*/


    //int** a = NULL;     //test nối theo chiều dọc
    //int l = 0;
    //int w = 0;
    //generateMatrix1(a, l, w);
    //printMatrix(a, l, w);
    //int** b = NULL;
    //generateMatrix1(b, l, w);
    //printMatrix(b, l, w);
    //int** c = NULL;
    //int lc = 0;
    //int wc = 0;
    //c = concatenate2MatricesV(a, b, l, w, lc, wc);
    //printMatrix(c, lc, wc);
    //int la = l, wa = w;
    //deleteMatrix(a, la, wa);
    //deleteMatrix(b, l, w);
    //deleteMatrix(c, lc, wc);


    //Multiple 2 given matrices.
    /*int** a = NULL;     
    int l = 0;
    int w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    int** b = NULL;
    int lb = 0;
    int wb = 0;
    generateMatrix1(b, lb, wb);
    printMatrix(b, lb, wb);
    int** c = NULL;
    int lc;
    int wc;
    int exist_c = multiple2Matrices(c, a, b, lc, wc, l, w, lb, wb);
    if (exist_c == 0)
        cout << "Khong ton tai tich cua a va b" << endl;
    else
        printMatrix(c, lc, wc);
    deleteMatrix(a, l, w);
    deleteMatrix(b, lb, wb);
    deleteMatrix(c, lc, wc);*/

    //Given a matrix a.Find the submatrix of a which satisfies keyboard input sizeand has the largest total value of its elements.
    /*int** a = NULL;
    int l = 0;
    int w = 0;
    generateMatrix1(a, l, w);
    printMatrix(a, l, w);
    int** c = NULL;
    int lc;
    int wc;
    c = findSubmatrix(a, l, w, lc, wc);
    printMatrix(c, lc, wc);
    deleteMatrix(a, l, w);
    deleteMatrix(c, lc, wc);*/

    //Sequential Search.
    /*int a[] = { 1,2,3,4,5,6,7,8,9 };
    int na = sizeof(a) / sizeof(int);
    cout << LinearSearch(a, na, 9) << endl;*/


    //Sequential Search uses flag.
    /*int a[] = { 1,2,3,4,5,6,7,8,9 };
    int na = sizeof(a) / sizeof(int);
    cout << SentinelLinearSearch(a, na, 9) << endl;*/

    //. Binary Search in sorted array a.
    /*int a[] = { 2,4,6,8,10,12,14,16,18,20 };
    int na = sizeof(a) / sizeof(int);
    cout << BinarySearch(a, na, 18) << endl;*/

    //Binary Search in sorted array a uses recursion.
    /*int a[] = { 2,4,6,8,10,12,14,16,18,20 };
    int na = sizeof(a) / sizeof(int);
    cout << RecursiveBinarySearch(a, 0, na - 1, 16) << endl;*/

    
    ////Calculate the sum of S = 1 + 2 + 3 + ... + n
    //cout << sumof_N(10) << endl;
    ////. Calculate the factorial n! = 1 ∗ 2 ∗ 3 ∗ ... ∗ n.
    //cout << factorial(5) << endl;
    //

    ////Calculate x^n
    //cout << x_expN(4, 4) << endl;

    ////Count the number of digits of a given integer.
    //cout << count_Numofdigit(123456) << endl;
    ////Verify if every digits of given integer are even.
    //cout << alldigitAreEven(2468) << endl;
    //cout << alldigitAreEven(12345) << endl;

    ////Count the number of common divisor of 2 given integers.
    //cout << count_NumOfDivisor(12, 18) << endl;


    //// Calculate the Greatest common divisorand Least common multiple of 2 given integers.
    //cout << gcd(12, 18) << ' ' << lcm(12, 18) << endl;

    //cout << reverse_value(1234567) << endl;

    //cout << recur_fibonaci(5) << ',' << fibonaci(5) << endl;
    //permute("ABC", 0, 2);


    return 0;

}