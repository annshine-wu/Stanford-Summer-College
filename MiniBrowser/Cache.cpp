/*
Justin Lee, Annshine Wu
Cache Assignment:
This program uses a hashmap and doubly linked list to store recent pages and their data, so that the user does
not need to download pages they have already visited when they visit them again.
*/
#define CacheCPP_Included
#include "Cache.h"
#include "hashmap.h"

using namespace std;

//This is the constructor function. It initializes the back and recent pointers, and the max variable.
template <typename ValueType>
Cache<ValueType>::Cache(int maxSize) {
    back = new Node();
    recent = back;
    max = maxSize;
}

//This is the destructor function. It uses a while loop to iterate through each element in the linked list
//and deletes them.
template <typename ValueType>
Cache<ValueType>::~Cache() {
    Node* current = back;
    Node* nextrecent;
    while(current != nullptr){
        nextrecent = current->next;
        delete current;
        current = nextrecent;
    }
}

//This function adds a new page to the cache. The function first checks if the key is already in the cache; if
//it is not, it then proceeds to connect the new page with the rest of the cache linked list. If the cache is
//already at its max capacity, the back pointer is deleted and the new page is added to the front.
template <typename ValueType>
void Cache<ValueType>::put(const std::string& key, const ValueType& value) {
    if(!map.containsKey(key)){
        if(map.size() == 0){
            back->value = value;
            back->key = key;
            map.put(key, back);
        }
        else if(map.size() == max){
            map.remove(back->key);
            back = back->next;
            delete back->prev;
            back->prev = nullptr;
            recent->next = new Node();
            recent->next->key = key;
            recent->next->value = value;
            recent->next->prev = recent;
            recent = recent->next;
            map.put(key, recent);
        }
        else{
            recent->next = new Node();
            recent->next->key = key;
            recent->next->value = value;
            recent->next->prev = recent;
            recent = recent->next;
            map.put(key, recent);
        }
    } else{
        get(key);
    }
}

//This function checks if the hashmap/cache contains the key. It returns true if its contained, and false
//if it is not.
template <typename ValueType>
bool Cache<ValueType>::containsKey(const std::string& key) {
    return map.containsKey(key);
}

//This function retrieves the article from the cache. The function takes in one parameter, which is the string key
//which can be matched to a key in the hashmap. The function returns the value assigned to the key in the hashmap,
//which is the article.
template <typename ValueType>
ValueType Cache<ValueType>::get(const std::string& key) {
    if(!map.containsKey(key)){
        error("No such article!");
    }
    Node *temp = map[key];
    if(recent != temp){
        if(!(back == temp)){
            temp->prev->next = temp->next;
        }else{
            back = temp->next;
        }
        recent->next = temp;
        temp->prev = recent;
        temp->next = nullptr;
        recent = temp;
    }
    return recent->value;
}

//This function is used in the tests to return the front article.
template <typename ValueType>
ValueType Cache<ValueType>::returnFront(){
    Node* current = back;
    while(true){
        if(current != nullptr)
            return current->prev->value;
        current = current->next;
    }
}

//This function is used in the tests to return the current size of the hashmap/cache.
template <typename ValueType>
int Cache<ValueType>::getSize(){
    return map.size();
}
