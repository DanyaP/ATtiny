#include <iostream>

void testing(int a, int b, long long sum) {
    std::cout << a << " + " << b << " = " << sum << " is ";
    if (a + b == sum) std::cout << "true!";
    else std::cout << "false!";
}