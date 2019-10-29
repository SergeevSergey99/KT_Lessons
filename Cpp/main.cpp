#include <iostream>

double f(double (*fn)(double), double a, double b, int steps) {
    double sum = 0;
    double len = (b - a) / steps;
    for (int i = 0; i < steps; ++i) {
        sum += len * fn(i * len + len / 2);
    }
    return sum;
}

int main() {
    std::cout << f( [](double x) { return x; }, 0, 4, 10);
    return 42;
}
