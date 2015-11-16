#include <iostream>
#include <sys/fcntl.h>
#include <unistd.h>
#include "attiny.h"

void instraction(char * data) {
    // instractions of attiny will be here soon
}

bool parsing_file(int fdsc) {
    ssize_t num_of_bytes = -1;
    char some_str[1]; // start while from record mark
    while (1) {
        num_of_bytes = read(fdsc, some_str, 1);
        if (num_of_bytes < 0) return false;
        else if (num_of_bytes == 0) break;
        char str_reclen[3], str_load_offset[5], str_rectype[3];
        str_reclen[2] = '\0';
        str_load_offset[4] = '\0';
        str_rectype[2] = '\0';
        int reclen = 0, load_offset = 0, rectype = 0;
        read(fdsc, str_reclen, 2);
        reclen = strtol(str_reclen, 0, 16);
        read(fdsc, str_load_offset, 4);
        //std::cerr << strtol(str_load_offset, 0, 16) << '\n' << str_load_offset;
        read(fdsc, str_rectype, 2);
        rectype = strtol(str_rectype, 0, 16);
        //std::cerr << strtol(str_rectype, 0, 16);
        switch (rectype) {
            case 0: // data
                char data[5];
                data[4] = '\0';
                for (uint32_t i = 0; i < reclen / 2; ++i) {
                    read(fdsc, data, 4);
                    instraction(data);
                }
            case 1: //end of file
                break;
            case 2:
                char usba[4];
                read(fdsc, usba, 4);
                break;
            case 3:
                break;
            case 4:
                break;
            case 5:
                break;
            default:
                break;
        }
        char str_chksum[3];
        str_chksum[2] = '\0';
        read(fdsc, str_chksum, 2);
        int chksum = strtol(str_chksum, 0, 16);
        char end_of_instruction[3];
        end_of_instruction[2] = '\0';
        read(fdsc, end_of_instruction, 2); // cin '\r\n'
    }
    return true;
}


void open_hex(const char *argv) {
    int fdsc;
    fdsc = open(argv, O_RDONLY);
    if (fdsc == -1) {
        std::cout << "Nonexistent or not available file\n";
    } else if (!parsing_file(fdsc)) {
        std::cout << "Some problem with hex file\n";
    } else {
        std::cout << "All correct\n";
    }
    close(fdsc);
}