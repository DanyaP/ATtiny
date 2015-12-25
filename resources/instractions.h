#pragma once
#ifndef ATTINY_INSTRACTIONS_H
#define ATTINY_INSTRACTIONS_H

#include "attiny.h"
#include <cstdint>
#include "instractions.h"
#include "doing_instractions.h"

void get_SREG(uint8_t * iter_data_memory);

void set_SREG(uint8_t * iter_data_memory);

bool nop(uint8_t * iter_program_memory, uint16_t &PC); // do nothig

bool adc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sum with carry

bool add(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sum

bool inc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // increment

bool sub(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers

bool sbc(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers with carry

bool subi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between register and const

bool sbci(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // sub between registers and const with carry

bool ldi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Load Immediate

bool mov(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Move Between Registers

bool sbi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Set Bit in I/O Register

bool cp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // compare

bool cpi(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Compare Register with Immediate

bool sec(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set carry flag

bool sen(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set negative flag

bool sez(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set zero flag

bool sei(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // global interrapt enable

bool ses(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set signed test fag

bool sev(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set two’s complement overflow

bool set(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set T in SREG

bool seh(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // set half carry flag

bool rjmp(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Relative Jump

//not done

bool rcall(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // call

bool ret(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // return

/*bool ser(uint8_t * iter_program_memory, uint8_t * iter_data_memory, uint16_t &PC); // Set all Bits in Register*/

#endif //ATTINY_INSTRACTIONS_H
