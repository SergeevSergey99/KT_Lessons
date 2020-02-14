//
// Created by MSI on 14.02.2020.
//
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");


    int a[100][100];
    bool is = false;
    int n;
    fin >> n;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            fin >> a[j][i];
            if (i == j && a[j][i] != 0)
                goto end;
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (a[j][i] != a[i][j])
                goto end;
        }
    }

    is = true;
end:;
    fout << (is ? "YES" : "NO");

    fin.close();
    fout.close();
    return 0;
}