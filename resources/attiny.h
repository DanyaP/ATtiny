#pragma once
#ifndef ATTINY_H
#define ATTINY_H

#include <vector>
#include <cstdint>

int open_hex(const char *argv, uint8_t *iter_program_memory);

int doing_instraction(uint8_t *iter_program_memory, uint8_t * iter_data_memory);

#endif