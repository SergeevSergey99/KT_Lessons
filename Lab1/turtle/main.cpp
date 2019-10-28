#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

ifstream fin("turtle.in");
ofstream fout("turtle.out");

int a, b;
int mas[1000][1000];


int main() {
    fin >> a >> b;

    for (int i = 0; i < a; ++i) {
        for (int j = 0; j < b; ++j) {
            fin >> mas[i][j];
        }
    }


    for (int i = a - 1; i >= 0; --i) {

        for (int j = 0; j < b; ++j) {
            if (i == a - 1 && j == 0) continue;
            if (i == a - 1) {
                mas[i][j] += mas[i][j - 1];
                continue;
            }
            if (j == 0) {
                mas[i][j] += mas[i + 1][j];
                continue;
            }
            mas[i][j] += max(mas[i + 1][j], mas[i][j - 1]);

        }
    }

    fout << mas[0][b-1];
    return 0;
}