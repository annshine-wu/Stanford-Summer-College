/* Submitted by: Justin Lee, Annshine Wu
 * Assignment: Boggle
 * This program uses backtracking recursion techniques to create a simple Boggle game
 * in which the human player and the computer searches for words. */

#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "bogglegui.h"
using namespace std;

//This function recursively searches for the word in the boggle board. Each time a recursive call is made, which
//is when the first character of the word is equal to the current tile of the board, the word is substringed
//so that the first character is cut off. When the word becomes an empty string, which is the base case, the
//recursive function returns true, meaning the entire word was found in the boggle. The function takes in
//multiple parameters, including the same ones from the wrapper function. The new parameters is a set of
//integer vectors representing the positions of the tiles/paths that have already been explored. The last two
//parameters, row and column, represent the tile that has just been explored, so the recursive function can
//explore the neighboring tiles.
bool humanWordSearchHelper(Grid<char>& board, Lexicon& dictionary, string word, Set<Vector<int> >& marked, int row, int column){
    if(word == ""){
        Vector<int> pos = {row,column};
        marked.add(pos);
        BoggleGUI::setHighlighted(pos.get(0), pos.get(1), true);
        return true;
    } else{
        bool check = false;
        Vector<int> pos = {row,column};
        marked.add(pos);
        BoggleGUI::setHighlighted(pos.get(0), pos.get(1), true);
        if(board.inBounds(row,column+1) && !marked.contains({row, column+1}) && board[row][column+1] == word[0]){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row,column+1);
        }
        if(board.inBounds(row,column-1) && !marked.contains({row, column-1}) && board[row][column-1] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row,column-1);
        }
        if(board.inBounds(row+1,column) && !marked.contains({row+1, column}) && board[row+1][column] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row+1,column);
        }
        if(board.inBounds(row+1,column-1) && !marked.contains({row+1, column-1}) && board[row+1][column-1] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row+1,column-1);
        }
        if(board.inBounds(row+1,column+1) && !marked.contains({row+1, column+1}) && board[row+1][column+1] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row+1,column+1);
        }
        if(board.inBounds(row-1,column) && !marked.contains({row-1, column}) && board[row-1][column] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row-1,column);
        }
        if(board.inBounds(row-1,column-1) && !marked.contains({row-1, column-1}) && board[row-1][column-1] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row-1,column-1);
        }
        if(board.inBounds(row-1,column+1) && !marked.contains({row-1, column+1}) && board[row-1][column+1] == word[0] && !check){
            check = humanWordSearchHelper(board,dictionary,word.substr(1),marked,row-1,column+1);
        }
        if(check == false){
            BoggleGUI::setHighlighted(pos.get(0), pos.get(1), false);
            marked.remove(pos);
        }
        pause(100);
        return check;
    }
}

//This function does initial checks before calling the recursive function. It checks if the word
//is contained in the dictionary and if it is long enough, and then is converted to all upper case
//so that is able to be compared to the letters on the board. A nested for loop runs through each letter
//of the board to find the starting point of the word. When a match is found, the recursive helper function
//is called, and the function returns true if the recursive function returns true, which means a match of
//the entire word is found in the boggle board.
bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word){
    if(!dictionary.contains(word) || word.length() < BoggleGUI::MIN_WORD_LENGTH){
        return false;
    }
    BoggleGUI::clearHighlighting();
    word = toUpperCase(word);
    Set<Vector<int> > marked;
    for(int i = 0; i < board.numRows(); i++){
        for(int j = 0; j < board.numCols(); j++){
            if(board.get(i,j) == word[0]){
                if(humanWordSearchHelper(board, dictionary, word.substr(1), marked, i, j)){
                    if(word.length() == 4) BoggleGUI::scorePointsHuman(1);
                    else if(word.length() == 5) BoggleGUI::scorePointsHuman(2);
                    else if(word.length() == 6) BoggleGUI::scorePointsHuman(3);
                    else if(word.length() == 7) BoggleGUI::scorePointsHuman(5);
                    else if(word.length() > 7) BoggleGUI::scorePointsHuman(11);
                    return true;
                }
            }
        }
    }
    return false;
}

// This is the recursive function that does the exhaustive word search.
// It returns true and false based on whether a single word has been found
// It checks whether the inputted row and column is out of bounds bounds and whether its already been marked, if yes: return false
// Then it adds the new letter to the "buildUp" word. It checks if the dictionary contains a word with the prefix, if not: return false
// Next, it checks:
//     1. whether the word is contained within the dictionary
//     2. whether the human found it
//     3. whether the computer has already found it
//     4. whether its length > minimum word length
// If all of these conditions fit, then it adds the word to the collection of already-found words
// Then, it marks the row and column and calls the recursive function 8 more times for its neighbors.
// It unmarks the position after returning from all the recursive calls.
bool findAllWords(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords, Set<string>& collection, Set<Vector<int> >& marked, int row, int column, string buildUp){
    if(!board.inBounds(row,column) || marked.contains({row,column})){
        return false;
    }
    buildUp += board[row][column];
    if(!dictionary.containsPrefix(buildUp)){
        return false;
    }
    if(dictionary.contains(buildUp) && !collection.contains(buildUp) && !humanWords.contains(buildUp) && buildUp.length() >= BoggleGUI::MIN_WORD_LENGTH){
        collection.add(buildUp);
    }
    Vector<int> pos = {row,column};
    marked.add(pos);
    findAllWords(board, dictionary, humanWords, collection, marked, row+1, column, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row+1, column+1, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row+1, column-1, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row-1, column, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row-1, column+1, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row-1, column-1, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row, column+1, buildUp);
    findAllWords(board, dictionary, humanWords, collection, marked, row, column-1, buildUp);
    if(buildUp.length() <= 2){
        buildUp = "";
    } else{
        buildUp.substr(buildUp.length()-2);
    }
    marked.remove(pos);
    return true;
}

//This function searches for all remaining words of the boggle puzzle. The nested for loop gos through
//every tile in the boggle board and runs the helper recursive function. The function then goes through
//each found word and assigns points to the score.
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords) {
    Set<string> todo;
    Set<Vector<int> > marked;
    for(int x = 0; x < board.numRows(); x++){
        for(int y = 0; y < board.numRows(); y++){
            findAllWords(board,dictionary,humanWords, todo, marked, x, y, "");
        }
    }
    for(string word: todo){
        if(word.length() == 4) BoggleGUI::scorePointsComputer(1);
        else if(word.length() == 5) BoggleGUI::scorePointsComputer(2);
        else if(word.length() == 6) BoggleGUI::scorePointsComputer(3);
        else if(word.length() == 7) BoggleGUI::scorePointsComputer(5);
        else if(word.length() > 7) BoggleGUI::scorePointsComputer(11);
    }
    return todo;
}
