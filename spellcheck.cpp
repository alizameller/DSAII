#include "hash.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/* Prompts: 
Enter name of dictionary: 
Total time (in seconds) to load dictionary: 

Enter name of input file: 

Enter name of output file: 
Total time (in seconds) to check document: 
*/

// traverse dictionary file one word at a time
// insert each word into hash table (dictionary)

// traverse input file one word at a time
// for each word, check if hash table contains word
//      if yes, print message in output file
//      if not, print message in output file
// go to next word
hashTable read (ifstream dictFile) {
    string word;
    hashTable dictionary; 
    while (getline(dictFile, word)) { 
        dictionary.insert(word); 
    }
    return dictionary; 
}


int main() {
    ifstream dictFile; //read Dictionary
    ifstream inFile; //read inFile
    ofstream outFile; //write outFile

    string dictFileName; 
    string inputFileName;
    string outputFileName;

    cout << "Enter name of dictionary file: ";
    cin >> dictFileName;
    dictFile.open(dictFileName);
    clock_t read1 = clock();
    read(ifstream dictFile); 
    clock_t read2 = clock();
    double readTimeDiff = ((double) (read2 - read1)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to load dictionary: " << readTimeDiff << "\n";

    cout << "Enter name of input file: ";
    cin >> inputFileName;
    inFile.open(inputFileName);

    cout << "Enter name of output file: ";
    cin >> outputFileName;
    outFile.open(outputFileName);
    clock_t check1 = clock();
    // check dictionary
    clock_t check2 = clock();
    double checkTimeDiff = ((double) (check2 - check1)) / CLOCKS_PER_SEC;

    cout << "Total time (in seconds) to check document: " << checkTimeDiff << "\n";
}