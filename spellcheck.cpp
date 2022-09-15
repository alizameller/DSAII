#include "hash.h"
#include "hash.cpp"
#include <iostream>
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

int main() {
    ifstream dictFile; //read Dictionary
    ifstream inFile; //read inFile
    ofstream outFile; //write outFile

    string dictFileName; 
    string inputFileName;
    string outputFileName;

    cout << "Enter name of dictionary file: ";
    cin >> dictFileName;
    infile.open(dictFileName);
    // time display
    
    cout << "Enter name of input file: ";
    cin >> inputFileName;
    inFile.open(inputFileName);

    cout << "Enter name of output file: ";
    cin >> outputFileName;
    outFile.open(outputFileName);
    // time display
}