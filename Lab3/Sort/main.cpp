#include <fstream>

long long a[1000000];
std::ifstream fin("sort.in");
std::ofstream fout("sort.out");

void Swap( long long  *A, long long *B )
{
    long long tmp = *A;

    *A = *B;
    *B = tmp;
}
void HeapCorrection( long long *A, long long N, long long i )
{
    long long l, r, best;

    while(1)
    {
        l = 2 * i + 1;
        r = 2 * i + 2;
        best = i;

        if (l < N && A[i] < A[l])
            best = l;
        if (r < N && A[best] < A[r])
            best = r;
        if (best == i)
            return;
        Swap( &A[i], &A[best]);
        i = best;
    }
}
void HeapSort(long long *A, long long N)
{
    long long i;

    for (i = N / 2 - 1; i >= 0; i--)
        HeapCorrection( A, N, i);
    while (N-- > 1)
    {
        Swap( &A[0], &A[N]);
        HeapCorrection( A, N, 0);
    }
}

int main() {
    std::ios::sync_with_stdio(false);

    long long n;
    fin >> n;
    for (long long i = 0; i < n; i++) {
        fin >> a[i];
    }
    HeapSort(a, n);
    for (long long i = 0; i < n; i++) {
        fout << a[i] << " ";
    }
    fin.close();
    fout.close();
    return 0;
}