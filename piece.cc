#include "piece.h"

Piece::Piece(char colour) : colour_(colour), row_(-1), col_(-1) {}

char Piece::getColour()
{
    return colour_;
}

S8 Piece::getRow()
{
    return row_;
}

S8 Piece::getCol()
{
    return col_;
}

void Piece::setCoords(S8 row, S8 col)
{
    row_ = row;
    col_ = col;
}
