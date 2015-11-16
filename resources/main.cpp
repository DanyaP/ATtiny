#include <iostream>
#include "test.h"
#include "attiny.h"

int main(const int argc, const char *argv[]) {
    open_hex(argv[1]);
    return 0;
}