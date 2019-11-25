#include <fstream>
#include <regex>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

struct node // структура для представления узлов дерева
{
    string key;
    string value;
    unsigned char height;
    node *left;
    node *right;

    explicit node(string k, string val) {
        key = k;
        value = val;
        left = right = nullptr;
        height = 1;
    }
};

unsigned char height(node *p) {
    return p ? p->height : 0;
}

int bfactor(node *p) {
    return height(p->right) - height(p->left);
}

void fixheight(node *p) {
    unsigned char hl = height(p->left);
    unsigned char hr = height(p->right);
    p->height = (hl > hr ? hl : hr) + 1;
}

node *rotateright(node *p) // правый поворот вокруг p
{
    node *q = p->left;
    p->left = q->right;
    q->right = p;
    fixheight(p);
    fixheight(q);
    return q;
}

node *rotateleft(node *q) // левый поворот вокруг q
{
    node *p = q->right;
    q->right = p->left;
    p->left = q;
    fixheight(q);
    fixheight(p);
    return p;
}

node *balance(node *p) // балансировка узла p
{
    fixheight(p);
    if (bfactor(p) == 2) {
        if (bfactor(p->right) < 0)
            p->right = rotateright(p->right);
        return rotateleft(p);
    }
    if (bfactor(p) == -2) {
        if (bfactor(p->left) > 0)
            p->left = rotateleft(p->left);
        return rotateright(p);
    }
    return p; // балансировка не нужна
}

node *insert(node *p, string k, string v) // вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k, v);
    if (k == p->key)
    {
        p->value = v;
        return balance(p);
    }
    if (k < p->key)
        p->left = insert(p->left, k, v);
    else
        p->right = insert(p->right, k, v);
    return balance(p);
}

node *findmin(node *p) // поиск узла с минимальным ключом в дереве p
{
    return p->left ? findmin(p->left) : p;
}

node *removemin(node *p) // удаление узла с минимальным ключом из дерева p
{
    if (p->left == nullptr)
        return p->right;
    p->left = removemin(p->left);
    return balance(p);
}

node *remove(node *p, string k) // удаление ключа k из дерева p
{
    if (!p) return nullptr;
    if (k < p->key)
        p->left = remove(p->left, k);
    else if (k > p->key)
        p->right = remove(p->right, k);
    else //  k == p->key
    {
        node *q = p->left;
        node *r = p->right;
        delete p;
        if (!r) return q;
        node *min = findmin(r);
        min->right = removemin(r);
        min->left = q;
        return balance(min);
    }
    return balance(p);
}

string isIn(node *p, string k) //поиск узла с ключем k из дерева p
{
    if (p->key == k) return p->value + "\n";
    if (p->key < k) {
        if (p->right != nullptr)
            return isIn(p->right, k);
        else
            return "none\n";
    }
    if (p->key > k) {
        if (p->left != nullptr)
            return isIn(p->left, k);
        else
            return "none\n";
    }

    return "none\n";
}
struct tree
{
    node* root;
};


int main() {
    ifstream fin;
    ofstream fout;
    fin.open("map.in");
    fout.open("map.out");
    ios_base::sync_with_stdio(false);

    string command;
    string key;
    string val;



    while ((command != "put") && !fin.eof()) {

        string str;
        getline(fin, str);
        if (str.length() < 2) continue;

        vector<string> results = split(str, ' ');
        command = results[0];
        key = results[1];
        if(command == "put")
            val = results[2];

        if (command == "get")
            fout << "none\n";
    }

    tree tr;
    tr.root = new node(key, val);
    node *r = tr.root;
    while (!fin.eof()) {
        string str;
        getline(fin, str);

        if (str == "") continue;
        vector<string> results = split(str, ' ');
        command = results[0];
        key = results[1];
        if(command == "put")
            val = results[2];

        if (command == "put") {
            if (r == nullptr)
                r = new node(key, val);
            else
                r = insert(r, key, val);
        }
        if (command == "delete") {
            if (r != nullptr)
                r = remove(r, key);
        }
        if (command == "get")
            if (r != nullptr)
                fout << isIn(r, key);
            else
                fout << "none\n";
    }

    fin.close();
    fout.close();
    return 0;
}