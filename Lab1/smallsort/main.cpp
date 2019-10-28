#include <iostream>
#include <fstream>

using namespace std;

long a[100000];
ifstream fin("smallsort.in");
ofstream fout("smallsort.out");

void quicksort(int l, int r) {
    int i = l, j = r;
    long x = a[(l+r)/2];
    while (i<=j) {
        while (a[i] < x) {i++;}
        while (a[j] > x) {j--;}
        if (i <= j) {swap(a[i++], a[j--]);}
    }
    if (i < r) {quicksort(i,r);}
    if (l < j) {quicksort(l,j);}
}

int main() {

    int n;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> a[i];
    }
    quicksort(0,n-1);
    for(int i = 0; i < n; i++){
        fout << a[i] << " ";
    }
    fin.close();
    fout.close();
    return 0;
}