/* Submitted by: Annshine Wu (annshine), Justin Lee (justin06)
   Assignment: Autocomplete
     Constructs a trie that can add words to the trie and return search results for suggestions
*/

#include "Autocomplete.h"
#include <cctype>
using namespace std;

/* The Autocomplete constructor initializes a root node, sets the letter it represents to "", and sets isWord to false
root represents the root node of the Trie
isWord represents whether the word formed at that node is a real word
ch is the letter that the node represents */
Autocomplete::Autocomplete() {
    root = new Node();
    root->isWord = false;
    root->ch = "";
}

/* The Autocomplete destructor takes a pointer to a node
 * Then, it uses a for loop to loop through its children to call on the recursive destructorHelper method
 * It deletes the node at the end of the function.
 * Result: Deletes the entire constructed Trie*/
void Autocomplete::destructorHelper(Autocomplete::Node* current){
    Vector<string> keys = current->children.keys();
    for(int x = 0; x < keys.size(); x++){
        destructorHelper(current->children[keys[x]]);
    }
    delete current;
}

/* The Autocomplete destructor calls the recursive destructorHelper function*/
Autocomplete::~Autocomplete() {
    destructorHelper(root);
}

/* addHelper is a recursive function
*  baseCase: index == text.size --> signifying that the entire word has been added
*  recursiveCase: each recursive call, it will look at the next letter within the text
*     if the next letter is already within the children, it will call the function again with the update node and index++
*     if the next letter is not already within the children, it will add it to the current node's children, then call the function
*        again with the updated node and index++ */
void Autocomplete::addHelper(Autocomplete::Node* current, string text, int index){
    if(index == text.size()){
        current->isWord = true;
        return;
    }
    string nextLetter = text.substr(index,1);
    if(current->children.containsKey(nextLetter)){
        addHelper(current->children[nextLetter], text, index+1);
    } else{
        Node* letterNode = new Node();
        letterNode->ch = nextLetter;
        current->children.put(nextLetter,letterNode);
        addHelper(current->children[nextLetter], text, index+1);
    }
}

/* The Autocomplete add calls the recursive addHelper function*/
void Autocomplete::add(const string& text) {
    addHelper(root,text,0);
}

/* suggestionsForHelper is a recursive helper function *
 * It will stop once maxHits == numFound as we have found enough autocomplete suggestions
 * Recursive case:
 * Option 1: We have not found the entire prefix yet --> keep recursively calling the function to find the entire word
 * Option 2: We have already found the prefix --> recursively call its children to find valid words --> add them to the results*/
void Autocomplete::suggestionsForHelper(const string& prefix, int maxHits, Set<string>& results, int& numFound, int index, string found, Autocomplete::Node* current) const{
    if(maxHits == numFound){
        return;
    }
    if(index == prefix.size()){
        if(current->isWord){
            numFound++;
            results.add(found);
        }
        Vector<string> keys = current->children.keys();
        for(int x = 0; x < keys.size(); x++){
            string nextLetter = keys[x];
            suggestionsForHelper(prefix, maxHits, results, numFound, index, found + nextLetter, current->children[nextLetter]);
        }
    } else{
        string nextLetter = prefix.substr(index,1);
        if(current->children.containsKey(nextLetter)){
            suggestionsForHelper(prefix, maxHits, results, numFound, index + 1, found, current->children[nextLetter]);
        }
    }
}

/* The Autocomplete suggestionsFor calls the recursive suggestionsForHelper function.
 * It returns a Set of strings as the autocomplete results for the specified prefix and under the maxHits limit. */
Set<string> Autocomplete::suggestionsFor(const string& prefix, int maxHits) const {
    Set<string> results;
    int numFound = 0;
    suggestionsForHelper(prefix,maxHits,results,numFound,0,prefix,root);
    return results;
}
