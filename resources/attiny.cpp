#include <iostream>
#include <sys/fcntl.h>
#include <unistd.h>
#include "attiny.h"
#include "instractions.h"
#include <vector>
#include <stdio.h>
#include <fstream>
#include <cstdint>

bool parsing_file(int fdsc, uint8_t *iter_program_memory) {
    ssize_t num_of_bytes = -1;
    char start_code;
    char str_byte_count[3], str_record_type[3], str_check_sum[3], str_address[5];
    str_byte_count[2] = '\0'; str_record_type[2] = '\0'; str_check_sum[2] = '\0';
    str_address[4] = '\0';
    uint8_t byte_count, record_type, check_sum;
    uint16_t address, PC;

    while (1) {
        num_of_bytes = read(fdsc, &start_code, sizeof(start_code));
        if (num_of_bytes < 0) return false;
        else if (num_of_bytes == 0) break;
        num_of_bytes = read(fdsc, str_byte_count, sizeof(str_byte_count) - 1);
        num_of_bytes = read(fdsc, str_address, sizeof(str_address) - 1);
        num_of_bytes = read(fdsc, str_record_type, sizeof(str_record_type) - 1);
        byte_count = strtoul(str_byte_count, 0, 16);
        address = strtoul(str_address, 0, 16);
        record_type = strtoul(str_record_type, 0, 16);
        switch (record_type)
        {
            case 0: // data
                char str_data[3];
                str_data[2] = '\0';
                uint8_t data;
                PC = address;
                for (int i = 0; i < byte_count; ++i) {
                    read(fdsc, str_data, sizeof(str_data) - 1);
                    data = strtoul(str_data, 0, 16);
                    if (i % 2 == 0) *(iter_program_memory + PC + 1) = data; // little endian
                    else *(iter_program_memory + PC - 1) = data;
                    ++PC;
                }
            case 1: //end of file
                break;
            case 2:
                char usba[4];
                read(fdsc, &usba, sizeof(usba));
                break;
            case 3:
                break;
            case 4:
                char upper[4];
                read(fdsc, upper, sizeof(upper));
                break;
            case 5:
                break;
            default:
                break;
        }
        read(fdsc, str_check_sum, sizeof(str_check_sum) - 1);
        check_sum = strtoul(str_check_sum, 0, 16);
        char end[2];
        read(fdsc, end, sizeof(end));
    }
    return true;
}


int open_hex(const char *argv, uint8_t *iter_program_memory) {
    int fdsc = open(argv, O_RDONLY);
    if (fdsc == -1) {
        close(fdsc);
        std::cerr << "Nonexistent or not available file\nPlease, enter available file\n";
        return -1;
    } else if (!parsing_file(fdsc, iter_program_memory)) {
        close(fdsc);
        std::cerr << "Some problem with hex file\nPlease, enter correct hex file\n";
        return 1;
    } else {
        close(fdsc);
        std::cerr << "All correct\nEmulation started\n";
        return 0;
    }
}