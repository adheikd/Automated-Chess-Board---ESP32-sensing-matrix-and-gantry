/*
    This library file declares functions that control operations over UART to the main processor, including:
        - Sending when a move has been made, and describing the move

    A GPIO (COM) will be set to low/high by the main processor to indicate when a move is expected to occur, 
    and players press the ENDMOVE button, whose line goes to GND, when they have finished their move
*/
#include <Arduino.h>
#include <chessboard.h>

// Communications pin - main processor sets this value low when it wants a move to be made
#define COM 22
#define ENDMOVE 23

//Initializes pins, etc that need initialization for inter-board communication
void init_interface();

//Prints the board state to the debugging serial port
void print_board_state_debug();

//Prints the board state to the MCU interface serial port
void print_board_state_interface();

//Prints out each move in the list 
void print_move_list();

/*
    Sends what move was found out to the main board, in the format:
        <moveType> <start col letter (lowercase)><start row num> <end col letter (lowercase)><end row num>
*/
void send_move(Move newMove);