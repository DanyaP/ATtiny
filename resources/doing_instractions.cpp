//
// Created by Daniil Petrochenko on 23/12/15.
//

#include <iostream>
#include "doing_instractions.h"
#include "instractions.h"
#include <unistd.h>

int doing_instraction(uint8_t *iter_program_memory, uint8_t * iter_data_memory) {
    uint16_t PC = 0;
    sleep(2);
    // I, T, H, S, V, N, Z, C;
    while (1) {
        if (PC == 0x01FF)
            PC = 0;
        if (adc(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing adc\n";
        } else if (add(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing add\n";
        } else if (sub(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sub\n";
        } else if (sbc(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sbc\n";
        } else if (subi(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing subi\n";
        } else if (sbci(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sbci\n";
        } else if (nop(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing nothing\n";
        } else if (rjmp(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing rjmp\n";
        } else if (ijmp(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing ijmp\n";
        } else if (call(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing call\n";
        } else if (cp(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing cp\n";
        } else if (ldi(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing ldi\n";
        } else if (sei(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sei\n";
        } else if (set(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing set\n";
        } else if (seh(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing seh\n";
        } else if (ses(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing ses\n";
        } else if (sev(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sev\n";
        } else if (sen(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sen\n";
        } else if (sez(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sez\n";
        } else if (sec(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sec\n";
        } else if (sbi(iter_program_memory, iter_data_memory, PC)) {
            std::cerr << "doing sbi\n";
        } else {
            std::cerr << "some undeclared instraction\nEmulation interrupted\n";
            return 1;
            //PC += 2;
        }
        sleep(2);
    }
}