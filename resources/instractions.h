#ifndef ATTINY_INSTRACTIONS_H
#define ATTINY_INSTRACTIONS_H

#include "attiny.h"

void SREG();

bool add(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // sum

bool adc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // sum with carry

bool sub(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // sub

bool jmp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // jump

bool call(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC);

bool cp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // compare

bool ldi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC);

bool nop(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // do nothig

bool sec(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set carry flag

bool sen(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set negative flag

bool sez(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set zero flag

bool sei(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // global interrapt enable

bool ses(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set signed test fag

bool sev(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set two’s complement overflow

bool set(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set T in SREG

bool seh(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t PC); // set half carry flag

#endif //ATTINY_INSTRACTIONS_H
