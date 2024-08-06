#include "usart.h"
#include "json_parser.h"
#include "command.h"

int main() {
    init_usart();
    for(;;);
}

void handle_json(char *json) {
    Command command;
    flush_command(&command);
    parse_json(json, &command);
    print_parsed_command(&command);
}