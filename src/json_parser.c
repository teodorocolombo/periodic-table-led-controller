#include "json_parser.h"

#include <stdio.h>
#include <cJSON.h>
#include "usart.h"

void parse_json(const char *json_string, Command *command) {
    // Parse the JSON string
    cJSON *json = cJSON_Parse(json_string);
    if (json == NULL) {
        send_string_usart("Error parsing JSON\n");
        return;
    }

    // Initialize counts
    command->elements_count = 0;
    command->families_count = 0;
    command->periods_count = 0;
    command->groups_count = 0;

    // Extract elements
    cJSON *elements = cJSON_GetObjectItemCaseSensitive(json, "elements");
    if (cJSON_IsArray(elements)) {
        command->elements_count = cJSON_GetArraySize(elements);
        for (int i = 0; i < command->elements_count; i++) {
            cJSON *element = cJSON_GetArrayItem(elements, i);
            if (cJSON_IsString(element)) {
                snprintf(command->elements[i], MAX_STRING_SIZE, "%s", element->valuestring);
            }
        }
    }

    // Extract families
    cJSON *families = cJSON_GetObjectItemCaseSensitive(json, "families");
    if (cJSON_IsArray(families)) {
        command->families_count = cJSON_GetArraySize(families);
        for (int i = 0; i < command->families_count; i++) {
            cJSON *family = cJSON_GetArrayItem(families, i);
            if (cJSON_IsString(family)) {
                snprintf(command->families[i], MAX_STRING_SIZE, "%s", family->valuestring);
            }
        }
    }

    // Extract periods
    cJSON *periods = cJSON_GetObjectItemCaseSensitive(json, "periods");
    if (cJSON_IsArray(periods)) {
        command->periods_count = cJSON_GetArraySize(periods);
        for (int i = 0; i < command->periods_count; i++) {
            cJSON *period = cJSON_GetArrayItem(periods, i);
            if (cJSON_IsNumber(period)) {
                command->periods[i] = period->valueint;
            }
        }
    }

    // Extract groups
    cJSON *groups = cJSON_GetObjectItemCaseSensitive(json, "groups");
    if (cJSON_IsArray(groups)) {
        command->groups_count = cJSON_GetArraySize(groups);
        for (int i = 0; i < command->groups_count; i++) {
            cJSON *group = cJSON_GetArrayItem(groups, i);
            if (cJSON_IsNumber(group)) {
                command->groups[i] = group->valueint;
            }
        }
    }

    // Extract reset
    cJSON *reset = cJSON_GetObjectItemCaseSensitive(json, "reset");
    if (cJSON_IsBool(reset)) {
        command->reset = cJSON_IsTrue(reset);
    }

    // Clean up
    cJSON_Delete(json);
}

void print_parsed_command(const Command *command) {
    char buffer[1000];  // Make sure this is large enough for your command
    int offset = 0;
    int remaining = sizeof(buffer);

    // Elements
    offset += snprintf(buffer + offset, remaining, "\nElements: ");
    remaining = sizeof(buffer) - offset;
    for (int i = 0; i < command->elements_count; i++) {
        offset += snprintf(buffer + offset, remaining, "%s ", command->elements[i]);
        remaining = sizeof(buffer) - offset;
    }

    // Families
    offset += snprintf(buffer + offset, remaining, "\nFamilies: ");
    remaining = sizeof(buffer) - offset;
    for (int i = 0; i < command->families_count; i++) {
        offset += snprintf(buffer + offset, remaining, "%s ", command->families[i]);
        remaining = sizeof(buffer) - offset;
    }

    // Periods
    offset += snprintf(buffer + offset, remaining, "\nPeriods: ");
    remaining = sizeof(buffer) - offset;
    for (int i = 0; i < command->periods_count; i++) {
        offset += snprintf(buffer + offset, remaining, "%d ", command->periods[i]);
        remaining = sizeof(buffer) - offset;
    }

    // Groups
    offset += snprintf(buffer + offset, remaining, "\nGroups: ");
    remaining = sizeof(buffer) - offset;
    for (int i = 0; i < command->groups_count; i++) {
        offset += snprintf(buffer + offset, remaining, "%d ", command->groups[i]);
        remaining = sizeof(buffer) - offset;
    }

    // Reset
    snprintf(buffer + offset, remaining, "\nReset: %s\n", command->reset ? "true" : "false");

    // Send the entire buffer at once
    send_string_usart(buffer);
}