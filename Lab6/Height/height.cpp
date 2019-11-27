#include <fstream>
#include <string>
#include <vector>

using namespace std;
int lefts[200000];
int rights[200000];

int height(int hght, int i) {

    if(lefts[i] == 0 && rights[i] == 0) return hght;
    int l = 0, r = 0;
    if (lefts[i] != 0) l = height(hght + 1, lefts[i]);
    if (rights[i] != 0) r = height(hght + 1, rights[i]);
    return (l > r ? l : r);
}

int main() {
    ifstream fin;
    ofstream fout;
    fin.open("height.in");
    fout.open("height.out");
    ios_base::sync_with_stdio(false);

    int n;
    fin >> n;
    for (int i = 1; i <= n; i++) {
        int a;
        fin >> a >> lefts[i] >> rights[i];
    }

    if (n == 0)
    {
        fout<<"0";
        return 0;
    }
    int hght = height(1,1);
    fout<<hght;
    fin.close();
    fout.close();
    return 0;
}