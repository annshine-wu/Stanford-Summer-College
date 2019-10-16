/*
Justin Lee, Annshine Wu
History Assignment:
This program manages how the user can go backwards and forwards between pages. It uses a doubly linked list to
access previous and next pages.
*/
#include "History.h"
#include "error.h"
using namespace std;

//This is the constructor function. It initializes the back pointer and current pointer.
History::History() {
    back = new Node();
    curr = back;
    numPages = 0;
}

//This is the the destructor function. It uses a while loop to iterate through each element in the linked list
//and deletes each element until the end has been reached.
History::~History() {
    Node* current = back;
    Node* nextPage;
    while(current != nullptr){
        nextPage = current->next;
        delete current;
        current = nextPage;
    }
}

//This function checks if the current page has a next page. It returns a boolean value, true if there is a next
//page or false if there is no next page.
bool History::hasNext() const {
    if(curr->next == nullptr){
        return false;
    }
    return true;
}

//This function checks if the current page has a previous page. It returns a boolean value, true if there is a previous
//page or false if there is no previous page.
bool History::hasPrevious() const {
    if(curr->prev == nullptr){
        return false;
    }
    return true;
}

//This function changes the current pointer to point to the next page. It then returns a string that represents
//the title of the article. If there is no next page, the program throws an error.
string History::next() {
    if(curr->next == nullptr){
        error("There is no next page!");
    }
    curr = curr->next;
    return curr->title;
}

//This function changes the current pointer to point to the previous page. It then returns a string that represents
//the title of the article. If there is no previous page, the program throws an error.
string History::previous() {
    if(curr->prev == nullptr){
        error("There is no previous page!");
    }
    curr = curr->prev;
    return curr->title;
}

//This function adds a new page to the history. It first uses a while loop similar to the one used in the destructor
//to delete each element after the current page. The function then adds the new page to the front of the history,
//connecting it to the rest of the linked list and sets current pointer to the new page.
void History::goTo(const string& page) {
    Node* nextPage;
    Node* current = curr->next;
    while(current != nullptr){
        nextPage = current->next;
        delete current;
        numPages --;
        current = nextPage;
    }
    if(numPages == 0){
        back->title = page;
        curr = back;
        numPages ++;
    }else{
        curr->next = new Node();
        curr->next->prev = curr;
        curr = curr->next;
        curr->title = page;
        numPages ++;
    }
}
