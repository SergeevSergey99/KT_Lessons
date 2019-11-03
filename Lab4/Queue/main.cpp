#include <fstream>
#include <queue>

using namespace std;
ifstream fin;
ofstream fout;


int main() {
    fin.open("queue.in");
    fout.open("queue.out");
    int n;
    char command;
    queue<int> que;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> command;
        if (command == '+')
        {
            int tmp;
            fin>>tmp;
            que.push(tmp);
        }
        else if (command == '-')
        {
            fout << que.front() << endl;
            que.pop();
        }
    }
    return 0;
}