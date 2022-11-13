#include "dijkstras.h"
#include <fstream>
#include <sstream>

using namespace std; 

void Graph::insertEdge(string id1, string id2, int weight) {
    Node *p1;
    if (!nodeVertex.contains(id1)) { // we have not yet encountered id1
        p1 = new Node(); 
        if (int var = nodeVertex.insert(id1, p1) == 1) {
            cerr << "Error: " << id1 << "is already in Hash Table\n"; //should not get here
        } else if (var == 2) {
            cerr << "Error: rehash failed when trying to insert" << id1; 
        }
        nodes.push_back(p1); 
        p1->index = size++; 
        p1->id = id1;
    } else {
        p1 = (Node*) nodeVertex.getPointer(id1); 
    }
    Node *p2;
    if (!nodeVertex.contains(id2)) { // we have not yet encountered id2 
        p2 = new Node(); 
        if (int var2 = nodeVertex.insert(id2, p2) == 1) {
            cerr << "Error: " << id2 << "is already in Hash Table\n"; //should not get here
        } else if (var2 == 2) {
            cerr << "Error: rehash failed when trying to insert" << id2; 
        }
        nodes.push_back(p2); 
        p2->index = size++; 
        p2->id = id2; 
    } else {
        p2 = (Node*) nodeVertex.getPointer(id2); 
    }
    pair<Node*, int> edge (p2, weight); 
    p1->edges.push_back(edge);
}

void Graph::buildGraph(ifstream *infile) {
    string line; 
    string id1, id2;
    int weight;
    for (line; getline(*infile, line);) {
        istringstream iss(line);
        if (!(iss >> id1 >> id2 >> weight)) { 
            cout << "test\n";
            break; // error ?
        }
        insertEdge(id1, id2, weight);
    }
}

void Graph::printGraph() {
    list<Node*>::iterator it;
    list< pair<Node*, int> >::iterator i; 
    
    for (it = nodes.begin(); it != nodes.end(); it++) {
        cout << "Node: " << (*it)->id << " Adjacency List: \n";    
        for (i = (*it)->edges.begin(); i != (*it)->edges.end(); i++) {
            cout << "\tDest: " << (*i).first->id << " Weight: " << (*i).second << endl; 
        }
    }
}

void Graph::dijkstras(string sourceId) {
    heap dijkstra(size); 
    distances.resize(size);
    prevs.resize(size);
/* 
    for each vertex v in G
        dv ← ∞
        knownv ← FALSE
    ds ← 0
    ps ← NULL
    while there are still unknown vertices
        v ← the unknown vertex with the
            smallest d-value
        knownv ← TRUE
        for each edge from v to vertex w
            if dv + cv,w < dw
                dw ← dv + cv,w
                pw ← v
*/
}

int main () {
    string filename;
    Graph graph;

    cout << "Enter the name of a file specifying the graph: ";
    cin >> filename;
    ifstream infile(filename);
    
    graph.buildGraph(&infile);
    graph.printGraph(); 
}
