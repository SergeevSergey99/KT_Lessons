//
// Created by MSI on 16.12.2019.
//

#include <fstream>

using namespace std;

int main() {
    ofstream fout;
    fout.open("linkedmap.in");

    string com[] = {"put", "delete", "get", "before", "after"};

    for (int i = 0; i < 350000; ++i) {
        string c, k, v;
        c = com[rand() % com->length()];
        k = (rand() % 50) + 70;
        fout << c << " " << k;

        for (int j = 0; j < 15; ++j) {
            fout<<k;
        }

        if(c.compare("put") == 0)
        {
            v = (rand() % 50) + 70;
            fout << " " << v;
            v = (rand() % 50) + 70;
            fout << v;
            v = (rand() % 50) + 70;
            fout << v;

        }
        fout << endl;
    }

    fout.close();
    return 0;
}