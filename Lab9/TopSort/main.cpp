//
// Created by MSI on 28.02.2020.
//

#include <fstream>
#include <vector>
#include <algorithm>
#include <iostream>

#define MAXN 100000
using namespace std;

int n; // число вершин
vector<int> g[MAXN]; // граф
int used[MAXN];
vector<int> ans;

bool dfs(int v) {
    used[v] = true;
    for (size_t i = 0; i < g[v].size(); ++i) {
        int to = g[v][i];
        if (used[to] == 0)
        {
            if(dfs(to))
                return true;
        }
        else if(used[to] == 1)
        {
            return true;
        }

    }
    used[v] = 2;
    ans.push_back(v);
    return false;
}

bool topological_sort() {
    for (int i = 0; i < n; ++i)
        used[i] = false;
    ans.clear();
    for (int i = 0; i < n; ++i)
        if (!used[i])
            if(dfs(i))
            {
                ans.clear();
                return false;
            }
    reverse(ans.begin(), ans.end());
    return true;
}


int main() {
    ifstream fin("topsort.in");
    ofstream fout("topsort.out");

    int m;
    fin >> n >> m;


    for (int i = 0; i < m; ++i) {

        int a;
        int b;
        fin >> a >> b;

        g[a-1].push_back(b-1);

    }

    cout<<(topological_sort()?"":"-1");


    for (int j = 0; j < ans.size(); ++j) {
        cout << ans[j]+1 << ' ';
    }

    fin.close();
    fout.close();
    return 0;
}