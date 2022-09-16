#include "hash.h"
#include <iostream>
#include <string>
#include <list>

using namespace std;

//hashTable constructor
hashTable::hashTable(int size){
    capacity = getPrimes(size); 
    filled = 0;
    vector<hashItem> data = []; //idk wtf this is supposed to be
}

// find position
int hashTable::findPos(const string &key){
    int currentPos = hash(key); //this is an index value
    while (currentPos < capacity){ 
        if (data[currentPos].isDeleted){ // slot is lazily deleted
            currentPos++;
            continue;
        } else if (!data[currentPos].isOccupied) { // not deleted, not occupied
            return -1;
        } else if (data[currentPos].key == key) { // key being checked is same as key at currentPos
            return currentPos; 
        }   
        currentPos++;
        if (currentPos == capacity){
            currentPos = 0;
        }
    }
}

// check if hashTable contains key
bool hashTable::contains(const string &key){
    if (findPos(&key) == -1) { // key was not found (i.e. not in table)
        return false;
    } else {
        return true;
    }
}

// function to get the next prime value for re-hashing
unsigned int hashTable::getPrime(int size){
    int primes[7] = {50021, 100153, 200363, 400853, 801811, 1604021, 3210703}; 
    for (int i = 0; i < 7; i++) { 
        if (primes[i] > 2 * size) {
            return primes[i]; 
        }
    }
}

// Hash function to calculate hash for a value
int hashTable::hash(const string &key){
}

bool hashTable::rehash(){ //why are there no input paramters
    capacity = getPrime(capacity); // put the *2 here or in the getPrime function?
}

// inserting into hashTable
int hashTable::insert(const string &key, void *pv){
    if (contains(&key) == false) { //if slot is empty
        hashTable::hashItem.isOccupied = false;
        // check if lazily deleted?
        if (filled >= capacity / 2) { // check if filled >= capacity/2 and if so, call re-hash
            rehash();
            insert(key, pv);
        } else {
            pv = hash(key); 
        // insert using key, pv and pushBack function?
            return 0;
        }
    } else { //if slot is full
        hashTable::hashItem.isOccupied = true;
        // linear probing to find next slot
        if (filled >= capacity / 2) { // check if filled >= capacity/2 and if so, call re-hash
            rehash();
            insert(key, pv);
        } else {
            return 1;
        }
    }
    // if insert fails (do I need this?)
    return 2; 
}
