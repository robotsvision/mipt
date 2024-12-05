#include <stdint.h>
#include <iostream>

int fib(int n) {
    return n < 2? n : fib(n - 1) + fib(n - 2);
}

int main(void) {
    int a = 10;
    std::cout << fib(a);
}