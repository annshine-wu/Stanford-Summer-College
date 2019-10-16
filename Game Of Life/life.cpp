/* Submitted by: Annshine Wu
 *
 * Version: life-extra.cpp (extra feature of a random world generation)
 *
 * Assignment: Game of Life
 * The program should read an input file given into a grid.
 * Then, display a main menu where users can either choose to animate, tick, or quit the program.
 * Tick will display the next generation of life. Animate will display the changing generations by clearing the console.
 * Quit will allow the user to either end the program or read another input file.
 * The rules for the next generation of life will follow a list of rules that is displayed in the beginning.
 */

#include <iostream>
#include "console.h"
#include <fstream>
#include "filelib.h"
#include "grid.h"
#include "strlib.h"
#include "simpio.h"
#include "lifegui.h"
#include <time.h>
using namespace std;

void printGameInstructions();
void processInputFile(Grid<string>&);
void generateRandomGrid(Grid<string>&);
void printGrid(Grid<string>&);
bool mainMenu(Grid<string>&);
void displayGUI(Grid<string>&);
void tick(Grid<string>&);
void animate(Grid<string>&);
int countNeighbors(Grid<string>&, int, int);
int countSelf(Grid<string>&, int, int);

int main() {
    printGameInstructions();
    Grid<string> board;
    processInputFile(board);
    LifeGUI::initialize();
    while(mainMenu(board)){
        processInputFile(board);
    }
    LifeGUI::shutdown();
    cout << "Have a nice Life!" << endl;
    return 0;
}

// printGameInstructions prints the initial game instructions
void printGameInstructions(){
    cout << "Welcome to the CS 106B/X Game of Life!" << endl;
    cout << "This program simulates the lifecycle of a bacterial colony." << endl;
    cout << "Cells (X) live and die by the following rules:" << endl;
    cout << "* A cell with 1 or fewer neighbors dies." << endl;
    cout << "* Locations with 2 neighbors remain stable." << endl;
    cout << "* Locations with 3 neighbors will create life." << endl;
    cout << "* A cell with 4 or more neighbors dies." << endl << endl;
}

// processInputFile prompts the user for a file
// then, it processes the input by organizing the information inside the provided grid
void processInputFile(Grid<string>& board){
    ifstream infile;
    string fileName = getLine("Grid input file name?");
    while(openFile(infile, fileName) == false && fileName != "random"){ // end while loop if the file can be opened or "random" is inputted as the filename
        cout << "Unable to open that file.  Try again." << endl;
        fileName = getLine("Grid input file name?");
    }
    if(fileName == "random"){
        generateRandomGrid(board);
    }
    else{
        string input;
        getline(infile,input);
        int totalRow = stringToInteger(input);
        getline(infile,input);
        int totalColumn = stringToInteger(input);

        board.resize(totalRow,totalColumn);
        for(int r = 0; r < board.numRows(); r++){
            getline(infile,input);
            for(int c = 0; c < board.numCols(); c++){
                board[r][c] = input[c];
            }
        }
        infile.close();
    }
}

void generateRandomGrid(Grid<string>& board){
    srand(time(nullptr));
    int totalRow = rand() % 100 + 1;
    int totalColumn = rand() % 100 + 1;
    board.resize(totalRow,totalColumn);
    cout << totalRow << endl;
    cout << totalColumn << endl;
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){
            int aliveOrDead = rand() % 2; // 0 or 1
            if(aliveOrDead == 0){
                board[r][c] = "-";
            }
            else{
                board[r][c] = "X";
            }
        }
    }
}

// mainMenu processes the possible choices (tick, animate, or quit)
// mainMenu also calls the functions for animate or tick, then prints and updates the GUI
// returns True or False when the user decides to quit to represent whether the user wants to load another file
// True - load another file / False - does not load another file
bool mainMenu(Grid<string>& board){
    printGrid(board);
    displayGUI(board);
    string choice = getLine("a)nimate, t)ick, q)uit? ");
    choice = toLowerCase(choice);
    while(choice != "q"){
        if(choice == "a"){
            animate(board);
            printGrid(board);
            displayGUI(board);
        }else if(choice == "t" || choice == ""){
            tick(board);
            printGrid(board);
            displayGUI(board);
        }
        else{
            cout << "Invalid choice; please try again." << endl;
        }
        choice = getLine("a)nimate, t)ick, q)uit? ");
        choice = toLowerCase(choice);
    }
    return getYesOrNo("Load another file? (y/n) ", "Please type a word that starts with 'Y' or 'N'.");
}

// displayGUI updates and displays the GUI based on its referenced grid
void displayGUI(Grid<string>& board){
    LifeGUI::resize(board.numRows(), board.numCols());
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){
            if(board[r][c] == "X"){
                LifeGUI::fillCell(r,c);
            }
        }
    }
    LifeGUI::repaint();
}

// tick updates the board by checking whether a spot should be dead, alive, or stable
// if the neighbor count <= 1 or >= 4, the cell dies
// if the neighbor count = 2, the cell remains stable
// if the neighbor count = 3, the cell will be alive
void tick(Grid<string>& board){
    Grid<string> newBoard;
    newBoard.resize(board.numRows(), board.numCols());
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){
            int neighbors = countNeighbors(board,r,c);
            if(neighbors <= 1 || neighbors >= 4){ // Cell dies
                newBoard[r][c] = "-";
            } else if(neighbors == 2){ // Cell remains stable
                newBoard[r][c] = board[r][c];
            } else if(neighbors == 3){ // Cell is alive
                newBoard[r][c] = "X";
            }
        }
    }
    board = newBoard;
}

// animate asks for the number of frames, then calls tick that number of times
// prints the board, updates the GUI, and clears the console every 100 ms
void animate(Grid<string>& board){
    int frames = getInteger("How many frames? ", "Illegal integer format. Try again.");
    if(frames > 0){ // Checks that entered frames isn't negative; if negative no animation will occur
        for(int i = 0; i < frames; i++){
            tick(board);
            printGrid(board);
            displayGUI(board);
            pause(100);
            clearConsole();
        }
    }
}

// countNeighbors returns the number of neighbor a particular cell (at the designated row and column) has
// It adjusts for boundaries by setting any that goes out of bounds to the other side of the grid (to become toroidal)
// It checks all neighbors in the 8 possibilities by calling countSelf for each neighbor's spot
int countNeighbors(Grid<string>& board, int row, int column){
    // Adjust for boundaries
    int columnMinus = column - 1;
    if(columnMinus < 0){
        columnMinus = board.numCols() - 1;
    }
    int columnPlus = column + 1;
    if(columnPlus >= board.numCols()){
        columnPlus = 0;
    }
    int rowMinus = row - 1;
    if(rowMinus < 0){
        rowMinus = board.numRows() - 1;
    }
    int rowPlus = row + 1;
    if(rowPlus >= board.numRows()){
        rowPlus = 0;
    }

    int count = 0;
    // Check the Eight Possible Spots for alive cells
    count += countSelf(board, rowMinus, columnMinus); // row - 1, column - 1
    count += countSelf(board, rowMinus, column); // row - 1, column
    count += countSelf(board, rowMinus, columnPlus); // row - 1, column + 1
    count += countSelf(board, row, columnMinus); // row, column - 1
    count += countSelf(board, row, columnPlus); // row, column + 1
    count += countSelf(board, rowPlus, columnMinus); // row + 1, column - 1
    count += countSelf(board, rowPlus, column); // row + 1, column
    count += countSelf(board, rowPlus, columnPlus); // row + 1, column + 1
    return count;
}

// countSelf returns 0 or 1 depending on whether the cell in the particular row and column is alive
// This function is used to check whether a neighboring cell is alive
// It is used in countNeighbors to check the 8 possibilities and count the number of neighbors
int countSelf(Grid<string>& board, int row, int column){
    if(board[row][column] == "X"){
        return 1; // if cell is alive, return 1 to count the neighbor
    }
    return 0; // if cell is NOT alive, return 0
}

// printGrid accepts a Grid reference and prints the grid
void printGrid(Grid<string>& board){
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c < board.numCols(); c++){
            cout << board[r][c];
        }
        cout << endl;
    }
}
