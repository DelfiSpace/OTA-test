#include <stdio.h>
#include <stdlib.h>

#include "../OTA.h"
#include "../def.h"

void print_metadata(uint8_t* metadata) {
    printf("Metadata:\n");
    printf("\tSlot status: ");
    switch (metadata[0])
    {
        case EMPTY:
            printf("Emtpy\n");
            break;
        case PARTIAL:
            printf("Partial\n");
            break;
        case FULL:
            printf("Full\n");
            break;
        case TRANSMISSION:
            printf("Transmission\n");
            break;
        default:
            printf("Unknown slot status %d!\n", metadata[0]);
            break;
    }
    printf("\tVersion: %02x%02x%02x%02x\n", metadata[CRC_SIZE+1], metadata[CRC_SIZE+2], metadata[CRC_SIZE+3], metadata[CRC_SIZE+4]);
    printf("\tNumber of blocks: %d\n", metadata[CRC_SIZE+6] << 8 | metadata[CRC_SIZE+5]);
    printf("\tMD5 CRC: ");
    for(int i = 0; i < CRC_SIZE; i++) {
        printf("%02X", metadata[i + 1]);
    }
    printf("\n");
}


int main(int argc, char* argv[]) {
    uint8_t command[256] = {0};
    command[COMMAND_DESTINATION] = 18;
    command[COMMAND_SIZE] = 5;
    command[COMMAND_STATE] = COMMAND_REQUEST;
    command[COMMAND_METHOD] = RECEIVE_METADATA;
    command[COMMAND_PARAMETER] = 1;
    command[COMMAND_PARAMETER_SIZE] = 1;

    uint8_t* response = command_handler(command);
    if(response[COMMAND_STATE] != COMMAND_ERROR) {
        print_metadata(&response[COMMAND_PARAMETER]);
    } else {
        puts("Error occurred!");
        for(int i = 0; i < response[COMMAND_SIZE]; i++) printf("%02X ", response[i]);
        putchar('\n');
    }

    free(response);
    return 0;
}