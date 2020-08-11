//------------------------------------------------------------------------------
//  File:               mazeDriver.cpp
//  Description:        Implementation of the maze walking algorithm.
//  Author:             David Landry
//                      CSS 342, Winter 2018
//                      Assignment 3: Recursive Maze Walk
//  Environment:        Written and compiled using Microsoft Visual Studio
//                          Community 2017.
//------------------------------------------------------------------------------
#include "maze.h"

//------------------------------------------------------------------------------
//  Method:             main
//  Description:        The main program file for stepping through a maze.
//  Arguments:          The file name.
//  Preconditions:      A file name is expected to be provided from the
//                          command line.
//------------------------------------------------------------------------------
int main(int argc, char* argv[])
{
    Maze testMaze;
    try
    {
        if (argv[1] == NULL)
        {
            std::cout << "Please specify a map file.";
            return 0;
        }
        else
            testMaze.readFile(argv[1]);
    }
    catch (std::exception e)
    {
        std::cout << e.what();
        return 0;
    }
    std::cout << "Start: " << testMaze.getStart() << std::endl;
    std::cout << "Exit:  " << testMaze.getExit() << std::endl;
    testMaze.printGrid();
    if (testMaze.step(testMaze.getStart(), testMaze.getExit()))
    {
        std::cout << "Exit reached! Press <enter> to see the route!";
        std::cin.get();
        system("cls");
        std::cout << "Start: " << testMaze.getStart() << std::endl;
        std::cout << "Exit:  " << testMaze.getExit() << std::endl;
        testMaze.printGrid();
        std::cout << "\nPress <enter> to see coordinates traversed." << std::endl;
        std::cin.get();
        for (int i = 0; i < testMaze.accessPath().size(); i++)
        {
            std::cout << testMaze.accessPath()[i] << std::endl;
        }
        std::cout << "PROFIT!\nPress <enter> to exit.";
    }
    else
        std::cout << "No path to the exit exists. Press <enter> to exit.";
    std::cin.get();    
    return 0;
}