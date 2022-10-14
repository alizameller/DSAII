#include "heap.h"
#include "hash.cpp"
#include <iostream>
#include <string>   
#include <list>
#include <vector>

heap::heap(int capacity):mapping(capacity*2) {
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    currentSize = 0;
    capacity = capacity;
}

heap::node::node(){
    id;
    key;
    pData; 
}

int heap::insert(const std::string &id, int key, void *pv = (void *)nullptr) {
    if (this->currentSize == this->capacity) {
        return 1;
    }
    // if a node with the given id already exists
    if (mapping.contains(id)) {
        return 2;
    }
    // insert node into heap (using key)
    int index = this->currentSize + 1;
    data[index].id = id;
    data[index].key = key;
    data[index].pData = pv; 

    percolateUp(index); //new node is in correct place on heap and inserted in hash table

    this->currentSize++; 
}

 /* get pointer to node from id in hashTable mapping
    bool b; 
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    */

int heap::setKey(const std::string &id, int key) {
    //increase key

    //decrease key
}

int heap::deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr) {
    if (pId) {
        *pId = data[1].id;
    }
    if (pKey) {
        *pKey = data[1].key;
    }
    if (ppData) {
       *(static_cast<void **> (ppData)) = data[1].pData;
    }

    data[1] = data[currentSize];
    currentSize --; //remove the last item

    percolateDown(1);
}

int heap::remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr) {

}

void heap::percolateUp(int posCur) {
    node newNode; 

    while(data[posCur].key <= data[posCur/2].key) {

        if (posCur == 1) {
            break; 
        }

        newNode = data[posCur];
        data[posCur] = data[posCur/2]; //push parent node down one level
        data[posCur/2] = newNode; //put new node at location of parent node
        if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
            // key does not exist on hashTable
            // fprintf ERROR
        }
        posCur = posCur/2; 
    }

    if (mapping.insert(newNode.id, (void *) &newNode) == 1) {
        mapping.setPointer(newNode.id, (void *) &newNode); //update pointer of node in hashTable
    } else if (mapping.insert(newNode.id, (void *) &newNode) == 2) {
        // rehash fails
        // fprintf ERROR
    }
}

void heap::percolateDown(int posCur) {
    // while parent is greater than (at least one of) its child(ren)
    node hold; 
    while (data[posCur].key >= data[posCur/2].key || data[posCur].key >= data[posCur/2 + 1].key) {
        if (posCur == currentSize) {
            break; 
        }
        hold = data[posCur];

        // if data[posCur/2].key is valid 
            // check if data[posCur/2 + 1].key is valid
                // if data[posCur/2].key >= data[posCur/2 + 1].key
                    //data[posCur] = data[posCur/2]; //push parent node down one level
                    //data[posCur/2] = hold; //put hold node at location of parent node
        // else
            data[posCur] = data[posCur/2 + 1]; //push parent node down one level
            data[posCur/2 + 1] = hold;

        // else
            // ERROR?
    }
}

int heap::getPos(heap::node *pn) {
    int pos = pn - &data[0];
    return pos;
}
