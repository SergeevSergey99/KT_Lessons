#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("sortland.in");
ofstream fout("sortland.out");
int32_t n;
float a[10000];
float index[10000];

void findk(int l, int r, int k) {
    int i = l;
    int j = r;
    float x = a[(l + r) / 2];

    while (i <= j) {
        while (a[i] < x) { i++; }
        while (a[j] > x) { j--; }
        if (i <= j) {
            swap(a[i], a[j]);
            swap(index[i], index[j]);
            i++;
            j--;
        }
    }

    if (k <= j) {
        findk(l, j, k);
    } else if (k >= i) {
        findk(i, r, k);
    } else {
        fout << index[k] << " ";
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    fin >> n;
    int k1 = 0;
    int k2 = n - 1;
    int k3 = n >> 1;
    for (int i = 0; i < n; i++) {
        fin >> a[i];
        index[i] = i + 1;
    }

    findk(0, n - 1, k1);
    findk(0, n - 1, k3);
    findk(0, n - 1, k2);
    fin.close();
    fout.close();
    return 0;
}