#include "dijkstras.h"
#include <fstream>
#include <sstream>
#include <ctime>

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
            break; // error 
        }
        insertEdge(id1, id2, weight);
    }
}

/* FOR DEBUGGING PURPOSES
void Graph::printGraph() {
    vector<Node*>::iterator it;
    list< pair<Node*, int> >::iterator i; 
    
    for (it = nodes.begin(); it != nodes.end(); it++) {
        cout << "Node: " << (*it)->id << " Adjacency List: \n";    
        for (i = (*it)->edges.begin(); i != (*it)->edges.end(); i++) {
            cout << "\tDest: " << (*i).first->id << " Weight: " << (*i).second << endl; 
        }
    }
} */

void Graph::dijkstras(string sourceId) {
    heap unknowns(size); 
    distances.resize(size, INT_MAX);
    prevs.resize(size);

    vector<Node*>::iterator it;

    for (it = nodes.begin(); it != nodes.end(); it++) { //for each vertex v in G
        unknowns.insert((*it)->id, INT_MAX, NULL); // dv ← ∞
    }

    unknowns.setKey(sourceId, 0); // ds ← 0
    unknowns.setPointer(sourceId, (Node *)nodeVertex.getPointer(sourceId)); // ps ← source (to follow output format guidelines)

    string vId;
    Node *vNode;
    int vKey; 
    Node *pvPrevs; 
    list< pair<Node*, int> >::iterator i; 

    while (!unknowns.deleteMin(&vId, &vKey, (void *) &pvPrevs)) { // while there are still unknown vertices (while heap is empty)
        vNode = (Node *)nodeVertex.getPointer(vId);
        distances[vNode->index] = vKey; // assign determined shortest distance to corresponding index in distances
        prevs[vNode->index] = pvPrevs; // assign pointer to prev. node to corresponding index in prevs

        for (i = vNode->edges.begin(); i != vNode->edges.end(); i++) { // for each edge from v to vertex w (iterate through adjacency list)
            if (!unknowns.heapContains((*i).first->id) || vKey == INT_MAX) {
                continue;
            } else if (vKey + (*i).second < unknowns.getKey((*i).first->id)) { // if dv + cv,w < dw
                unknowns.setKey((*i).first->id, vKey + (*i).second); // dw ← dv + cv,w
                unknowns.setPointer((*i).first->id, vNode); // pw ← v
            }
        }
    }
}

bool Graph::graphContains(string id) {
    return nodeVertex.contains(id);
}

string Graph::printPath(Node *end) {
    string path = "]"; 
    int i = end->index;
    Node *curr = end;
    
    while (prevs[i] != curr) {
        path = ", " + curr->id + path; 
        curr = prevs[i];
        i = curr->index;
    }
    path = "[" + curr->id + path; 
    return path;
}

void Graph::outputGraph(ofstream *outFile) {
    vector<Node*>::iterator it;
    for (it = nodes.begin(); it != nodes.end(); it++) {
        *outFile << (*it)->id << ": "; 
        cout << distances[(*it)->index] << endl;
        if (distances[(*it)->index] == INT_MAX) {
            *outFile << "NO PATH" << endl; 
        } else {
            *outFile << distances[(*it)->index] << " " << printPath(*it) << endl;
        }
    }
}

int main () {
    string inFilename;
    string outFilename;
    Graph graph;
    string startingVertex;

    cout << "Enter name of graph file: ";
    cin >> inFilename;
    ifstream infile(inFilename);
    graph.buildGraph(&infile);

    do { 
        cout << "Enter name of starting vertex: "; 
        cin >> startingVertex;
    } while (!graph.graphContains(startingVertex));

    clock_t t1 = clock();
    graph.dijkstras(startingVertex); 
    clock_t t2 = clock();
    double timeDiff = ((double) (t2 - t1)) / CLOCKS_PER_SEC;
    cout << "Total time (in seconds) to apply Dijkstra's algorithm: " << timeDiff << endl;

    cout << "Enter name of output file: ";
    cin >> outFilename;
    ofstream outfile(outFilename);
    graph.outputGraph(&outfile);
}
