//------------------------------------------------------------------------------
//  File:               Coordinates.cpp
//  Description:        Definitions of methods for the Coordinates class
//  Author:             David Landry
//                      CSS 342, Winter 2018
//                      Assignment 3: Recursive Maze Walk
//  Environment:        Written and compiled using Microsoft Visual Studio
//                          Community 2017.
//------------------------------------------------------------------------------

#include "coordinates.h"

//------------------------------------------------------------------------------
//  Method:         Coordinates
//  Description:    Default constructor for a Coordinates data type.
//  Precondition:   The character parameter must be a valid map symbol.
//------------------------------------------------------------------------------
Coordinates::Coordinates(int row, int col, char character, bool hasVisited)
{
    switch (character)
    {
    case '#':
    case 'o':
    case '+':
    case ' ':
        m_character = character;
        break;
    default:
        throw std::logic_error("Invalid map character.");
    }
    m_hasVisited = hasVisited;
    m_row = row;
    m_col = col;
}

//------------------------------------------------------------------------------
//  Method:         setVisited
//  Description:    Marks a set of coordinates as visited both with a boolean
//                      flag and an appropriate map marker.
//------------------------------------------------------------------------------
void Coordinates::setVisited()
{
    m_hasVisited = true;
    m_character = '+';
}

//------------------------------------------------------------------------------
//  Method:         setRow
//  Description:    Sets the coordinate row.
//------------------------------------------------------------------------------
void Coordinates::setRow(int row)
{
    if (row >= 0)
        m_row = row;
    else
        throw std::logic_error("Row value must be 0 or positive.");
}

//------------------------------------------------------------------------------
//  Method:         setColumn
//  Description:    Sets the coordinate column.
//------------------------------------------------------------------------------
void Coordinates::setColumn(int col)
{
    if (col >= 0)
        m_col = col;
    else
        throw std::logic_error("Column value must be 0 or positive.");
}

//------------------------------------------------------------------------------
//  Method:         setCharacter
//  Description:    Sets the coordinate map symbol.
//  Precondition:   This method must take in a correct map symbol. Correct
//                      map symbols are ' ' (space), '#', 'o' (lowercase o),
//                      and '+'.
//------------------------------------------------------------------------------
void Coordinates::setCharacter(char symbol)
{
    if (symbol == ' ' || symbol == '#' || symbol == 'o' || symbol == '+')
        m_character = symbol;
    else
        throw std::logic_error("Invalid map symbol detected.");
}

//------------------------------------------------------------------------------
//  Method:         operator==
//  Description:    "Is equal to" operator overload. Checks if row & column
//                      of the lhs are equal to those of the rhs.
//------------------------------------------------------------------------------
bool Coordinates::operator==(const Coordinates& rhs) const
{
    return (this->m_col == rhs.getColumn() && this->m_row == rhs.getRow());
}

//------------------------------------------------------------------------------
//  Method:         operator!=
//  Description:    "Is not equal to" operator overload. Checks if row & column
//                      of the lhs are not equal to those of the rhs.
//------------------------------------------------------------------------------
bool Coordinates::operator!=(const Coordinates& rhs) const
{
    return (this->m_col != rhs.getColumn() || this->m_row != rhs.getRow());
}

//------------------------------------------------------------------------------
//  Function:       operator<<
//  Description:    Non-class operator overload of the stream output operator.
//                      Used to help print coordinates in a consistent format.
//------------------------------------------------------------------------------
std::ostream& operator<<(std::ostream& sout, const Coordinates& rhs)
{
    sout << "[" << rhs.getColumn() << ", " << rhs.getRow() << "]";
    return sout;
}