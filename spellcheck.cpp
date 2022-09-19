#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

hashTable makeDict(string dictFileName) {
    ifstream dictFile; 
    dictFile.open(dictFileName);

    string word;
    hashTable dictionary = hashTable(); 

    while (getline(dictFile, word)) { 
        dictionary.insert(word); 
    }

    dictFile.close();
    return dictionary; 
}

void checkFile(string inFileName, string outFileName, hashTable dictionary) {
    ifstream inFile; //read inFile
    ofstream outFile; //write outFile
    inFile.open(inFileName);
    outFile.open(outFileName);

    string line; 
    string::iterator it;
    int lineNum = 0;
    // consider multiple invalid characters in a row (ex: "hello????adin")
    while(getline(inFile, line)) { 
        lineNum++; 

        for (it = line.begin(); it != line.end(); it++) {
            //check if character is valid 
            if ((*it >= 'a' && *it <= 'z') || (*it >= 'A' && *it <= 'Z') || *it == '\'' || 
                 *it == '-' || (*it >= '0' && *it <= '9')) {
                    //check if counter == 20
                    if (it - line.begin() == 20) {
                        outFile << "Long word at line" << lineNum << ", starts: " << string(line.begin(), it) << "\n"; 
                    }
                continue;
            } else if (it - line.begin() < 20 && !dictionary.contains(string(line.begin(), it))) {
                outFile << "Unknown word at line" << lineNum << ": " << string(line.begin(), it) << "\n"; 
            }
            //adjust line so that line.begin() starts at the beginning of 
            line = string(it + 1, line.end()); 
        }
    }

    inFile.close();
    outFile.close();
}

int main() {
    string dictFileName; 
    string inputFileName;
    string outputFileName;

    cout << "Enter name of dictionary file: ";
    cin >> dictFileName;
    
    clock_t read1 = clock();
    hashTable dictionary = makeDict(dictFileName); 
    clock_t read2 = clock();
    double readTimeDiff = ((double) (read2 - read1)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to load dictionary: " << readTimeDiff << "\n";

    cout << "Enter name of input file: ";
    cin >> inputFileName;

    cout << "Enter name of output file: ";
    cin >> outputFileName;

    clock_t check1 = clock();
    checkFile(inputFileName, outputFileName, dictionary); 
    clock_t check2 = clock();
    double checkTimeDiff = ((double) (check2 - check1)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to check document: " << checkTimeDiff << "\n";
}