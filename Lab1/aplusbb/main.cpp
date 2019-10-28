#include <iostream>
#include <fstream>

using namespace std;

ifstream fin("aplusbb.in");
ofstream fout("aplusbb.out");


int main()
{
    long long a, b;
    fin>>a>>b;
    fout<<a+b*b;
    return 0;
}

