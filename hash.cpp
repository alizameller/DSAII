#include "hash.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

// find position
int hashTable::findPos(const string &key){
    // somehow find position of key
}

// check if hashTable contains key
bool hashTable::contains(const string &key){
    if (findPos(&key) == -1) { // key was not found (i.e. not in table)
        return false;
    } else {
        int pos = findPos(&key);
        return true;
    }
}

// function to get the next prime value for re-hashing
unsigned int hashTable::getPrime(int size){
}

// Hash function to calculate hash for a value
int hashTable::hash(const string &key){
}

bool hashTable::rehash(){
    // use getPrime and make new hashTable with size of new prime
}

// inserting into hashTable
int hashTable::insert(const string &key, void *pv){
    if (contains(&key) == false) { //if slot is empty
        hashTable::hashItem.isOccupied = false;
        // check if lazily deleted?
        // check if size >> ___ and if so, call re-hash
        // insert using key, pv and pushBack function?
        return 0;
    } else { //if slot is full
        hashTable::hashItem.isOccupied = true;
        // linear probing to find next slot
        // check if size >> ___ and if so, call re-hash
        return 1;
    }
    // if re-hash fails
    return 2; 
}

// instance of hashTable constructor
hashTable::hashTable(int size){
    size = getPrime(); //to find size
    // allocate space for a list of size "size" 
}
// instance of hashItem constructor
hashTable::hashItem::hashItem(){
}