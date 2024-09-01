#include "usart.h"
#include "json_parser.h"
#include "command.h"
#include "trigger.h"
#include <stdint.h>

int main() {
    init_usart();
}

static void MX_GPIO_Init(void) {
    GPIO_InitTypeDef GPIO_InitStruct = {0};

    // Habilita os clocks dos GPIOs A, B e C
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();

    // Configura os pinos PB9 ao PB3 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_9 | GPIO_PIN_8 | GPIO_PIN_7 | GPIO_PIN_6 | GPIO_PIN_5 | GPIO_PIN_4 | GPIO_PIN_3;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configura os pinos PA15, PA12 ao PA8 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_12 | GPIO_PIN_11 | GPIO_PIN_10 | GPIO_PIN_9 | GPIO_PIN_8;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configura os pinos PB15 ao PB12 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_15 | GPIO_PIN_14 | GPIO_PIN_13 | GPIO_PIN_12;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configura o pino PC15 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_15;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    // Configura os pinos PA0 ao PA7 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    // Configura os pinos PB0 e PB1 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

    // Configura os pinos PB10 e PB11 como saída
    GPIO_InitStruct.Pin = GPIO_PIN_10 | GPIO_PIN_11;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
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