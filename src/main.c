
#include <stdio.h>
#include <stdlib.h>
#include "command.h"
#include <cbor.h>

int main() {
    // Example CBOR hex data representing the string "Hello"
    uint8_t cbor_data[] = {0x65, 0x48, 0x65, 0x6c, 0x6c, 0x6f};
    size_t cbor_data_len = sizeof(cbor_data) / sizeof(cbor_data[0]);

    cborDecoder(cbor_data, cbor_data_len);

    return 0;
}
