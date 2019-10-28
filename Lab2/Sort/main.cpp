#include <fstream>

long long a[100000];
std::ifstream fin("sort.in");
std::ofstream fout("sort.out");

void quicksort(long long l,long long r) {
    long long i = l, j = r;
    long long x = a[(l + r) / 2];
    while (i <= j)
    {
        while (a[i] < x) { i++; }
        while (a[j] > x) { j--; }
        if (i <= j) { std::swap(a[i++], a[j--]); }

    }
    if (i < r) { quicksort(i, r); }
    if (l < j) { quicksort(l, j); }
}

int main() {
    std::ios::sync_with_stdio(false);

    long long n;
    fin >> n;
    for (long long i = 0; i < n; i++) {
        fin >> a[i];
    }
    quicksort(0, n - 1);
    for (long long i = 0; i < n; i++) {
        fout << a[i] << " ";
    }
    fin.close();
    fout.close();
    return 0;
}