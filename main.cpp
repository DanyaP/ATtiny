#include <iostream>
#include "test.h"
#include "attiny.h"

using namespace std;

int main() {
    int a, b;
    long long sum;
    std::cin >> a >> b >> sum;
    say();
    testing(a, b, sum);
    return 0;
}