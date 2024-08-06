#include <string.h>
#include "stm32f1xx.h"
#include "usart.h"
#include "json_parser.h"
#include "main.h"

#define RX_BUFFER_SIZE 1000
#define TX_BUFFER_SIZE 1000
#define APB2_CLOCK 8000000
#define BAUD_RATE 115200

char rx_buffer[RX_BUFFER_SIZE], tx_buffer[TX_BUFFER_SIZE];
uint16_t rx_index = 0, tx_index = 0;

void send_string_usart(char *str);

void flush_buffer(char *array, size_t size);

void handle_incoming_message(char message);

void transmit_message();

void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        handle_incoming_message((char) USART1->DR);
    } else if (USART1->SR & USART_SR_TXE) {
        transmit_message();
    }
}

void handle_incoming_message(char message) {
    if (rx_index < RX_BUFFER_SIZE) {
        rx_buffer[rx_index++] = message;
    } else {
        flush_buffer(rx_buffer, RX_BUFFER_SIZE);
        rx_index = 0;
    }
    if (message == '}') {
        //send_string_usart(rx_buffer);
        handle_json(rx_buffer);
        flush_buffer(rx_buffer, RX_BUFFER_SIZE);
        rx_index = 0;
    }
}


void transmit_message(void) {
    if (tx_buffer[tx_index] && tx_index < RX_BUFFER_SIZE) { // Existe algum elemento a ser transmitido?
        USART1->DR = tx_buffer[tx_index++];
    } else {
        USART1->CR1 &= (uint32_t) (~USART_CR1_TXEIE); // Desab. interrupção por TXE
        tx_index = 0;
    }
}

void send_string_usart(char *str) {
    flush_buffer(tx_buffer, TX_BUFFER_SIZE);
    int i = 0;
    while (!(USART1->SR & USART_SR_TXE)) {
        // Aguarda buffer de Tx estar vazio
    }
    while (str[i] && i < RX_BUFFER_SIZE) {
        tx_buffer[i] = str[i];
        i++;
    }
    USART1->CR1 |= USART_CR1_TXEIE; // Hab. interrupção por TXE
}

void flush_buffer(char *array, size_t size) {
    memset(array, 0, size);
}

void init_usart(void) {
    // Habilita clock do barramento APB2
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN | RCC_APB2ENR_IOPCEN | RCC_APB2ENR_AFIOEN;
    GPIOC->CRH |= GPIO_CRH_MODE13_1;    // Configura pino PC13 como saida open-drain 2 MHz
    // PA9 como saída push-pull em função alt. (Tx da USART1)
    GPIOA->CRH = (GPIOA->CRH & 0xFFFFFF0F) | 0x000000B0; // 0b1011=0xB
    GPIOA->CRH |= (0x04 << 8); // PA10 como entrada flutuante (Rx da USART1)

    /* Config USART1 para Tx e Rx com IRQ */
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;   // Hab. clock para USART1
    USART1->BRR = APB2_CLOCK / BAUD_RATE;            // Define baudrate = 9600 baud/s (APB2_clock = 8 MHz)
    USART1->CR1 |= (USART_CR1_RE | USART_CR1_TE);   //  Hab. RX e TX
    USART1->CR1 |= USART_CR1_RXNEIE;        // Hab. interrupção por RXNE
    USART1->CR1 |= USART_CR1_UE;            // Hab USART1
    // NVIC->IP[USART1_IRQn] = ?;        // Config. prioridade da IRQ USART1
    NVIC->ISER[1] = (uint32_t) (1 << (USART1_IRQn - 32)); // Hab. IRQ da USART1 na NVIC

    send_string_usart("Started USART\n");
}
