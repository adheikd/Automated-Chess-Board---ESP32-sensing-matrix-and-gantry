/*
    This library file declares functions that control operations over UART to the main processor, including:
        - Sending when a move has been made, and describing the move
        - Sending the state of the board

    A GPIO will be set to low/high to indicate when a move is expected to occur
*/
#include <Arduino.h>

/*
    Prints the board state to serial
*/
void print_board_state(HardwareSerial serialport);