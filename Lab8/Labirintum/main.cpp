//
// Created by MSI on 24.02.2020.
//


#include <fstream>
#include <vector>
#include <iostream>

#define INF 1000000000

using namespace std;


struct edge {
    int a, b;
};

int n, m, v = 0;
vector<edge> e;

int main() {
    ifstream fin("input.txt");
    ofstream fout("output.txt");

    int n, m;

    char labir[100][100];

    fin >> n >> m;

    int S,T;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            fin>>labir[j][i];
            if(labir[j][i] == 'S')
                S = j + i*m;
            if(labir[j][i] == 'T')
                T = j + i*m;
            if(labir[j][i] == '.' or labir[j][i] == 'S' or labir[j][i] == 'T')
            {
                if(j > 0){
                    if(labir[j][i] == '.' or labir[j][i] == 'S' or labir[j][i] == 'T')
                    {
                        edge e1;
                        e1.a = j + i*m;
                        e1.b = j - 1 + i*m;
                        e.push_back(e1);
                    }
                }
                if(i > 0){
                    if(labir[j][i] == '.' or labir[j][i] == 'S' or labir[j][i] == 'T')
                    {
                        edge e1;
                        e1.a = j + i*m;
                        e1.b = j + (i-1)*m;
                        e.push_back(e1);
                    }
                }
            }
        }
    }


    v = S;

    vector<int> d(n*m, INF);

    d[v] = 0;
    for (;;) {
        bool any = false;
        for (int j = 0; j < e.size(); ++j) {   //    if (d[e[j].a] < INF)
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

 /*   for (int k = 0; k < n*m; ++k) {
        fout << d[k] << ' ';
    }
*/
    string way = "";
    int cur = T;
    if (d[T] == INF)
    {
        fout << -1;
        goto end;
    }
    fout<<d[T]<<endl;

    for (int l = 1; l <= d[T]; ++l) {
 //       cout<<d[cur];
        if(cur%m - 1 >= 0 and labir[(cur-1)%m][(cur-1)/m] != '#' and d[cur - 1] == d[T]-l) //left
        {
            cur = cur - 1;
            way = "R" + way;
            continue;
        }
        if(cur + 1 < n * m and labir[(cur+1)%m][(cur+1)/m] != '#' and d[cur + 1] == d[T]-l) //right
        {
            cur = cur + 1;
            way = "L" + way;
            continue;
        }
        if(cur - m >= 0 and labir[(cur-m)%m][(cur-m)/m] != '#' and d[cur - m] == d[T]-l) //up
        {
            cur = cur - m;
            way = "D" + way;
            continue;
        }
        if(cur + m < n*m and labir[(cur+m)%m][(cur+m)/m] != '#' and d[cur + m] == d[T]-l) //down
        {
            cur = cur + m;
            way = "U" + way;
            continue;
        }
    }

    fout<<way;
    end:
    fin.close();
    fout.close();
    return 0;
}
