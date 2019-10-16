/* Submitted by: Annshine Wu
 * Assignment: ADT NGrams(Part B)
 * The objective of the program is to read an input file and map it according to a specified N value.
 * Then, the program should generate a specified number of random words.
*/
#include <iostream>
#include "console.h"
#include "simpio.h"
#include <fstream>
#include "filelib.h"
#include "vector.h"
#include "map.h"
#include "random.h"
using namespace std;

void printInstructions();
int processInputFile(Map< Vector<string>,Vector<string>>&);
bool generateRandomWords(Map< Vector<string>,Vector<string>>& , Vector<string>& , int);
void printOutput(Vector<string>);

int main() {
    printInstructions();
    Map< Vector<string>,Vector<string>> ngrams;
    int n = processInputFile(ngrams);
    if(n > 0){
        Vector<string> output;
        while(generateRandomWords(ngrams,output,n)){
            printOutput(output);
            output.clear();
        }
    }
    cout << "Exiting." << endl;
    return 0;
}

// printInstructions prints instructions.
void printInstructions(){
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" << endl;
    cout << "This program generates random text based on a document." << endl;
    cout << "Give me an input file and an 'N' value for groups" << endl;
    cout << "of words, and I'll create random text for you." << endl;
    cout << endl;
}

// processInputFile prompts the user for an input file and N
// It also sorts the input into the referenced map (ngrams)
// It retursn n
int processInputFile(Map< Vector<string>,Vector<string>>& ngrams){
    ifstream infile;
    promptUserForFile(infile, "Input file name? ", "Unable to open that file.  Try again.");
    int n = getInteger("Value of N: ", "Illegal integer format. Try again.");
    while(n < 2){
        cout << "N must be 2 or greater." << endl;
        n = getInteger("Value of N: ", "Illegal integer format. Try again.");
    }
    string input;
    Vector<string> window, fullInput;
    while(infile >>	input)	{
        fullInput.add(input);
        if(window.size() >= n-1){
            Vector<string> temp = ngrams.get(window);
            temp.add(input);
            ngrams.put(window,temp);
            window.remove(0);
        }
        window.add(input);
    }
    if(n > fullInput.size()){
        cout << "N is larger than the number of words in the file." << endl;
        cout << "Unable to compute N-grams." << endl;
        return 0;
    }
    for(int x = 0; x < n-1; x++){
        Vector<string> temp = ngrams.get(window);
        temp.add(fullInput[x]);
        ngrams.put(window,temp);
        window.remove(0);
        window.add(fullInput[x]);
    }
    cout << endl;
    return n;
}

// generateRandomWords returns T/F to indicate whether more than 1 word is generated (0 means quitting the program)
// It prompts the user for a certain number of words to generate then generates that specificed number of words
// It starts with a random word and uses ngrams to map to another word randomly until enough words are added to the output
// Vector<string> output is modified so output will contain the final stream of words
bool generateRandomWords(Map< Vector<string>,Vector<string>>& ngrams, Vector<string>& output, int n){
    int numWords = getInteger("# of random words to generate (0 to quit): ", "Illegal integer format. Try again.");
    while(numWords < n){
        if(numWords == 0){
            return false;
        }
        cout << "Must be at least " << n << " words." << endl;
        cout << endl;
        numWords = getInteger("# of random words to generate (0 to quit): ", "Illegal integer format. Try again.");
    }
    int random = randomInteger(0,ngrams.size()-1);
    Vector<Vector<string>> keys = ngrams.keys();
    output+= keys[random];
    Vector<string> window = keys[random];
    for(int x = 0; x <= numWords-n; x++){
        random = randomInteger(0,ngrams[window].size() - 1);
        string newWord = ngrams.get(window)[random];
        output.add(newWord);
        window.add(newWord);
        window.remove(0);
    }
    return true;
}

// printOutput takes in a vector of strings and outputs them in specific formatting
void printOutput(Vector<string> output){
    cout << "... ";
    for(int x = 0; x < output.size(); x++){
        cout << output[x] << " ";
    }
    cout << "..." << endl;
    cout << endl;
}
