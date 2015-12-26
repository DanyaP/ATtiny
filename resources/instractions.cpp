#include "instractions.h"
#include <cstdint>
#include <iostream>
#include <bitset>

bool I, T, H, S, V, N, Z, C;
uint8_t address_reg = 0x3Fu;
//uint8_t SPL = 0x3Du;
void get_SREG(uint8_t * iter_data_memory) {
    uint8_t sreg = *(iter_data_memory + address_reg);
    I = sreg >> 7;
    T = ((sreg << 1) >> 7);
    H = ((sreg << 2) >> 7);
    S = ((sreg << 3) >> 7);
    V = ((sreg << 4) >> 7);
    N = ((sreg << 5) >> 7);
    Z = ((sreg << 6) >> 7);
    C = ((sreg << 7) >> 7);
}

void set_SREG(uint8_t * iter_data_memory) {
    uint8_t sreg = ((uint8_t) I << 7) | ((uint8_t) T << 6) |
                   ((uint8_t) H << 5) | ((uint8_t) S << 4) | ((uint8_t) V << 3) |
                   ((uint8_t) N << 2) | ((uint8_t) Z << 1) | (uint8_t) (C);
    *(iter_data_memory + address_reg) = sreg;
}

bool adc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0x1Cu) {
        get_SREG(iter_data_memory); // flags
        uint8_t r = ((((*(iter_program_memory + PC) >> 1) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = (((*(iter_program_memory + PC) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) >> 4 & 0xFu));
        uint8_t res = (*(iter_data_memory + d) + *(iter_data_memory + r) + (uint8_t) C);
        H = ((((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((*(iter_data_memory + r) & (1 << 3)) >> 3)) |
            (((*(iter_data_memory + d) & (1 << 3)) >> 3) & !((res & (1 << 3)) >> 3)) |
            (((*(iter_data_memory + r) & (1 << 3)) >> 3) & !((res & (1 << 3)) >> 3)));
        S = (N ^ V);
        V = (((*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7) & !(res >> 7)) |
                (!(*(iter_data_memory + d) >> 7) & !(*(iter_data_memory + r) >> 7) & (res >> 7)));
        N = (res >> 7);
        Z = (res == 0);
        C = ((*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7)) |
                ((*(iter_data_memory + d) >> 7) & !(res >> 7)) |
                ((*(iter_data_memory + r) >> 7) & !(res >> 7));
        *(iter_data_memory + d) = res;
        PC += 2;
        PC %= 0x200u;
        set_SREG(iter_data_memory);
        return true;
    }
    return false;
}

bool add(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0xCu) {
        get_SREG(iter_data_memory); // flags
        uint8_t r = ((((*(iter_program_memory + PC) >> 1) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = (((*(iter_program_memory + PC) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) >> 4 & 0xFu));
        uint8_t res = *(iter_data_memory + d) + *(iter_data_memory + r);
        H = ((((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((*(iter_data_memory + r) & (1 << 3)) >> 3)) |
             (((*(iter_data_memory + d) & (1 << 3)) >> 3) & !((res & (1 << 3)) >> 3)) |
             (((*(iter_data_memory + r) & (1 << 3)) >> 3) & !((res & (1 << 3)) >> 3)));
        S = (N ^ V);
        V = (((*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7) & !(res >> 7)) |
             (!(*(iter_data_memory + d) >> 7) & !(*(iter_data_memory + r) >> 7) & (res >> 7)));
        N = (res >> 7);
        Z = (res == 0);
        C = ((*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7)) |
            ((*(iter_data_memory + d) >> 7) & !(res >> 7)) |
            ((*(iter_data_memory + r) >> 7) & !(res >> 7));
        *(iter_data_memory + d) = res;
        PC += 2;
        PC %= 0x200u;
        set_SREG(iter_data_memory);
        return true;
    }
    return false;
}

bool inc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (((*(iter_program_memory + PC) & 0xFEu) == 0x94u) && ((*(iter_program_memory + PC) & 0xFu) == 0x3u)) {
        get_SREG(iter_data_memory);
        uint8_t d = (((*(iter_data_memory + PC) & 0x1u) << 4) + ((*(iter_data_memory + PC) >> 4) & 0xFu));
        *(iter_data_memory + d) += 1;
        S = (N ^ V);
        if (*(iter_data_memory + d) == 0x80) V = true;
        else V = false;
        if (((*(iter_data_memory + d) >> 7) & 0x1u)) N = true;
        else N = false;
        if (*(iter_data_memory + d) == 0) Z = true;
        else Z = false;
        PC += 2;
        PC %= 0x200u;
        set_SREG(iter_data_memory);
        return true;
    }
    return false;
}

bool sub(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0x18u) {
        get_SREG(iter_data_memory);
        uint8_t r = ((*(iter_program_memory + PC) >> 4 & 0b1u) << 4 | (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = ((*(iter_program_memory + PC) & 0b1u) << 4 | (*(iter_program_memory + PC + 1) >> 4));
        *(iter_data_memory + d) = *(iter_data_memory + d) - *(iter_data_memory + r);
        // change flags
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sbc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0x8u) {
        get_SREG(iter_data_memory);
        uint8_t r = ((*(iter_program_memory + PC) >> 4 & 0b1u) << 4 | (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = ((*(iter_program_memory + PC) & 0b1u) << 4 | (*(iter_program_memory + PC + 1) >> 4));
        *(iter_data_memory + d) = *(iter_data_memory + d) - *(iter_data_memory + r) - C;
        // change flags
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool subi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xF0u) == 0x50u) {
        get_SREG(iter_data_memory);
        uint8_t d = ((*(iter_program_memory + PC + 1) >> 4));
        uint8_t K = (((*(iter_program_memory + PC) & 0xFu) << 4) | (*(iter_program_memory + PC + 1) & 0xFu));
        *(iter_data_memory + d) = *(iter_data_memory + d) - K;
        // change flags
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sbci(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xF0u) == 0x40u) {
        get_SREG(iter_data_memory);
        uint8_t d = ((*(iter_program_memory + PC + 1) >> 4));
        uint8_t K = (((*(iter_program_memory + PC) & 0xFu) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        *(iter_data_memory + d) = *(iter_data_memory + d) - K - C;
        // change flags
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sbi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFFu) == 0x9Au) {
        uint8_t A = 0x20u + (((*(iter_program_memory + PC + 1) >> 4) << 1) + ((*(iter_program_memory + PC + 1) >> 3) & 0x1u));
        uint8_t b = (*(iter_program_memory + PC + 1) & 0x7u);
        *(iter_data_memory + A) = (*(iter_data_memory + A) | (1 << b));
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool rjmp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (((*(iter_program_memory + PC) >> 4) & 0xFu) == 0xCu) {
        int16_t k = ((int16_t)(*(iter_program_memory + PC) & 0xF) << 8) +
                (int16_t)(*(iter_program_memory + PC + 1) & 0xFF);
        k += 1;
        PC += (2 * k);
        PC %= 0x200u;
        return true;
    }
    return false;
}
// need fix problem with stack
/*bool rcall(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0xD0u) {
        int16_t k = ((((int16_t)(*(iter_program_memory + PC) & 0xF)) << 8) +
                (int16_t)(*(iter_program_memory + PC + 1) & 0xFF)) + 1;
        PC += (2 * k);
    }
}

bool ret(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) { }*/

bool mov(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFEu) == 0x2Cu) {
        uint8_t r = ((((*(iter_program_memory + PC) >> 1) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = (((*(iter_program_memory + PC) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) >> 4 & 0xFu));
        *(iter_data_memory + d) = *(iter_data_memory + r);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool cp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xFCu) == 0x14u) {
        get_SREG(iter_data_memory);
        uint8_t r = ((((*(iter_program_memory + PC) >> 1) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t d = (((*(iter_program_memory + PC) & 0b1u) << 4) + (*(iter_program_memory + PC + 1) >> 4 & 0xFu));
        uint8_t res = *(iter_data_memory + d) - *(iter_data_memory + r);

        H = ((!((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((*(iter_data_memory + r) & (1 << 3)) >> 3)) |
             (!((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((res & (1 << 3)) >> 3)) |
             (((*(iter_data_memory + r) & (1 << 3)) >> 3) & ((res & (1 << 3)) >> 3)));
        S = (N ^ V);
        V = (((*(iter_data_memory + d) >> 7) & !(*(iter_data_memory + r) >> 7) & !(res >> 7)) |
             (!(*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7) & (res >> 7)));
        N = (res >> 7);
        Z = (res == 0);
        C = (!(*(iter_data_memory + d) >> 7) & (*(iter_data_memory + r) >> 7)) |
            (!(*(iter_data_memory + d) >> 7) & (res >> 7)) |
            ((*(iter_data_memory + r) >> 7) & (res >> 7));
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool cpi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xF0u) == 0xC0u) {
        get_SREG(iter_data_memory);
        uint8_t d = ((*(iter_program_memory + PC + 1) >> 4) & 0xFu);
        uint8_t K = (((*(iter_program_memory + PC) & 0xFu) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        uint8_t res = *(iter_data_memory + d) - K;
        H = ((!((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((K & (1 << 3)) >> 3)) |
             (!((*(iter_data_memory + d) & (1 << 3)) >> 3) & ((res & (1 << 3)) >> 3)) |
             (((K & (1 << 3)) >> 3) & ((res & (1 << 3)) >> 3)));
        S = (N ^ V);
        V = (((*(iter_data_memory + d) >> 7) & !(K >> 7) & !(res >> 7)) |
             (!(*(iter_data_memory + d) >> 7) & (K >> 7) & (res >> 7)));
        N = (res >> 7);
        Z = (res == 0);
        C = (!(*(iter_data_memory + d) >> 7) & (K >> 7)) |
            (!(*(iter_data_memory + d) >> 7) & (res >> 7)) |
            ((K >> 7) & (res >> 7));
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool ldi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if ((*(iter_program_memory + PC) & 0xF0u) == 0xE0u) {
        uint8_t d = 16 + ((*(iter_program_memory + PC + 1) >> 4));
        uint8_t K = (((*(iter_program_memory + PC) & 0xFu) << 4) + (*(iter_program_memory + PC + 1) & 0xFu));
        *(iter_data_memory + d) = K;
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

/*bool ser(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0xEFu && *(iter_program_memory + PC + 1) == 0xEu) {
        uint8_t d = (*(iter_program_memory + PC + 1) & 0xF0);
        *(iter_data_memory + d) = 0xFF;
        PC += 2;
        return true;
    }
    return false;
}*/

bool sec(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x8u) {
        get_SREG(iter_data_memory);
        C = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sez(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x18u) {
        get_SREG(iter_data_memory);
        Z = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sen(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x28u) {
        get_SREG(iter_data_memory);
        N = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sev(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x38u) {
        get_SREG(iter_data_memory);
        V = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool ses(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x48u) {
        get_SREG(iter_data_memory);
        S = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool seh(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x58u) {
        get_SREG(iter_data_memory);
        H = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool set(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x68u) {
        get_SREG(iter_data_memory);
        T = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool sei(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC) {
    if (*(iter_program_memory + PC) == 0x94u && *(iter_program_memory + PC + 1) == 0x78u) {
        get_SREG(iter_data_memory);
        I = 1;
        set_SREG(iter_data_memory);
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}

bool nop(uint8_t * iter_program_memory, uint16_t &PC) {
    if (iter_program_memory[PC] == 0 && iter_program_memory[PC + 1] == 0) {
        PC += 2;
        PC %= 0x200u;
        return true;
    }
    return false;
}