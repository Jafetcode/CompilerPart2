#include <iostream>
#include <fstream>
#include <vector>
#include <map>
using namespace std;

#include "LexAnalyzer.h"

int main() {
    ifstream lexemes("lexemes.txt");
    ifstream source("source.txt");
    ofstream sourcelexemes("sourcelexemes.txt");

    // Ensure all files are successfully opened
    if (!lexemes.is_open() || !source.is_open() || !sourcelexemes.is_open()) {
        cerr << "Error opening file." << endl;
        return 1;
    }

    // Create the LexAnalyzer instance with the lexemes file
    LexAnalyzer lexanalyzer(lexemes);

    // Process the source file and output the token/lexeme pairs
    lexanalyzer.scanFile(source, sourcelexemes);

    cout << "Lexical analysis completed. Token/Lexeme file generated." << endl;

    return 0;
}
