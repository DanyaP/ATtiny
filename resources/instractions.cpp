#include "instractions.h"

bool I, T, H, S, V, N, Z, C;

void get_SREG(uint8_t * iter_program_memory) {
    uint8_t address_reg = 0x3F;
    uint8_t sreg = iter_program_memory[address_reg];
    I = sreg >> 7;
    T = ((sreg << 1) >> 7);
    H = ((sreg << 2) >> 7);
    S = ((sreg << 3) >> 7);
    V = ((sreg << 4) >> 7);
    N = ((sreg << 5) >> 7);
    Z = ((sreg << 6) >> 7);
    C = ((sreg << 7) >> 7);
}

void set_SREG(uint8_t * iter_program_memory) {
    uint8_t address_reg = 0x3F;
    uint8_t sreg = ((uint8_t) I << 7) | ((uint8_t) T << 6) |
                   ((uint8_t) H << 5) | ((uint8_t) S << 4) | ((uint8_t) V << 3) |
                   ((uint8_t) N << 2) | ((uint8_t) Z << 1) | (uint8_t) (C);
    iter_program_memory[address_reg] = sreg;
}

bool adc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC) {
    if ((iter_program_memory[PC] & 0xFCu) == 0x1Cu) {
        uint8_t r = ((iter_program_memory[PC + 1] & 0b10u) | (iter_program_memory[PC] & 0xFu));
        uint8_t d = ((iter_program_memory[PC + 1] & 0b1u) | (iter_program_memory[PC] >> 4));
        iter_data_memory[d] = r + d + C;
        get_SREG(iter_program_memory); // flags
        if (((d >> 7) & (r >> 7)) |
                ((r >> 7) & !(d >> 7)) |
                (!(d >> 7) & (d >> 7)))
            C = true;
        else C = false;
        if (!(d >> 7) & !((d & 64) >> 6) & !((d & 32) >> 5) & !((d & 16) >> 4) & !((d & 8) >> 3) &
            !((d & 4) >> 2) & !((d & 2) >> 1) & !(d & 1))
            Z = true;
        else Z = false;
        if ((d >> 7)) N = true;
        else N = false;
        if (((d >> 7) & (r >> 7) & !(d >> 7)) | (!(d >> 7) & (r >> 7) & (d >> 7))) V = true;
        else V = false;
        if ((N ^ V)) S = true;
        else S = false;
        if (((d >> 3) & (r >> 3)) |
            ((r >> 3) & !(d >> 3)) |
            (!(d >> 3) & (d >> 3)))
            H = true;
        else H = false;
        PC += 2;
        set_SREG(iter_program_memory);
    }
    return false;
}

bool add(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC) {
    if ((iter_program_memory[PC] & 0xFCu) == 0xCu) {
        uint8_t r = ((iter_program_memory[PC + 1] & 0b10u) | (iter_program_memory[PC] & 0xFu));
        uint8_t d = ((iter_program_memory[PC + 1] & 0b1u) | (iter_program_memory[PC] >> 4));
        iter_data_memory[d] = r + d;
        get_SREG(iter_program_memory); // flags
        if (((d >> 7) & (r >> 7)) |
            ((r >> 7) & !(d >> 7)) |
            (!(d >> 7) & (d >> 7)))
            C = true;
        else C = false;
        if (!(d >> 7) & !((d & 64) >> 6) & !((d & 32) >> 5) & !((d & 16) >> 4) & !((d & 8) >> 3) &
            !((d & 4) >> 2) & !((d & 2) >> 1) & !(d & 1))
            Z = true;
        else Z = false;
        if ((d >> 7)) N = true;
        else N = false;
        if (((d >> 7) & (r >> 7) & !(d >> 7)) | (!(d >> 7) & (r >> 7) & (d >> 7))) V = true;
        else V = false;
        if ((N ^ V)) S = true;
        else S = false;
        if (((d >> 3) & (r >> 3)) |
            ((r >> 3) & !(d >> 3)) |
            (!(d >> 3) & (d >> 3)))
            H = true;
        else H = false;
        PC += 2;
        set_SREG(iter_program_memory);
    }
    return false;
}

bool nop(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC) {
    if (iter_program_memory[PC] == 0x00 && iter_program_memory[PC + 1] == 0x00) {
        PC += 2;
        return true;
    }
    return false;
}