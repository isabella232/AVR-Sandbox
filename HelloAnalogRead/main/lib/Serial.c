/**
 * @file Serial.c
 * @author pavl_g.
 * @brief An implementation for the [Serial.h] header file.
 * @version 0.1
 * @date 2022-07-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include<Serial.h>

void Serial::UART::startProtocol() {
	UCSR0B = (1 << TXEN0) | (1 << RXEN0); // TXEN_BIT = 1, enables the transmitter buffer register.
    UCSR0C = (1 << USBS0) | (3 << UCSZ00); // enables the UCSZ0, UCSZ1 and URSEL
    UBRR0 = 0x10; // 0x10 (16) for BR = 57600 // 0x33 (51) for 9600
}

void Serial::UART::stopProtocol() {
    UCSR0B = 0x00; 
}

uint8_t Serial::UART::readASCII() {
    while (!(UCSR0A & (1 << RXC0)));
	return UDR0;
}
 
void Serial::UART::cprint(char& data) {
    while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

void Serial::UART::cprintln(char& data) {
    cprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}

void Serial::UART::sprint(char* data) {
    int i = 0;
    while (i < strlen(data)) {
        cprint(data[i++]);
    }
}

void Serial::UART::sprintln(char* data) {
    sprint(data);
    sprint(NEW_LINE_CARRIAGE_R);
}

void Serial::UART::print(const int64_t& data, const uint8_t& base) {
    char* strBuffer = allocateStringBuffer();
    // convert input to string
    itoa(data, strBuffer, base);
    int i = 0;
    while (i < strlen(strBuffer)) {
        cprint(strBuffer[i++]);
    }
    free(strBuffer);
}

void Serial::UART::println(const int64_t& data, const uint8_t& base) {
    print(data, base);
    sprint(NEW_LINE_CARRIAGE_R);
}
