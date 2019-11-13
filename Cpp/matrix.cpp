//#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

const int N = 200, M = 200, P = 200;

int matrix1[N][M];
int matrix2[M][P];
int matrix3[N][P] = {};

void func(int i) {
    for (int j = 0; j < P; ++j) {
        for (int k = 0; k < M; ++k) {
            matrix3[i][j] += matrix1[i][k] * matrix2[k][j];
        }
    }
}

int main() {


    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < M; ++j) {
            matrix1[i][j] = 1;
        }
    }
    for (int i = 0; i < M; ++i) {
        for (int j = 0; j < P; ++j) {
            matrix2[i][j] = 1;
        }
    }


    int thread_coount = 1;

    vector<thread> threads;

    auto start = chrono::system_clock::now();

    for (int i = 0; i < N; ++i)
    {
        if (threads.size() < thread_coount)
            threads.emplace_back(thread(func, i));
        else
        {

            for (int ii = 0; ii < thread_coount; ++ii)
            {
                threads.back().join();
                threads.pop_back();
            }
        }
    }
    while (threads.size() > 0)
    {
        threads.back().join();
        threads.pop_back();
    }
    auto end = chrono::system_clock::now();
    chrono::duration<double, milli> diff = end - start;
    cout << "Time in ms: " << diff.count() << endl;

    return 42;
}