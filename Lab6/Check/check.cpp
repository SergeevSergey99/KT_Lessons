//
// Created by Sergey on 26.11.2019.
//

#include <fstream>
#include <string>

using namespace std;
long long vals[200010];
long long lefts[200010];
long long rights[200010];

bool check(long long i, long long lo, long long hi) {


    if (vals[i] < lo || vals[i] > hi)
        return false;
    if (lefts[i] == 0 && rights[i] == 0) {


        return true;
    }
/*1    bool l = true, r = true;
    if (lefts[i] != 0) {
        if (vals[i] > vals[lefts[i]])
            l = check(lefts[i]);
        else
            l = false;
    }
    if (rights[i] != 0) {
        if (vals[i] < vals[rights[i]])
            r = check(rights[i]);
        else
            r = false;
    }
    return l && r;*/


    bool l = true, r = true;
    if (lefts[i] != 0)
        l = check(lefts[i], lo, vals[i]);
    if (rights[i] != 0)
        r = check(rights[i], vals[i], hi);
    return l && r;
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("check.in");
    fout.open("check.out");
    //ios_base::sync_with_stdio(false);

    long long n;
    fin >> n;

    if (n == 0) {
        fout << "YES";
        fin.close();
        fout.close();
        return 0;
    }

    for (long long i = 1; i <= n; i++) {

        fin >> vals[i] >> lefts[i] >> rights[i];
    }

    fout << (check(1, -99999999999, 99999999999) ? "YES" : "NO");
    fin.close();
    fout.close();
    return 0;
}