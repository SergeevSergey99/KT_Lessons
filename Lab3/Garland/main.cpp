#include <iostream>
#include <fstream>
#include <iomanip>

#define EPS 0.000001
using namespace std;
ifstream fin("garland.in");
ofstream fout("garland.out");


int main() {

    ios::sync_with_stdio(false);
    cin.tie(NULL);


    int n;
    double A, res;

    fin>>n>>A;

    double l = 0;
    double r = A;
    while (r - l > EPS)
    {
        double m = (r - l) / 2 + l;

        double min = A;
        double x[1000];
        x[0] = A;
        x[1] = m;
        for (int i = 2; i < n; i++) {
            x[i] = 2 * x[i - 1] - x[i - 2] + 2;
            if (x[i] < min) {
                min = x[i];
            }
        }
        res = x[n -1];

        if (min >= 0) {
            r = m;
        } else {
            l = m;
        }
    }

    fout << std::fixed << std::setprecision(2);
    fout<<res;

    fin.close();
    fout.close();
    return 0;
}