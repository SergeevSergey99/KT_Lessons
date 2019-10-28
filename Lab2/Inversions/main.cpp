#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin("inversions.in");
ofstream fout("inversions.out");

#define LEN 100000
unsigned long long mas[LEN] = {0};
using namespace std;

unsigned long long cnt = 0;

void fill(int n) {
    for (int i = 0; i < n; i++) {
        fin>>mas[i];
    }
}

unsigned long long B[LEN];
void MergeSortRec( unsigned long long *A,  unsigned long N )
{
    unsigned long M, k, i = 0, j = N / 2;

    if (N < 2)
        return;
    M = N / 2;
    MergeSortRec( A, M );
    MergeSortRec( A + M, N - M );
    for (k = 0; k < N; k++){
        if (j >= N || i < M && A[i] <= A[j]) {
            B[k] = A[i++];
        }
        else {
            B[k] = A[j++];
            //    if (k<M)
            cnt+= M - i;
        }
    }
    for (k = 0; k < N; k++)
        A[k] = B[k];
}
void MergeSort(unsigned long long *A, unsigned long N)
{
    MergeSortRec( A, N );
}

int main() {
    int n;
    fin >> n;

    fill(n);

    MergeSort(mas,n);

    fout<<endl<<cnt<<endl;

    return 0;
}