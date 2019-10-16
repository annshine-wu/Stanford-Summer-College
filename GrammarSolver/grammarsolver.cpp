// Submitted by: Justin Lee, Annshine Wu
// Assignment: Grammer Solver
// Grammer Solver takes in an input file with grammar rules, then reads it into a map.
// It utilizes the map (with rules) to generate a certain number of symbols and returns it in a vector.

#include "grammarsolver.h"
#include "map.h"
#include "strlib.h"
#include "vector.h"
#include "random.h"
using namespace std;

void formatInputFile(istream&, Map<string, Vector< Vector<string> > >&);
string generateSymbol(Map<string, Vector< Vector<string> > >&, string);

// grammarGenerate takes in an input file, a symbol, and a number.
// It creates a map of dictionary for rules based on the input file..
// Then, generates a specified symbol a certain number of times and adds them into a vector.
// Finally, it returns the vector (with the symbols).
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    if(symbol == ""){
        throw "The symbol entered is empty";
    }
    Vector<string> v;
    Map<string, Vector< Vector<string> > > dictionary;
    formatInputFile(input, dictionary);
    for(int i = 0; i < times; i++){
        string generate = generateSymbol(dictionary, symbol);
        generate = trim(generate);
        v.add(generate);
    }
    return v;
}

// formatInputFile takes in the input file and reads them into a map.
// The map has a string as the key (non-terminal) and a vector of a vector of strings as the value.
void formatInputFile(istream& input, Map<string, Vector< Vector<string> > >& dictionary){
    string line;
    while(getline(input, line)){
        line = trim(line);
        Vector<string> keySplit = stringSplit(line, "::="); // keySplit[0] will be the key (non-terminal value)
        if(dictionary.containsKey(keySplit[0])){
            throw "There is a duplicate rule";
        }
        Vector<string> pipeSplit = stringSplit(keySplit[1], "|"); // pipeSplit will contain each individual rule
        Vector< Vector<string> > inputData;
        for(int i = 0; i < pipeSplit.size(); i++){ // Read through all rules
            Vector<string> spaceSplit = stringSplit(pipeSplit[i], " "); // Split each rule with spaces
            inputData.add(spaceSplit); // Add each rule represented by a vector of strings back to inputData
        }
        dictionary.put(keySplit[0], inputData); // inputData is a vector of a vector of strings
   }
}

// generateSymbol returns a string of generated symbol
// base case occurs when the passed symbol is a terminal word (not a key in the dictionary) --> return the symbol itself
// recursive case:
//  1. generate a number to represent a rule to follow
//  2. generate a symbol for all the parts of the rule
//  3. return the entire phrase
string generateSymbol(Map<string, Vector< Vector<string> > >& dictionary, string symbol){
    if(!dictionary.containsKey(symbol)){ // base case: terminal
        return symbol + " "; // if symbol is not a key in the dictionary, simply return the value
    }
    int random = randomInteger(0 , dictionary[symbol].size() - 1); // generate random number to represent a rule
    string phrase = "";
    for(int i = 0; i < dictionary[symbol].get(random).size(); i++){
        // recursive case generates symbols for the undefined terminals
        phrase += generateSymbol(dictionary, dictionary[symbol].get(random).get(i));
    }
    return phrase;
}
