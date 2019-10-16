/* Submitted by: Annshine Wu
 * Assignment: ADT Word Ladder(Part A)
 * The objective of the program is to print out the shortest possible word ladder
 * from one word to another by using a given dictionary and only modifying one character at the time.
 */
#include <iostream>
#include "console.h"
#include <fstream>
#include "filelib.h"
#include "set.h"
#include "simpio.h"
#include "strlib.h"
#include "queue.h"
#include "stack.h"
#include "vector.h"
using namespace std;

void printInstructions();
void processInputDictionary(Set<string>&);
bool inputTwoWords(string&,string&);
bool checkValidInput(Set<string>&, string, string);
void constructLadder(Set<string>&, string, string, Queue<Stack<string> >&);
bool examineNeighbors(Set<string>&, string, string, Queue<Stack<string> >&, Set<string>&);
void printAnswer(string, string, Stack<string>&);

bool subsequence(string w1, string w2, int index1, int index2){
    if(index1 == w1.length()){
        cout << "1";
        return true;
    }
    if(index2 >= w2.length()){
        cout << "2";
        return false;
    }
    if(w1.substr(index1,1) == w2.substr(index2,1)){
        cout << "3";
        return subsequence(w1,w2,index1+1,index2+1);
    }else{
        cout << "4";
        return subsequence(w1,w2,index1,index2+1);
    }
}

int main() {
    /* printInstructions();
    Set<string>	dictionary;
    processInputDictionary(dictionary);
    string w1, w2;
    while(inputTwoWords(w1,w2)){
        if(checkValidInput(dictionary,w1,w2)){
            Queue<Stack<string> > allLadders;
            constructLadder(dictionary,w1,w2,allLadders);
        }
        cout << endl;
    }
    cout << "Have a nice day." << endl; */
    bool first = subsequence("the","three",0,0);
    cout << first;
    cout << endl;
    first = subsequence("tab","boat",0,0);
    cout << first;
    return 0;
}

// printInstructions prints the starting instructions
void printInstructions(){
    cout << "Welcome to CS 106B/X Word Ladder!" << endl;
    cout << "Please give me two English words, and I will convert the" << endl;
    cout << "first into the second by modifying one letter at a time." << endl;
    cout << endl;
}

// processInputDictionary takes in a reference to a set of strings
// It prompts the user to input a dictionary file name, then adds each word to the referenced set
void processInputDictionary(Set<string>& dictionary){
    ifstream infile;
    promptUserForFile(infile, "Dictionary file name: ", "Unable to open that file.  Try again.");
    string line;
    while(getline(infile, line)){
        dictionary.add(line);
    }
    cout << endl;
    infile.close();
}

// inputTwoWords takes two parameters (references to word1 and word2)
// It returns T/F to represent whether the user wishes to quit the program
// It prompts the user to enter two words and saves it to word1 and word2
// If the user presses enter, the function will return false and quit (otherwise: true)
bool inputTwoWords(string& w1, string& w2){
    w1 = getLine("Word 1 (or Enter to quit): ");
    w1 = toLowerCase(w1);
    if(w1 == ""){
        return false;
    }
    w2 = " ";
    w2 = getLine("Word 2 (or Enter to quit): ");
    w2 = toLowerCase(w2);
    if(w2 == ""){
        return false;
    }
    return true;
}

// checkValidInput takes in a referenced set of strings and the two inputted words
// returns true if the input is valid or false if it doesnt and also prints a corresponding error message
bool checkValidInput(Set<string>& dictionary, string w1, string w2){
    if(!dictionary.contains(w1)|| !dictionary.contains(w2)){
        cout << "The two words must be found in the dictionary." << endl;
    } else if(w1.length() != w2.length()){
        cout << "The two words must be the same length." << endl;
    } else if(w1 == w2){
        cout << "The two words must be different." << endl;
    } else{
        return true;
    }
    return false;
}

// constructLadder uses examineNeighbors to check whether word 2 is found
// if w2 is never found and all possibilities have been exhausted (allLadders.size() == 0), a "no word ladder" message is printed
void constructLadder(Set<string>& dictionary, string w1, string w2, Queue<Stack<string> >& allLadders){
    Stack<string> original = {w1};
    allLadders.enqueue(original);
    bool found = false;
    Set<string> used = {w1};
    while(allLadders.size() > 0 && !found){
        found = examineNeighbors(dictionary,w1,w2,allLadders,used);
    }
    if(!found){
        cout << "No word ladder found from " << w2 << " back to " << w1 << endl;
    }
}

// examineNeighbors returns true if word2 is found (false otherwise)
// Attempts to make new words from the word on top of the dequeued stack by switching every character with the alphabet
// Then, it uses the dictionary to check whether the word is real.
// If the word is real AND the word is not already checked before:
//  1. the word is put inside a new stack with the same contents
//  2. the new stack is then queued into allLadders
//  3. the word is added to a "used words" list
bool examineNeighbors(Set<string>& dictionary, string w1, string w2, Queue<Stack<string> >& allLadders, Set<string>& used){
    Stack<string> dequeued = allLadders.dequeue();
    string lookAt = dequeued.peek();
    int length = lookAt.length();
    for(int i = 0; i < length; i++){
        for (char ch = 'a'; ch <= 'z'; ch++) {
            string neighbor = lookAt.substr(0,i);
            neighbor+= ch;
            neighbor+= lookAt.substr(i+1, length - 1 - i);
            if(dictionary.contains(neighbor) && used.contains(neighbor) == false){
                Stack<string> newLadder = dequeued;
                newLadder.push(neighbor);
                allLadders.enqueue(newLadder);
                used.add(neighbor);
                if(neighbor == w2){
                    printAnswer(w1,w2,newLadder);
                    return true;
                }
            }
        }
    }
    return false;
}

// printAnswer prints the ladder from the 2nd word back to the 1st word
void printAnswer(string w1, string w2, Stack<string>& newLadder){
    cout << "A ladder from " << w2 << " back to " << w1 <<":" << endl;
    while(!newLadder.isEmpty())	{
        cout << newLadder.pop() << " ";
    }
    cout << endl;
}


