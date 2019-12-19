//
// Created by Sergey on 03.12.2019.
//
#include <fstream>
#include <vector>
#include <sstream>
//#include <chrono>

#define LEN 4096
#define LEN_VALS 128
using namespace std;

int k_for_hash[20] = {7, 0, 1, 3, 5,
                      4, 0, 1, 1, 51,
                      1, 0, 5, 97, 13,
                      3, 37, 2, 61, 29
};
int _hash(string str) {
    int n = str.length() % 7;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += ((unsigned int) str[i]) << k_for_hash[i];
    }
    return  (sum) % (LEN);
}

int __hash(string str) {
    int n = str.length() % 7;
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        sum += ((unsigned int) str[i]) << k_for_hash[i];
    }
    return  (sum) % (LEN_VALS);
}

struct node_vals // структура для представления элементов хеш таблицы
{
public:

    string value;

    node_vals *next;

    explicit node_vals(string v) {
        value = v;
        next = nullptr;
    }
};
struct node // структура для представления элементов хеш таблицы
{
public:
    string key;
    node_vals *value[LEN_VALS] = {};

    int n;
    node *next;

    explicit node(string k, string v) {
        n = 1;
        key = k;
        value[__hash(v)] = new node_vals(v);
        next = nullptr;
    }
};

struct LinkedMap {
    node *table[LEN] = {};
};

LinkedMap linkedMap;

void add(string key, string val) {
    int i = _hash(key);
    node *now = linkedMap.table[i];

    if (now == nullptr) {
        linkedMap.table[i] = new node(key, val);
        return;
    }
    while ((now->next != nullptr) and (now->key != key)) {
        now = now->next;
    }
    if (now->key == key) {

/*        for (int j = 0; j < now->value.size(); ++j) {
            if(now->value[j] == val)
                return;
        }
        now->value.push_back( val);*/

        // таблица значение с данным кейем
        // Хешь значения которое хотим добавить
        int i_val = __hash(val);
        node_vals *val_now = now->value[i_val];
        // Если есть заканчиваем
        if(val_now == nullptr)
        {
            // Если нет добавляем
            now->value[i_val] = new node_vals(val);
            now->n++;
            return;
        }
        while(val_now->value != val)
        {
            if(val_now->next == nullptr)
            {
                // Если нет добавляем
                val_now->next = new node_vals(val);
                now->n++;
                return;
            }
            val_now = val_now->next;
        }
        return;
    }

    now->next = new node(key, val);
}
void removeAll(string key) {
    int i = _hash(key);

    node *now = linkedMap.table[i];
    node *prev = nullptr;
    if (now == nullptr)
        return;
    if (linkedMap.table[i]->key == key)
    {
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

    if (prev != nullptr)
        prev->next = now->next;
    delete (now);

}
std::vector<std::string> split(const std::string &s, char delim) {
    std::stringstream ss(s);
    std::string item;
    std::vector<std::string> elems;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}
void remove(string key, string val) {
    int i = _hash(key);

    node *now = linkedMap.table[i];
    node *prev = nullptr;
    if (now == nullptr)
        return;
    if (linkedMap.table[i]->key == key)
    {



        /*
        if(linkedMap.table[i]->value[0] == val && linkedMap.table[i]->value.size() == 1) {
            node *nxt = linkedMap.table[i]->next;
            delete (linkedMap.table[i]);
            linkedMap.table[i] = nxt;
            return;
        }
        for (int j = 0; j < linkedMap.table[i]->value.size(); ++j) {
            if(linkedMap.table[i]->value[j] == val)
            {
                linkedMap.table[i]->value.erase(linkedMap.table[i]->value.begin()+j);
            }
        }
*/

        node_vals *val_now = now->value[__hash(val)];
        node_vals *val_prev = nullptr;
        // Если есть удаляем
        if(val_now == nullptr)
            return;

        while(val_now->value != val)
        {
            val_prev = val_now;
            if(val_now->next == nullptr)
            {
                // Если нет заканчиваем
                return;
            }
            val_now = val_now->next;
        }

        if(val_prev == nullptr)
            now->value[__hash(val)] = val_now->next;
        else
            val_prev->next = val_now->next;
        now->n--;
        val_now->next = nullptr;
        delete(val_now);

   /*     if(val_prev == nullptr)
            now->value[__hash(val)] = nullptr;
*/
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

    /*if (prev != nullptr)
        prev->next = now->next;
*/
    /*
    node *nxt = now->next;
    if(now->value[0] == val && now->value.size() == 1) {
        delete (now);
        if (prev != nullptr)
            prev->next = nxt;

        return;
//        linkedMap.table[i] = nxt;
    }
    for (int j = 0; j < now->value.size(); ++j) {
        if(now->value[j] == val)
        {
            now->value.erase(now->value.begin()+j);
        }
    }
*/
    node_vals *val_now = now->value[__hash(val)];
    node_vals *val_prev = nullptr;
    // Если есть удаляем
    while(val_now->value != val)
    {
        val_prev = val_now;
        if(val_now->next == nullptr)
        {
            // Если нет заканчиваем
            return;
        }
        val_now = val_now->next;
    }

    val_prev->next = val_now->next;

    now->n--;
    val_now->next = nullptr;
    delete(val_now);

    if(val_prev == nullptr)
        now->value[__hash(val)] = nullptr;

    return;


}
string get(string key) {
    int i = _hash(key);
    node *now = linkedMap.table[i];

    if (now == nullptr)
        return "0";
    while ((now->next != nullptr) and (now->key != key)) {
        now = now->next;
    }
    if (now->key == key) {
        string string1 = to_string(now->n);
        for (int j = 0; j < LEN_VALS; ++j) {
//            if(now->value[j] != nullptr)
            {
  //              string1 += " " + now->value[j]->value;
                 node_vals *val_now = now->value[j];

                while (val_now != nullptr)
                {
                    string1 += " " + val_now->value;

                    val_now = val_now->next;
                }
            }
        }
        return string1;
    }
    return "0";
}
int main() {


    //  auto start = std::chrono::system_clock::now();

    ios_base::sync_with_stdio(false);
    ifstream fin;
    ofstream fout;
    fin.open("multimap.in");
    fout.open("multimap.out");



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
        if (command == "deleteall") {
            removeAll(key);
        }
        if (command == "delete") {
            val = results[2];
            remove(key, val);
        }
        if (command == "get") {
            fout << get(key) << "\n";
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
