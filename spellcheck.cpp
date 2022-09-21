#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

bool isValidChar(char c){
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '\'' || 
            c == '-' || (c >= '0' && c <= '9');
}

hashTable makeDict(string dictFileName) {
    ifstream dictFile; 
    dictFile.open(dictFileName);

    string word;
    hashTable dictionary = hashTable(); 

    while (getline(dictFile, word)) { 
        for(int i = 0; i < sizeof word; i++) { 
            if(word[i] >= 'A' && word[i] <= 'Z') {
                word[i] = word[i] + 32;
            }
        }
        dictionary.insert(word); 
    }

    dictFile.close();
    return dictionary; 
}

void checkFile(string inFileName, string outFileName, hashTable dictionary) {
    ifstream inFile; //read inFile
    ofstream outFile; //write outFile
    inFile.open(inFileName, ios::in);
    outFile.open(outFileName, ios::out);

    string line; 
    
    string::iterator it;
    int lineNum = 0;
    int offset; 
    int firstPrint = 1;
    int hasDigit;
    // consider multiple invalid characters in a row (ex: "hello????adin")
    while(getline(inFile, line)) { 
        lineNum++; 
        offset = 0;
        hasDigit = 0;

        for (it = line.begin(); it != line.end(); it++) {
            //check if character is valid 
            if (isValidChar(*it)) {
                    if(*it >= 'A' && *it <= 'Z') {
                        *it = *it + 32;
                    } else if (*it >= '0' && *it <= '9') {
                        hasDigit = 1;
                    }

                    if (it - (line.begin() + offset) == 20) {
                        if (firstPrint) {
                            outFile << "Long word at line " << lineNum << ", starts: " << string(line.begin() + offset, it); 
                            firstPrint = 0;
                        } else {
                            outFile << endl << "Long word at line " << lineNum << ", starts: " << string(line.begin() + offset, it); 
                        }
                    }
                continue;

            } else if (!hasDigit && (string(line.begin() + offset, it) != "") && it - (line.begin() + offset) <= 20 && 
                        !dictionary.contains(string(line.begin() + offset, it))) {
                if (firstPrint) {
                    outFile << "Unknown word at line " << lineNum << ": " << string(line.begin() + offset, it); 
                    firstPrint = 0;
                } else {
                    outFile << endl << "Unknown word at line " << lineNum << ": " << string(line.begin() + offset, it);
                } 
            }

            offset = it + 1 - line.begin(); 
            hasDigit = 0;
        }

        if (!hasDigit && (string(line.begin() + offset, it) != "") && it - (line.begin() + offset) <= 20 && 
            !dictionary.contains(string(line.begin() + offset, it))) {
            if (firstPrint) {
                outFile << "Unknown word at line " << lineNum << ": " << string(line.begin() + offset, it); 
                firstPrint = 0;
            } else {
                outFile << endl << "Unknown word at line " << lineNum << ": " << string(line.begin() + offset, it);
            }
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