
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cbor.h>
#include <stdbool.h>
#include "receptor.h"
#include "command.h"

void cbor_decoder(const uint8_t *data, size_t size, ElementCommand *command)
{

    // Create the parsers
    struct cbor_load_result result;
    cbor_item_t *item = cbor_load(data, size, &result);

    // Check for errors
    if (result.error.code != CBOR_ERR_NONE)
    {
        fprintf(stderr, "CBOR decoding error: %d\n", result.error.code);
        return;
    }

    // Check if item is a map
    if (!cbor_isa_map(item))
    {
        fprintf(stderr, "CBOR data isnt a map.");
        cbor_decref(&item);
        return;
    }

    // Parse the data to a map format
    struct cbor_pair *map_data = cbor_map_handle(item);
    size_t map_size = cbor_map_size(item);

    // For debugging purposes
    printf("Map Size: %ld", map_size);

    for (size_t i = 0; i < map_size; i++)
    {

        char *key = (char *)cbor_string_handle(map_data[i].key);
        char *value = (char *)cbor_string_handle(map_data[i].value);

        // Check for every single key name to evaluate each field
        if (strcmp(key, "elements") == 0)
        {
            command->elements = strdup(value);
        }
        else if (strcmp(key, "families") == 0)
        {
            command->families = strdup(value);
        }
        else if (strcmp(key, "periods") == 0)
        {
            command->periods = strdup(value);
        }
        else if (strcmp(key, "groups") == 0)
        {
            command->groups = strdup(value);
        }
        else if (strcmp(key, "reset") == 0)
        {
            command->reset = cbor_get_bool(map_data[i].value);
        }
    }

    // Free the item
    cbor_decref(&item);
}

// For testing purposes
int main()
{
    // Create fake data
    cbor_item_t *map = cbor_new_definite_map(5);

    cbor_map_add(map, (struct cbor_pair){
                          .key = cbor_build_string("elements"),
                          .value = cbor_build_string("Elementos de teste")});

    cbor_map_add(map, (struct cbor_pair){
                          .key = cbor_build_string("families"),
                          .value = cbor_build_string("Famílias de teste")});

    cbor_map_add(map, (struct cbor_pair){
                          .key = cbor_build_string("periods"),
                          .value = cbor_build_string("Períodos de teste")});

    cbor_map_add(map, (struct cbor_pair){
                          .key = cbor_build_string("groups"),
                          .value = cbor_build_string("Grupos de teste")});

    cbor_map_add(map, (struct cbor_pair){
                          .key = cbor_build_string("reset"),
                          .value = cbor_build_bool(true)});

    unsigned char buffer[512];
    size_t buffer_size = cbor_serialize(map, buffer, sizeof(buffer));

    // Decodificar os dados CBOR
    ElementCommand command = {0};
    cbor_decoder(buffer, buffer_size, &command);

    // Exibir os valores decodificados
    printf("Elements: %s\n", command.elements);
    printf("Families: %s\n", command.families);
    printf("Periods: %s\n", command.periods);
    printf("Groups: %s\n", command.groups);
    printf("Reset: %s\n", command.reset ? "true" : "false");

    // Liberar a memória alocada
    free(command.elements);
    free(command.families);
    free(command.periods);
    free(command.groups);
    cbor_decref(&map);

    return 0;
}
