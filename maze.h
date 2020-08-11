//------------------------------------------------------------------------------
//  File:               maze.h
//  Description:        Declarations for the maze project
//  Author:             David Landry
//                      CSS 342, Winter 2018
//                      Assignment 3: Recursive Maze Walk
//  Environment:        Written and compiled using Microsoft Visual Studio
//                          Community 2017.
//------------------------------------------------------------------------------
#ifndef MAZE_H
#define MAZE_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include "coordinates.h"

enum MAZE_COORDINATES{COL=0, ROW=1};

class Maze
{
public:
    Maze() {}
    ~Maze();
    Coordinates& getStart() { return m_mazeGrid[m_currentLocation[ROW]][m_currentLocation[COL]]; }
    Coordinates& getExit();
    bool step(Coordinates& start, Coordinates& end);
    Coordinates getNextStep(const Coordinates& currentLocation) const;
    void markVisited(Coordinates& visited) { visited.setVisited(); }
    int readFile(std::string fileName);
    void printGrid(std::ostream& sout = std::cout) const;
    const std::vector<Coordinates>& accessPath() const { return m_visited; }
private:
    int m_currentLocation[2];
    int m_exitLocation[2];
    Coordinates** m_mazeGrid;
    int m_width;
    int m_height;
    bool m_atGoal = false;
    std::vector<Coordinates> m_visited;
};

namespace DL_MAZE_WALK
{

}
#endif