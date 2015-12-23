#ifndef ATTINY_INSTRACTIONS_H
#define ATTINY_INSTRACTIONS_H

#include "attiny.h"
#include <cstdint>

void SREG();

void get_SREG(uint8_t * iter_program_memory);

void set_SREG(uint8_t * iter_program_memory);

bool nop(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // do nothig

bool add(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sum

bool adc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sum with carry

bool sub(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers

bool sbc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers with carry

bool subi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between register and const

bool sbci(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers and const with carry


//not done
bool cp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // compare


bool sbi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Set Bit in I/O Register


bool rjmp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Relative Jump

bool ijmp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Indirect Jump to const

bool call(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // call



bool ldi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // move

bool sec(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set carry flag

bool sen(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set negative flag

bool sez(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set zero flag

bool sei(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // global interrapt enable

bool ses(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set signed test fag

bool sev(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set two’s complement overflow

bool set(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set T in SREG

bool seh(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set half carry flag

#endif //ATTINY_INSTRACTIONS_H
