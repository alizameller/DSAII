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

int heap::setKey(const std::string &id, int key) {
    //increase key

    //decrease key
}

int heap::deleteMin(std::string *pId = nullptr, int *pKey = nullptr, void *ppData = nullptr) {
    if (!currentSize) {
        return 1;
    }

    if (pId) {
        *pId = data[1].id;
    }
    if (pKey) {
        *pKey = data[1].key;
    }
    if (ppData) {
       *(static_cast<void **> (ppData)) = data[1].pData;
    }

    if (!mapping.remove(data[1].id)) { //remove this item from hash table
        fprintf(stderr, "Error: Item %s not found in hash table", data[1].id); 
        std::exit(1);
    }

    data[1] = data[currentSize];
    currentSize--; //remove the last item from heap

    percolateDown(1);

    return 0;
}

int heap::remove(const std::string &id, int *pKey = nullptr, void *ppData = nullptr) {
    // if currentSize = 0?

    //get pointer to node from id in hashTable mapping
    bool b; 
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));

    if (pKey) {
        *pKey = pn->key;
    }
    if (ppData) {
       *(static_cast<void **> (ppData)) = pn->pData;
    }
    //why not the id?

    if (!mapping.remove(pn->id)) { //remove this item from hash table
        fprintf(stderr, "Error: Item %s not found in hash table", pn->id); 
        // does this mean node does not exist?
        return 1;
    }

    *pn = data[currentSize];
    currentSize--; //remove the last item from heap

    percolateDown(1); //or start with index of removed node?

    return 0;
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
            fprintf(stderr, "Error: Item %s not found in hash table", data[posCur].id); 
            std::exit(1);
        }
        posCur = posCur/2; 
    }

    if (mapping.insert(newNode.id, (void *) &newNode) == 1) {
        mapping.setPointer(newNode.id, (void *) &newNode); //update pointer of node in hashTable
    } else if (mapping.insert(newNode.id, (void *) &newNode) == 2) {
        // rehash failed
        fprintf(stderr, "Error: rehash failed when trying to insert %s", newNode.id); 
    }
}

void heap::percolateDown(int posCur) {
    node hold; 
    // while parent is greater than (at least one of) its child(ren)
    while (posCur*2 + 1 <= currentSize && 
           (data[posCur].key >= data[posCur*2].key || data[posCur].key >= data[posCur*2 + 1].key)) {
            // inside while loop we can assume both children exist
        hold = data[posCur];

        if (data[posCur*2].key >= data[posCur*2 + 1].key) {
            data[posCur] = data[posCur*2]; // push child node up to parent location
            data[posCur*2] = hold; // put hold node at location of child node
            if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
                // key does not exist on hashTable
                fprintf(stderr, "Error: Item %s not found in hash table", data[posCur].id); 
                std::exit(1);
            }
            posCur = posCur*2;
        } else {
            data[posCur] = data[posCur*2 + 1]; // push child node up to parent location
            data[posCur*2 + 1] = hold; // put hold node at location of child node
            if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
                // key does not exist on hashTable
                fprintf(stderr, "Error: Item %s not found in hash table", data[posCur].id); 
                std::exit(1);
            }
            posCur = posCur*2 + 1;
        }
    }

    if (posCur*2 <= currentSize && data[posCur].key >= data[posCur*2].key) { // we know there is only a left node 
        hold = data[posCur];
        data[posCur] = data[posCur*2]; // push child node up to parent location
        data[posCur*2] = hold; // put hold node at location of child node

        if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
            // key does not exist on hashTable
            fprintf(stderr, "Error: Item %s not found in hash table", data[posCur].id); 
            std::exit(1);
        }
        posCur = posCur*2; 
    }

    if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of node in hashTable
        // key does not exist on hashTable
        fprintf(stderr, "Error: Item %s not found in hash table", data[posCur].id); 
        std::exit(1); 
    }

    return; // no children
}

int heap::getPos(heap::node *pn) {
    int pos = pn - &data[0];
    return pos;
}
