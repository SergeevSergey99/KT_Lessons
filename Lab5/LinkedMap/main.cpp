//
// Created by Sergey on 03.12.2019.
//
#include <fstream>
#include <vector>
#include <sstream>
//#include <chrono>

#define LEN 4096
using namespace std;

struct node // структура для представления элементов хеш таблицы
{
public:
    string key;
    string value;
    int hash;

    node *next;
    node *after;
    node *before;
/*
    node() {
        key = nullptr;
        value = nullptr;
        after = before = nullptr;
        hash = -1;
    }*/

    explicit node(string k, string v, int h) {
        key = k;
        value = v;
        after = nullptr;
        next = nullptr;
        before = nullptr;
        hash = h;
    }
};
int k_for_hash[20] = {73, 53, 11, 7, 17,
                      3, 37, 41, 1, 51,
                      1, 0, 5, 97, 13,
                      3, 37, 2, 61, 29
};
int _hash(string str) {
    int n = str.length() & 7;
    int sum = str[0];
    for (int i = 0; i < n; ++i) {
        sum += (unsigned int) str[i] * k_for_hash[i];
    }
    return  (sum) & (LEN-1);
}

struct LinkedMap {
    node *table[LEN] = {};
    node *cur = nullptr;
};
LinkedMap linkedMap;

void add(string key, string val) {
        int i = _hash(key);
        node *now = linkedMap.table[i];

        if (now == nullptr) {
            linkedMap.table[i] = new node(key, val, i);
            if (linkedMap.cur == nullptr)
                linkedMap.cur = linkedMap.table[i];
            else {
                linkedMap.cur->after = linkedMap.table[i];
                linkedMap.table[i]->before = linkedMap.cur;
                linkedMap.cur = linkedMap.table[i];
            }
            return;
        }
        while ((now->next != nullptr) and (now->key != key)) {
            now = now->next;
        }
        if (now->key == key) {
            now->value = val;
            return;
        }

        now->next = new node(key, val, i);
        now->next->before = linkedMap.cur;
        linkedMap.cur->after = now->next;
        linkedMap.cur = now->next;
    }
    void remove(string key) {
        int i = _hash(key);

        node *now = linkedMap.table[i];
        node *prev = nullptr;
        if (now == nullptr)
            return;
        if (linkedMap.table[i]->key == key)
        {

            if (linkedMap.cur == now)
                linkedMap.cur = linkedMap.cur->before;
            node *after = now->after;
            node *before = now->before;
            if (after != nullptr)
                after->before = before;
            if (before != nullptr)
                before->after = after;

            node *nxt = linkedMap.table[i]->next;
            delete (linkedMap.table[i]);
            linkedMap.table[i] = nxt;
            return;
        }
        while (now != nullptr) {

            if (now->key == key)
                break;
            prev = now;
            now = now->next;
        }
        if (now == nullptr)
            return;

        if (linkedMap.cur == now)
            linkedMap.cur = linkedMap.cur->before;
        node *after = now->after;
        node *before = now->before;
        if (prev != nullptr)
            prev->next = now->next;
        if (after != nullptr)
            after->before = before;
        if (before != nullptr)
            before->after = after;
        delete (now);

    }
    string get(string key) {
        int i = _hash(key);
        node *now = linkedMap.table[i];

        if (now == nullptr)
            return "none";
        while ((now->next != nullptr) and (now->key != key)) {
            now = now->next;
        }
        if (now->key == key)
            return now->value;
        return "none";
    }
    string next(string key) {
        int i = _hash(key);
        node *now = linkedMap.table[i];

        if (now == nullptr)
            return "none";
        while ((now->next != nullptr) and (now->key != key)) {
            now = now->next;
        }
        if (now->key == key and now->after != nullptr)
            return now->after->value;
        return "none";
    }
    string prev(string key) {
        int i = _hash(key);
        node *now = linkedMap.table[i];

        if (now == nullptr)
            return "none";
        while ((now->next != nullptr) and (now->key != key)) {
            now = now->next;
        }
        if (now->key == key and now->before != nullptr)
            return now->before->value;
        return "none";
    }
//};
std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
int main() {


  //  auto start = std::chrono::system_clock::now();

    ios_base::sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("linkedmap.in");
    fout.open("linkedmap.out");



    string command;
    string key;
    string val;

    while (!fin.eof()) {

        string str;
        getline(fin, str);
        if (str.length() < 2) continue;

        vector<string> results = split(str, ' ');
        command = results[0];
        key = results[1];
        if (command == "put") {
            val = results[2];
            add(key, val);
        }
        if (command == "delete") {
            remove(key);
        }
        if (command == "get") {
            fout << get(key) << "\n";
        }
        if (command == "next") {
            fout << next(key) << "\n";
        }
        if (command == "prev") {
            fout << prev(key) << "\n";
        }
    }

/*
    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    fout << "Time in ms: " << diff.count()<<std::endl;
*/
    fin.close();
    fout.close();
    return 0;
}
