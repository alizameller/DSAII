#ifndef _DIJKSTRAS_H
#define _DIJKSTRAS_H

#include <vector>
#include <string>
#include <iostream>
#include <list>
#include <utility> 
#include "heap.h"
using namespace std;

class Graph {

    public:
        Graph() {
            size = 0;
        }

        void buildGraph(ifstream *infile);
        //void printGraph(); FOR DEBUGGING PURPOSES ONLY
        void dijkstras(string sourceId);
        void outputGraph(ofstream *outfile); 
        bool graphContains(string id); 
        

    private:
        class Node { // An inner class within heap
            public:
                string id; 
                list< pair<Node*, int> > edges; //adjacency list, int = weight
                int index;
        };

        vector<Node*> nodes; 
        hashTable nodeVertex; // maps nodes to vertices
        int size; 

        vector<int> distances;
        vector<Node*> prevs; 

        // Should insert the edge FROM node with id1 TO node2 with id2
        // into the graph, associating it with the number weight.
        void insertEdge(string id1, string id2, int weight);
        
        string printPath(Node *end);
};

#endif //_DIJKSTRAS_H