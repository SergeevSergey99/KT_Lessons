//
// Created by MSI on 14.02.2020.
//
#include <fstream>

using namespace std;

int main() {

    ifstream fin("input.txt");
    ofstream fout("output.txt");


    int n, m;
    fin >> n >> m;
    int a[100][100] = {};
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> y >> x;
        a[x - 1][y - 1] = 1;
    }
    for (int j = 0; j < n; ++j) {
        for (int i = 0; i < n; ++i) {
            fout << a[i][j] << (i == n - 1? "\n":" ");
        }
    }

    fin.close();
    fout.close();
    return 0;
}