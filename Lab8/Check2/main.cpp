//
// Created by MSI on 14.02.2020.
//
#include <fstream>

using namespace std;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");


    int a[100][100] = {};
    bool is = true;
    int n, m;
    fin >> n >> m;
    for (int i = 0; i < m; ++i) {
        int x, y;
        fin >> y >> x;
        a[x - 1][y - 1]++;
        if (x != y)
            if (a[x - 1][y - 1]>1 or a[y - 1][x - 1]>0)
                goto end;
    }

    is = false;
    end:;
    fout << (is ? "YES" : "NO");
    fin.close();
    fout.close();
    return 0;
}