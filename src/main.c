#include "usart.h"
#include "json_parser.h"
#include "command.h"
#include "trigger.h"
#include <stdint.h>

int main() {
    init_usart();
}

void handle_json(char *json) {
    Command command;
    flush_command(&command);
    parse_json(json, &command);
    // print_parsed_command(&command);
    for (;;)
    {
        if (command.elements_count > 0)
        {
            for (int i = 0; i < command.elements_count; i++)
            {
                uint8_t element_value = get_element_value(command.elements[i]); // return -> 8 bits
            }
        }
    }
}