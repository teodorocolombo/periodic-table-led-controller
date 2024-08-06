
#ifndef PERIODIC_TABLE_COMMAND_H
#define PERIODIC_TABLE_COMMAND_H

#include <stdbool.h>
#include <stdint.h>

#define MAX_ELEMENTS_ARRAY_SIZE 118
#define MAX_FAMILIES_ARRAY_SIZE 10
#define MAX_PERIODS_ARRAY_SIZE 7
#define MAX_GROUPS_ARRAY_SIZE 18
#define MAX_STRING_SIZE 50

typedef struct {
    char elements[MAX_ELEMENTS_ARRAY_SIZE][MAX_STRING_SIZE];
    char families[MAX_FAMILIES_ARRAY_SIZE][MAX_STRING_SIZE];
    uint8_t periods[MAX_PERIODS_ARRAY_SIZE];
    uint8_t groups[MAX_GROUPS_ARRAY_SIZE];
    uint8_t elements_count;
    uint8_t families_count;
    uint8_t periods_count;
    uint8_t groups_count;
    uint8_t reset;
} Command;

void flush_command(Command *cmd);

#endif //PERIODIC_TABLE_COMMAND_H
