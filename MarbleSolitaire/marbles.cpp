// Submitted by: Justin Lee, Annshine Wu
// Assignment: Marbles
// Uses a recursive function to solve the marbles puzzle, leaving only one marble on the board

#include "grid.h"
#include "vector.h"
#include "set.h"
#include "marbletypes.h"
#include "compression.h"
#include "marbleutil.h"
using namespace std;

bool solvePuzzleHelper(Grid<Marble>&, int, Vector<Move>&, Set<BoardEncoding>&);

// solvePuzzle calls the helper recursive function
bool solvePuzzle(Grid<Marble>& board, int marbleCount, Vector<Move>& moveHistory) {
    Set<BoardEncoding> pastBoards;
    return solvePuzzleHelper(board,marbleCount,moveHistory,pastBoards);
}

// solvePuzzleHelper keeps track of the board, number of left on the board, the moveHistory, and all the pastBoards
// It returns true and false based on whether it solved the puzzle
// Everytime it enters a new state, it compresses the board and checks whether it has entered the state before
// If not, it adds the encoding to the pastBoards to avoid entering the state again
// Then, it checks the marbleCount. If it is equal to 1, it returns true (base case: the function has solved it)
// It uses findPossibleMoves and loops through all the possible moves.
// It makes the move, add it to the history, and enters the recursive function to see if the move has solved the puzzle.
// If it has solved the puzzle, it returns true. If it has not, it unmakes the move and removes it from the history.
bool solvePuzzleHelper(Grid<Marble>& board, int marbleCount, Vector<Move>& moveHistory, Set<BoardEncoding>& pastBoards){
    BoardEncoding encoding = compressBoard(board);
    if(!pastBoards.contains(encoding)){
        pastBoards.add(encoding);
        if(marbleCount == 1){
            return true;
        }
        Vector<Move> possibleMoves = findPossibleMoves(board);
        for(int x = 0; x < possibleMoves.size(); x++){
            makeMove(possibleMoves[x],board);
            moveHistory.add(possibleMoves[x]);
            bool check = solvePuzzleHelper(board, marbleCount - 1, moveHistory,pastBoards);
            if(!check){
                undoMove(possibleMoves[x], board);
                moveHistory.remove(moveHistory.size()-1);
            } else{
                return true;
            }
        }
    }
    return false;
}
