#include <fstream>
#include <string>

using namespace std;

struct node // структура для представления узлов дерева
{
    int key;
    unsigned char height;
    node *left;
    node *right;

    explicit node(int k) {
        key = k;
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

node *insert(node *p, int k) // вставка ключа k в дерево с корнем p
{
    if (!p) return new node(k);
    if (k == p->key) return balance(p);
    if (k < p->key)
        p->left = insert(p->left, k);
    else
        p->right = insert(p->right, k);
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

node *remove(node *p, int k) // удаление ключа k из дерева p
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

bool isIn(node *p, int k) //поиск узла с ключем k из дерева p
{
    if (p->key == k) return true;
    if (p->key < k) {
        if (p->right != nullptr)
            return isIn(p->right, k);
        else
            return false;
    }
    if (p->key > k) {
        if (p->left != nullptr)
            return isIn(p->left, k);
        else
            return false;
    }

    return false;
}
struct tree
{
    node* root;
};
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("set.in");
    fout.open("set.out");
    ios_base::sync_with_stdio(false);

    string command;
    int val;
    while ((command != "insert") && !fin.eof()) {

        string str;
        getline(fin, str);
        if (str.length() < 5)continue;
        command = str.substr(0, 6);
        val = stoi(str.substr(6));

        if (command == "exists")
            fout << "false\n";
    }

    tree tr;
    tr.root = new node(val);
    node *r = tr.root;
    while (!fin.eof()) {
        string str;
        getline(fin, str);
        if (str.length() < 5)continue;
        command = str.substr(0, 6);
        val = stoi(str.substr(6));


        if (command == "insert") {
            if (r == nullptr)
                r = new node(val);
            else
               r = insert(r, val);
        }
        if (command == "delete") {
            if (r != nullptr)
                r = remove(r, val);
        }
        if (command == "exists")
            if (r != nullptr)
                fout << (isIn(r, val) ? "true\n" : "false\n");
            else
                fout << "false\n";
    }

    fin.close();
    fout.close();
    return 0;
}