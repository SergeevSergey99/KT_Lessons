#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("aplusb.in");
ofstream fout("aplusb.out");


int main()
{
    int a, b;
    fin>>a>>b;
    fout<<a+b;
    return 0;
}

