#ifndef JSON_PARSER_H
#define JSON_PARSER_H

#include "command.h"
#include <stdint.h>

#define MAX_ARRAY_SIZE 10
#define MAX_STRING_SIZE 50

void parse_json(const char *json_string, Command *command);
void print_parsed_command(const Command *command);

#endif // JSON_PARSER_H