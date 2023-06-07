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

//