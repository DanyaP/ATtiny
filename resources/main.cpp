#include "attiny.h"
#include <vector>
#include <cstdint>
#include <sys/signal.h>
#include <iostream>

void func(int s) {
    std::cerr << "User's interruption\n";
    exit(0);
}

int main(const int argc, const char *argv[]) {
    signal(SIGINT, func);
    std::vector<uint16_t> program_memory(0x01FF);
    std::vector<uint8_t> data_memory(0x009F);
    uint8_t * iter_program_memory = (uint8_t *)program_memory.data();
    uint8_t * iter_data_memory = data_memory.data();
    if (!open_hex(argv[1], iter_program_memory)) {
        doing_instraction(iter_program_memory, iter_data_memory);
    }

    return 0;
}