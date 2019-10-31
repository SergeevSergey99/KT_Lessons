#include <iostream>
#include <fstream>

using namespace std;

long a[100000];
long a_m[100000];
ifstream fin("binsearch.in");
ofstream fout("binsearch.out");

int binsearch(int num, int start, int end){
    int index = -1;
    int middle = (start + end)/2;

    if (start == end && a[middle] != num) return -1;
    if (a[middle] > num) index = binsearch(num, start, middle);
    if (a[middle] < num) index = binsearch(num, middle + 1, end);
    if (a[middle] == num) index = middle;

    return index;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    int n = 0;

    if(fin.is_open())
        n = 1;
    fin >> n;
    for (int i = 0; i < n; i++){
        fin >> a[i];
    }
    int m;
    fin >> m;
    for (int i = 0; i < m; i++){
        fin >> a_m[i];
        int index = binsearch(a_m[i],0,n);
        if (index == -1){
            fout<<"-1 -1\n";
            continue;
        }
        int j = index;
        while (j > -1 && a[j] == a[index]){j--;}
        fout<<j + 2<<" ";
        j = index;
        while (j < n && a[j] == a[index]){j++;}
        fout<<j<<"\n";
    }



    fin.close();
    fout.close();
    return 0;
}