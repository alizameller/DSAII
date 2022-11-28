#include <iostream>
#include <string>   
#include <list>
#include <vector>
#include <fstream>
#include <sstream>
#include <ctime>
#include <cctype>

using namespace std;

bool matrix[1001][1001] = {0}; 

int main(){
    string infileName;
    string outfileName;
    ifstream input; 
    ofstream output; 

    string A, B, C;
    int sizeA, sizeB, sizeC;
    string outString = "";

    cout << "Enter name of input file: ";
    getline(cin, infileName);
    cout << "Enter name of output file: ";
    getline(cin, outfileName);
    
    input.open(infileName);
    output.open(outfileName); 

    while (getline(input, A)) {
        getline(input, B);
        getline(input, C);

        sizeA = A.length();
        sizeB = B.length();
        sizeC = C.length();

        if (sizeC != sizeA + sizeB) {
            output << "*** NOT A MERGE ***" << endl; 
            continue; 
        }

        for (int i = 0; i <= sizeA; i++) {
            for (int j = 0; j <= sizeB; j++) {
                if (!i && !j) {
                    matrix[0][0] = true; // setting empty string place in matrix to true; 
                } else if (!i) { 
                    matrix[i][j] = matrix[i][j-1] && (C[i+j-1] == B[j-1]);
                } else if (!j) {
                    matrix[i][j] = matrix[i-1][j] && (C[i+j-1] == A[i-1]);
                } else {
                    matrix[i][j] = (matrix[i][j-1] && (C[i+j-1] == B[j-1])) || (matrix[i-1][j] && (C[i+j-1] == A[i-1]));
                }
            }
        }

        /* FOR DEBUGGING USE ONLY */
        
        for (int i = 0; i <= sizeA; i++) {
            for (int j = 0; j <= sizeB; j++) {
                cout << matrix[i][j] << " ";
            }
            cout << endl;
        }

        if (matrix[sizeA][sizeB] == false) {
            output << "*** NOT A MERGE ***"; 
            
        } else {
            int i = sizeA;
            int j = sizeB;
            int it = 1; 

            while ((i && j) || (i && !j) || (!i && j)) {
                if (!i) {
                    outString = C[sizeC-it] + outString;
                    it++, j--; 
                } else if (!j) {
                    outString = (char) toupper (C[sizeC-it]) + outString;
                    it++, i--;
                } else if (matrix[i][j-1]) {
                    outString = C[sizeC-it] + outString;
                    it++, j--; 
                } else {
                    outString = (char) toupper (C[sizeC-it]) + outString;
                    it++, i--; 
                }
            }

            /*
            itA = A.begin();
            for (itC = C.begin(); itC != C.end(); itC++) {
                if (*itC == *itA) {
                    output << (char) toupper(*itC); 
                    itA++;
                    continue;
                } 
                output << *itC; 
            }
            */
        }

        output << outString << endl; 
        outString = "";
    }
}

