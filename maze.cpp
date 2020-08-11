//------------------------------------------------------------------------------
//  File:               maze.cpp
//  Description:        Definitions for the maze project
//  Author:             David Landry
//                      CSS 342, Winter 2018
//                      Assignment 3: Recursive Maze Walk
//  Environment:        Written and compiled using Microsoft Visual Studio
//                          Community 2017.
//------------------------------------------------------------------------------
#include "maze.h"

// These macro definitions will save horizontal space later on:
#define STEP_SOUTH m_mazeGrid[currentLocation.getRow() + 1][currentLocation.getColumn()]
#define STEP_EAST m_mazeGrid[currentLocation.getRow()][currentLocation.getColumn() + 1]
#define STEP_WEST m_mazeGrid[currentLocation.getRow()][currentLocation.getColumn() - 1]
#define STEP_NORTH m_mazeGrid[currentLocation.getRow() - 1][currentLocation.getColumn()]


//------------------------------------------------------------------------------
//  Method:             ~Maze
//  Description:        Destructor for the Maze class. Deallocates memory used
//                          to construct a map grid, if a grid was successfully
//                          created.
//------------------------------------------------------------------------------
Maze::~Maze()
{
    // Deallocate memory used to build the maze grid
    if (m_mazeGrid != nullptr)
    {
        for (int i = 0; i < m_height; i++)
            delete[] m_mazeGrid[i];
        delete[] m_mazeGrid;
    }
}

//------------------------------------------------------------------------------
//  Method:             getExit
//  Description:        Returns the coordinates object corresponding to the
//                          maze object's exit.
//  Precondition:       An exit must exist.
//------------------------------------------------------------------------------
Coordinates& Maze::getExit()
{
    if (m_exitLocation[COL] >= 0 && m_exitLocation[ROW] >= 0)
        return m_mazeGrid[m_exitLocation[ROW]][m_exitLocation[COL]];
    else
        throw std::runtime_error("There is no exit!");
}


//------------------------------------------------------------------------------
//  Method:         step
//  Description:    Steps through the maze to see if there's a path to the end.
//                      This is the main recursive method for all your maze 
//                      running needs.
//------------------------------------------------------------------------------
bool Maze::step(Coordinates& start, Coordinates& end)
{
    markVisited(m_mazeGrid[start.getRow()][start.getColumn()]);
    m_visited.push_back(start);
    bool foundTheExit = (start == end);
    if (!foundTheExit)
    {
        Coordinates nextStep = getNextStep(start);
        while (!foundTheExit && (nextStep != Coordinates(-1,-1)))
        {
            foundTheExit = step(nextStep, end);
            if (!foundTheExit)
                nextStep = getNextStep(nextStep);
        }
    }
    return foundTheExit;
}



//------------------------------------------------------------------------------
//  Method:         getNextStep
//  Description:    Gets the coordinates for the next step when attempting to
//                      step to the exit.
//  Note:           To properly program the m_mazeGrid array, I had to do so in
//                      order of (row, column). However, the coord. system of
//                      the project specifications call for (column, row) 
//                      coordinates. Therefore, the coordinates for m_mazeGrid 
//                      appear to be reversed, although they refer to the 
//                      correct spot on the grid.
//                  Also, this method uses macros defined at the top of this
//                      document.
//------------------------------------------------------------------------------
Coordinates Maze::getNextStep(const Coordinates& currentLocation) const
{
    // South
    if (STEP_SOUTH.getCharacter() != '#' && !(STEP_SOUTH.getIfVisited()) && 
        currentLocation.getRow() < m_height - 1)
        return STEP_SOUTH;
    // East
    else if (STEP_EAST.getCharacter() != '#' && !(STEP_EAST.getIfVisited()) && 
        currentLocation.getColumn() < m_width - 1)
        return STEP_EAST;
    // West
    else if (STEP_WEST.getCharacter() != '#' && !(STEP_WEST.getIfVisited()) && 
        currentLocation.getColumn() > 0)
        return STEP_WEST;
    // North
    else if (STEP_NORTH.getCharacter() != '#' && !(STEP_NORTH.getIfVisited()) &&
        currentLocation.getRow() > 0)
        return STEP_NORTH;
    // Otherwise can't move
    else
        return Coordinates(-1,-1);
}

//------------------------------------------------------------------------------
//  Method:         readFile
//  Description:    This file reads a maze file and creates a maze grid.
//  Precondition:   The file passed in must be a text file whose text consists
//                      of a line of coordinate data followed by a properly
//                      formatted map with correct map symbols and an exit.
//------------------------------------------------------------------------------
int Maze::readFile(std::string fileName)
{
    m_mazeGrid = nullptr;
    // Set a default exit location to make it easier to test for a proper exit.
    m_exitLocation[ROW] = -1;
    m_exitLocation[COL] = -1;
    std::ifstream mazeReader(fileName);
    std::vector<std::string> lines;
    std::string line;
    if (mazeReader.is_open())
    {
        // Separate each line of the map grid to its own string, making parsing
        //  much easier.
        while (!mazeReader.eof())
        {
            std::getline(mazeReader, line);
            lines.push_back(line);
        }
        mazeReader.close();
        // Parse the first line:
        std::istringstream lineReader(lines[0]);
        if (lineReader.peek() != '\n')
            lineReader >> m_height;
        else
            throw std::logic_error
            ("Error in the configuration of the maze file.");
        if (lineReader.peek() != '\n')
            lineReader >> m_width;
        else
            throw std::logic_error
            ("Error in the configuration of the maze file.");
        if (lineReader.peek() != '\n')
            lineReader >> m_currentLocation[COL];
        else
            throw std::logic_error
            ("Error in the configuration of the maze file.");
        if (lineReader.peek() != '\n')
            lineReader >> m_currentLocation[ROW];
        else
            throw std::logic_error
            ("Error in the configuration of the maze file.");
        if (m_width < 1 || m_height < 1 || m_currentLocation[ROW] < 1 || 
            m_currentLocation[COL] < 1 || m_currentLocation[ROW] >= m_height || 
            m_currentLocation[COL] >= m_width || !lineReader)
            throw std::logic_error
            ("Error in the configuration of the maze file.");
        // Read the map grid:
        m_mazeGrid = nullptr;
        m_mazeGrid = new Coordinates*[m_height];
        for (int i = 1; i <= m_height; i++)
        {
            m_mazeGrid[i - 1] = nullptr;
            m_mazeGrid[i - 1] = new Coordinates[m_width];
            for (int j = 0; j < m_width; j++)
            {
                m_mazeGrid[i - 1][j].setRow(i - 1);
                m_mazeGrid[i - 1][j].setColumn(j);
                m_mazeGrid[i - 1][j].setCharacter(lines[i][j]);
                if (m_mazeGrid[i - 1][j].getCharacter() == 'o')
                {
                    if (m_exitLocation[ROW] == -1 && m_exitLocation[COL] == -1)
                    {
                        m_exitLocation[ROW] = i - 1;
                        m_exitLocation[COL] = j;
                    }
                    else
                        throw std::logic_error
                        ("There can be only one exit in the maze.");
                }
            }
        }
        if (m_exitLocation[ROW] == -1 && m_exitLocation[COL] == -1)
            throw std::logic_error("There's no exit! You are trapped forever!");
    }// End if mazeReader.is_open()
    else
        throw std::runtime_error
        ("Invalid file. Check the spelling and access permission of the file.");
    return 0;
}

//------------------------------------------------------------------------------
//  Method:         printGrid
//  Description:    Prints the map grid to the output stream.
//------------------------------------------------------------------------------
void Maze::printGrid(std::ostream& sout) const
{
    for (int i = 0; i < m_height; i++)
    {
        for (int j = 0; j < m_width; j++)
        {
            std::cout << m_mazeGrid[i][j].getCharacter();
        }
        std::cout << std::endl;
    }
}