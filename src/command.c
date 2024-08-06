#include "command.h"
#include <string.h>

void flush_command(Command *cmd) {
    // Reset all counters
    cmd->elements_count = 0;
    cmd->families_count = 0;
    cmd->periods_count = 0;
    cmd->groups_count = 0;
    cmd->reset = 0;

    // Clear elements array
    for (int i = 0; i < MAX_ELEMENTS_ARRAY_SIZE; i++) {
        memset(cmd->elements[i], 0, MAX_STRING_SIZE);
    }

    // Clear families array
    for (int i = 0; i < MAX_FAMILIES_ARRAY_SIZE; i++) {
        memset(cmd->families[i], 0, MAX_STRING_SIZE);
    }

    // Clear periods array
    for (int i = 0; i < MAX_PERIODS_ARRAY_SIZE; i++) {
        cmd->periods[i] = 0;
    }

    // Clear groups array
    for (int i = 0; i < MAX_GROUPS_ARRAY_SIZE; i++) {
        cmd->groups[i] = 0;
    }
}