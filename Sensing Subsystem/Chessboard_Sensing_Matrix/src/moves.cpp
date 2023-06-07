/*
    This C++ file will define functions pertaining to the calculation 
    of what types of move has been made in a given period of time
*/
#include "moves.h"

extern std::list<PosChange> moveList = {};

void clean_moves()
{
    
}

Move calculate_move()
{
    if (moveList.size() < 2)
    {
        // Returns default move (invalid, from A1 to A1)
        return Move();
    }
    // 
    if (moveList.size() == 2)
    {

    }

}