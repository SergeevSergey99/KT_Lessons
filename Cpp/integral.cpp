#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <functional>


template <typename TFunc>
void f(TFunc fn, double a, double b, int steps, double& result) {
    double sum = 0;
    double len = (b - a) / steps;
    for (int i = 0; i < steps; ++i) {
        sum += len * (fn(i * len) + fn(i * len + len)) / 2;
    }
    result += sum;
}

int main() {

    auto start = std::chrono::system_clock::now();


    double result = 0;
    std::function<double(double)> function{[](double x) { return x * x; }};


    std::vector<std::thread> threads;
    int thread_coount = 4;
    for (int i = 0; i < thread_coount; ++i) {
        threads.emplace_back(std::thread(f<std::function<double(double)>>, function, i*4, (i+1)*4, 100, std::ref(result)));
    }

    for (int i = 0; i < thread_coount; ++i) {
        if(threads.back().joinable()) threads.back().join();
        threads.pop_back();
    }

    auto end = std::chrono::system_clock::now();
    std::chrono::duration<double, std::milli> diff = end - start;
    std::cout << "Time in ms: " << diff.count()<<std::endl;
    std::cout << "Result is: " << result<<std::endl;
    return 42;
}
