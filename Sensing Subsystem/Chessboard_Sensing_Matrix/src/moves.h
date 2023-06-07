/*
    This library file will declare functions pertaining to the calculation 
    of what types of move has been made in a given period of time
*/
#include <list>
#include "chessboard.h"

//Used to represent whether a move is a piece being placed or lifted
enum Delta
{
    place,
    lift
};

//Used to represent a change of position; has indices for row, column, and 
struct PosChange
{
    int row;
    int col;
    enum Delta direc;

    PosChange(int _row, int _col, enum Delta _direc) :
              row(_row), col(_col), direc(_direc) {}
};

// Define the list of moves
extern std::list<PosChange> moveList;

// The different types of moves that can be made
enum MoveType
{
    shift,
    capture,
    invalid
};

struct Move
{
    int startRow;
    int startCol;
    int endRow;
    int endCol;
    MoveType type;

    Move(int _startRow = 0, int _startCol = 0, int _endRow = 0, int _endCol = 0, MoveType _type = invalid) :
         startRow(_startRow), startCol(_startCol), endRow(_endRow), endCol(_endCol), type(_type) {}
};

// Cleans the list of move changes such that it's more easily read
void clean_moves();

// Calculates what type of move is needed, and returns it
Move calculate_move();