#include <fstream>
#include <stack>

using namespace std;
ifstream fin;
ofstream fout;


int main() {
    fin.open("stack.in");
    fout.open("stack.out");
    int n;
    char command;
    stack<int> st;
    fin >> n;
    for(int i = 0; i < n; i++) {
        fin >> command;
        if (command == '+')
        {
            int tmp;
            fin>>tmp;
            st.push(tmp);
        }
        else if (command == '-')
        {
            fout << st.top() << endl;
            st.pop();
        }
    }
    return 0;
}