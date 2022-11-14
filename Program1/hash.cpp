#include "hash.h"
#include <iostream>
#include <string>   
#include <list>
#include <vector>

using namespace std;

hashTable::hashItem::hashItem() {
    key = "";
    isOccupied = false;
    isDeleted = false;
    pv = nullptr;
} 

//hashTable constructor
hashTable::hashTable(int size){
    capacity = getPrime(size); // this.getPrimes(size) instead?
    filled = 0;
    data = vector<hashItem>(capacity);
}

// find position
int hashTable::findPos(const string &key){
    int currentPos = this->hash(key); //this is an index value

    while (currentPos < capacity){ 
        if (data[currentPos].isDeleted){ // slot is lazily deleted
            currentPos++;
            continue;
        } else if (!data[currentPos].isOccupied) { // not deleted, not occupied
            return -1;
        } else if (data[currentPos].key == key) { // key being checked is same as key at currentPos
            return currentPos;; 
        }   
        currentPos++;
        if (currentPos == capacity){
            currentPos = 0;
        }
    }
    return 0; //this will never trigger (just to suppress warning)
}

// check if hashTable contains key
bool hashTable::contains(const string &key){
    if (this->findPos(key) == -1) { // key was not found (i.e. not in table)
        return false;
    } else {
        return true;
    }
}

void * hashTable::getPointer(const std::string &key, bool *b) {
    int thisPos = findPos(key);
    if (b) {
        *b = !(thisPos == -1); 
    }

    if (thisPos == -1) {
        return nullptr;
    }

    return data[thisPos].pv; 
}

int hashTable::setPointer(const std::string &key, void *pv) {
    int thisPos = findPos(key);
    if (thisPos == -1) {
        return 1;
    } 
    data[thisPos].pv = pv;
    return 0;
}

bool hashTable::remove(const std::string &key) {
    int thisPos = findPos(key);
    if (thisPos == -1) {
        return false;
    }
    data[thisPos].isDeleted = true;

    return true; 
}

// function to get the next prime value for re-hashing
unsigned int hashTable::getPrime(int size){
    int primes[7] = {50021, 100153, 200363, 400853, 801811, 1604021, 3210703}; 
    for (int i = 0; i < 7; i++) { 
        if (primes[i] > 2 * size) {
            return primes[i]; 
        }
    }
    return 0; //this will never trigger (just to suppress warning)
}

// Hash function to calculate hash for a value
unsigned int hashTable::hash(const string &key){
    int seed = 37;
    unsigned int hashVal = 0;

    for (char ch : key) {
        hashVal = (seed * hashVal + ch) % capacity; 
    }

    return hashVal; 
}

bool hashTable::rehash(){
    vector<hashItem> oldData = data;
    capacity = getPrime(capacity);
    filled = 0;
    try {
        data = vector<hashItem>(capacity);
            for (hashItem x : oldData) {
                if (x.isOccupied && !x.isDeleted) {
                    this->insert(x.key, x.pv);
                }
            }
        return true; 
    } catch (const bad_alloc& e){
        return false;
    }
}

// inserting into hashTable
int hashTable::insert(const string &key, void *pv){
    if (this->contains(key)) { //key is in hashTable
        return 1;
    } 

    int insertPos = this->hash(key); 

    while (data[insertPos].isOccupied && !data[insertPos].isDeleted){ // check if pos is occupied
        insertPos++; 

        if (insertPos == capacity){
            insertPos = 0;
        }

    }
    data[insertPos].key = key;
    data[insertPos].isDeleted = false;
    data[insertPos].isOccupied = true;
    data[insertPos].pv = pv;

    filled++;

    if (filled >= capacity/2) {
        if(!this->rehash()) { //if rehash fails
            return 2; 
        } 
    }

    return 0;
}
