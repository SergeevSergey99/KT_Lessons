#include <fstream>
#include <stack>

using namespace std;

int main() {
    ifstream fin;
    ofstream fout;

    fin.open("brackets.in");
    fout.open("brackets.out");

    char symbol;
    stack<char> st;

    int i = 0;
    while (!fin.eof()) {
            fin.get(symbol);
        if (symbol == '\n' || fin.eof())
        {

            if (st.empty())
            {
                if(i != 0)
                    fout << "YES\n";

            }
            else
                fout << "NO\n";
            while (!st.empty())
                st.pop();
            i = 0;
            continue;
        }

        if (st.size() > 0)
            if ((st.top() == '(' && symbol == ')') ||
                (st.top() == '[' && symbol == ']')
                || (st.top() == '{' && symbol == '}'))
            {
                st.pop();
                continue;
            }
        i++;
        st.push(symbol);
    }


    fin.close();
    fout.close();
    return 0;
}