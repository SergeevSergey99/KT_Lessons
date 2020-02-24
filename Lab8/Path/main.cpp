//
// Created by MSI on 24.02.2020.
//
#include <fstream>
#include <vector>

#define INF 1000000000

using namespace std;

struct edge {
    int a, b;
};

int n, m, v = 0;
vector<edge> e;




int main() {
    ifstream fin("pathbge1.in");
    ofstream fout("pathbge1.out");

    fin >> n >> m;

    for (int i = 0; i < m; ++i) {
        edge e1;
        fin >> e1.a >> e1.b;
        e1.a -=1;
        e1.b -=1;
        int tmp = min(e1.a, e1.b);
        e1.b = e1.a + e1.b - tmp;
        e1.a = tmp;
        e.push_back(e1);
    }



    vector<int> d(n, INF);

    d[v] = 0;
    for (;;) {
        bool any = false;
        for (int j = 0; j < m; ++j) {   //    if (d[e[j].a] < INF)
            if (d[e[j].b] > d[e[j].a] + 1) {
                d[e[j].b] = d[e[j].a] + 1;
                any = true;
            }
            if (d[e[j].a] > d[e[j].b] + 1) {
                d[e[j].a] = d[e[j].b] + 1;
                any = true;
            }
        }
        if (!any) break;
    }

    for (int k = 0; k < n; ++k) {
        fout << d[k] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}