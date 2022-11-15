#include "heap.h"
#include <iostream>

using namespace std; 

heap::heap(int capacity):mapping(capacity*2) {
    // Allocate space for the nodes (0 slot is not used)
    data.resize(capacity+1);
    currentSize = 0;
    this->capacity = capacity;
}

int heap::insert(const std::string &id, int key, void *pv) {
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

    return 0;
}

int heap::setKey(const std::string &id, int key) {
    int posCur; 
    bool b;
    node* pn = static_cast<node *> (mapping.getPointer(id, &b)); 
    if (!b) {
        return 1; 
    }    
    posCur = getPos(pn);

    int tempKey = pn->key;
    pn->key = key;

    if (key < tempKey) { //decrease key 
        percolateUp(posCur); 
    } else { //increase key
        percolateDown(posCur);
    }

    return 0; 
}

int heap::deleteMin(std::string *pId, int *pKey, void *ppData) {
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
        cerr << "Error: Item " << (data[1].id).c_str() << " not found in hash table when performing deleteMin\n"; 
        exit(1);
    }

    data[1] = data[currentSize];
    currentSize--; //remove the last item from heap

    percolateDown(1);

    return 0;
}

int heap::remove(const std::string &id, int *pKey, void *ppData) {
    //get pointer to node from id in hashTable mapping
    bool b; 
    node *pn = static_cast<node *> (mapping.getPointer(id, &b));
    if (!b) {
        return 1; 
    }

    if (pKey) {
        *pKey = pn->key;
    }
    if (ppData) {
       *(static_cast<void **> (ppData)) = pn->pData;
    }

    if (!mapping.remove(pn->id)) { //remove this item from hash table
        cerr << "Error: Item " << (pn->id).c_str() << "not found in hash table when performing remove\n"; 
        exit(1);
    }

    int tempKey = pn->key;
    *pn = data[currentSize];
    currentSize--; //remove the last item from heap

    if (getPos(pn) > currentSize) { //if removing last element in heap
        return 0; 
    }

    if (pn->key < tempKey) { 
        percolateUp(getPos(pn)); 
    } else {
        percolateDown(getPos(pn));
    }

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
            cerr << "Error: Item " << (data[posCur].id).c_str() << " not found in hash table when performing percolateUp\n"; 
            exit(1);
        }
        posCur = posCur/2; 
    }

    if (int var = mapping.insert(data[posCur].id, (void *) &data[posCur]) == 1) {
        mapping.setPointer(data[posCur].id, (void *) &data[posCur]); //update pointer of node in hashTable
    } else if (var == 2) {
        // rehash failed -> we should never get here!
        cerr << "Error: rehash failed when trying to insert " << (data[posCur].id).c_str() << " when performing percolateUp"; 
    }
}

void heap::percolateDown(int posCur) {
    node hold; 
    // while parent is greater than (at least one of) its child(ren)
    while (posCur*2 + 1 <= currentSize && 
           (data[posCur].key >= data[posCur*2].key || data[posCur].key >= data[posCur*2 + 1].key)) {
            // inside while loop we can assume both children exist
        hold = data[posCur];

        if (data[posCur*2].key <= data[posCur*2 + 1].key) {
            data[posCur] = data[posCur*2]; // push child node up to parent location
            data[posCur*2] = hold; // put hold node at location of child node
            if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
                // key does not exist on hashTable
                cerr << "Error: Item " << (data[posCur].id).c_str() << " not found in hash table when performing percolateDown 1\n"; 
                exit(1);
            }
            posCur = posCur*2;
        } else {
            data[posCur] = data[posCur*2 + 1]; // push child node up to parent location
            data[posCur*2 + 1] = hold; // put hold node at location of child node
            if (mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of parent node in hashTable
                // key does not exist on hashTable
                cerr << "Error: Item " << (data[posCur].id).c_str() << " not found in hash table when performing percolateDown 2\n"; 
                exit(1);
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
            cerr << "Error: Item " << (data[posCur].id).c_str() << " not found in hash table when performing percolateDown 3\n"; 
            exit(1);
        }
        posCur = posCur*2; 
    }

    if (currentSize && mapping.setPointer(data[posCur].id, (void *) &data[posCur])) { //update pointer of node in hashTable
        // key does not exist on hashTable
        cerr << "Error: Item " << (data[posCur].id).c_str() << " not found in hash table when performing percolateDown 4\n"; 
        exit(1); 
    }

    return; // no children
}

int heap::getPos(heap::node *pn) {
    int pos = pn - &data[0];
    return pos;
}

int heap::getKey(string &id) {
    node *pn = (node *)mapping.getPointer(id);
    return pn->key;  
}

void heap::setPointer(string &id, void *pv) {
    node *pn = (node *)mapping.getPointer(id);
    pn->pData = pv; 
}

bool heap::heapContains(string id) {
    return mapping.contains(id); 
}
