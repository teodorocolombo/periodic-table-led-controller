
#ifndef PERIODIC_TABLE_COMMAND_H
#define PERIODIC_TABLE_COMMAND_H

typedef struct {
    char *elements; // 118 in total
    char *families; // 10 in total
    char *periods; // 7 in total
    char *groups; // 18 in total
    bool reset; // reset all leds
} ElementCommand;



#endif //PERIODIC_TABLE_COMMAND_H
