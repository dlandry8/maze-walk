//------------------------------------------------------------------------------
//  File:               coordinates.h
//  Description:        Declarations for the coordinates class.
//  Author:             David Landry
//                      CSS 342, Winter 2018
//                      Assignment 3: Recursive Maze Walk
//  Environment:        Written and compiled using Microsoft Visual Studio
//                          Community 2017.
//------------------------------------------------------------------------------
#ifndef COORDINATES_H
#define COORDINATES_H
#include <string>
#include <iostream>

class Coordinates
{
public:
    Coordinates(int row = 0, int col = 0, char character = ' ', 
        bool hasVisited = false);
    char getCharacter() const { return m_character; }
    bool getIfVisited() const { return m_hasVisited; }
    int getRow() const { return m_row; }
    int getColumn() const { return m_col; }
    void setVisited();
    void setRow(int row);
    void setColumn(int col);
    void setCharacter(char symbol);
    bool operator==(const Coordinates& rhs) const;
    bool operator!=(const Coordinates& rhs) const;
    friend std::ostream& operator<<(std::ostream& sout, const Coordinates& rhs);
private:
    int m_row;
    int m_col;
    char m_character;
    bool m_hasVisited;
};
#endif