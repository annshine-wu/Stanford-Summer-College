/* Submitted by: Annshine Wu (annshine), Justin Lee (justin06)
   Assignment: LineManager
     Constructs a binary tree to search for words at a specific Y height and within range of a max and min Y
*/

#include "LineManager.h"
using namespace std;

//This is the recursive helper function for the constructor. It creates the binary tree by finding the middle
//index of the vector given and then using the middle index to build the left and right subtrees recursively.
//There are three parameters, the first being a vector of lines given, and the other two paratmers are the start
//and end indexes which are used to calculate the middle index. The base case is if the start index is greater
//than the end index.
LineManager::Node* LineManager::LineManagerHelper(const Vector<Line *>& lines, int start, int end){
    if(start > end){
        return nullptr;
    }
    int index = (start + end)/2;
    Node* current = new Node();
    current->line = lines[index];
    current->left = LineManagerHelper(lines, start, index-1);
    current->right = LineManagerHelper(lines, index+1, end);
    return current;
}

/* The LineManager constructor calls the recursive LineManagerHelper function*/
LineManager::LineManager(const Vector<Line *>& lines) {
    root = LineManagerHelper(lines,0,lines.size()-1);
}

/* The LineManager destructor calls the recursive deleteTreeHelper function*/
LineManager::~LineManager() {
    deleteTreeHelper(root);
}

//This is the recursive helper function for the destructor. It takes in a single parameter, which is a pointer
//to the node which is used to get its children when the function goes to its recursive case. The base case is
//the node passed in is empty.
void LineManager::deleteTreeHelper(Node *currentNode){
    if (currentNode == nullptr)
        return;
    deleteTreeHelper(currentNode->left);
    deleteTreeHelper(currentNode->right);
    delete currentNode->line;
    delete currentNode;
}

/* contentHeightHelper keeps traversing to the tree's right node to find the right most node
*  after reaching the right mode node, it returns that node's line's highY */
double LineManager::contentHeightHelper(LineManager::Node* current) const{
    if(current->right != nullptr){
        return contentHeightHelper(current->right);
    } else{
        return current->line->highY();;
    }
}

/* contentHeight calls the recursive contentHeightHelper function*/
double LineManager::contentHeight() const {
    return contentHeightHelper(root);
}

/* linesInRangeHelper is a recursive helper function
 * base case: current == nullptr --> return
 * recursive case:
 * if the current's line's lowY >= min, calls itself again with current's left
 * if the current's line is in range, it adds the current's line to the range vector
 * if the current's line's higherY <= max, calls itself again with current's right*/
void LineManager::linesInRangeHelper(LineManager::Node* current, double min, double max, Vector<Line *>& range) const{
    if(current == nullptr){
        return;
    }
    if(current->line->lowY() >= min){
        linesInRangeHelper(current->left,min,max,range);
    }
    if(current->line->lowY() <= max && current->line->highY() >= min){
        range.add(current->line);
    }
    if(current->line->highY() <= max){
        linesInRangeHelper(current->right,min,max,range);
    }
}

/* linesInRange calls the recursive linesInRangeHelper function*/
Vector<Line *> LineManager::linesInRange(double lowY, double highY) const {
    Vector<Line *> range;
    linesInRangeHelper(root, lowY, highY, range);
    return range;
}

//This is the recursive helper function for the lineAt wrapper function. It takes two parameters, the first being
//the y-value that is to be contained in the line returned. The second parameter is a pointer to the current node
//being searched at, as the function conducts a binary search through the tree. The base case is if the node
//passed in is empty. The recursive case prevents arms-length recursion by checking if each child subtree line
//is completely out of range. Therefore, unneccessary recursion is prevented.
Line* LineManager::lineAtHelper(double y, Node *current) const {
    if(current == nullptr){
        return nullptr;
    } else{
        if(current->line->lowY() <= y && current->line->highY() >= y){
            return current->line;
        } else{
            if(y < current->line->lowY()){
                return lineAtHelper(y, current->left);
            } else{
                return lineAtHelper(y, current->right);
            }
        }
    }
}

//This function calls the recursive function that returns a pointer to a line.
Line* LineManager::lineAt(double y) const {
    return lineAtHelper(y, root);
}
