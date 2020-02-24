//
// Created by MSI on 23.02.2020.
//

#include <fstream>
#include <vector>

#define MAXN 100000
using namespace std;


int n;
vector<int> g[MAXN];
bool used[MAXN];
int results[MAXN];
vector<int> comp;
int cnt = 1;

void dfs(int v) {
    used[v] = true;
    comp.push_back(v);
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (!used[to])
            dfs(to);
    }
}

void find_comps() {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    for (int i = 0; i < n; ++i)
        if (!used[i]) {
            comp.clear();
            dfs(i);

            for (size_t j = 0; j < comp.size(); ++j) {
                results[comp[j]] = cnt;
            }
            cnt++;
        }
}


int main() {
    ifstream fin("components.in");
    ofstream fout("components.out");

    int m;
    fin >> n >> m;

//    short a[100000] = {};

    for (int i = 0; i < m; ++i) {
        int b, e;
        fin >> b;
        fin >> e;

        g[b - 1].push_back(e - 1);
        g[e - 1].push_back(b - 1);
    }

    find_comps();

    fout << cnt - 1 << endl;
    for (int j = 0; j < n; ++j) {
        fout << results[j] << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}