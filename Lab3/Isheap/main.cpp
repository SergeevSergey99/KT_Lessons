#include <fstream>

using namespace std;

long a[100000];
ifstream fin("isheap.in");
ofstream fout("isheap.out");


int main() {
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        fin >> a[i];
    }

    for (int j = 0; j < n; ++j) {
        if (j * 2 + 1 < n)
            if (a[j] > a[j * 2 + 1]) {
                fout << "NO";
                return 0;
            }
        if (j * 2 + 2 < n)
            if (a[j] > a[j * 2 + 2]) {
                fout << "NO";
                return 0;
            }
    }

    fout << "YES";
    return 0;
}