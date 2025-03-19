// created by Jacob Luytjes, David Gonzalez, Abraham Hernandez,
// David Llamas, Ethan Gallenbach, Jafet Isidoro.

#include "LexAnalyzer.h"
#include <iostream>
#include <map>
#include <vector>
#include <string>

using namespace std;

// Constructor: Reads token-lexeme pairs from input file
LexAnalyzer::LexAnalyzer(istream& infile) {
    string wordPair;
    while (getline(infile, wordPair)) {
        size_t pos = wordPair.find(" ");
        string token = wordPair.substr(0, pos);
        string lex = wordPair.substr(pos + 1);
        tokenmap.insert(make_pair(lex, token));
        lexemes.push_back(lex);
        tokens.push_back(token);
    }
}

// Checks if a lexeme is surrounded by valid characters or lexemes
bool LexAnalyzer::validChecker(int start, int end, const string& lineOfCode) {
    bool lValid = false;
    bool rValid = false;
    auto it = tokenmap.begin();

    if (start < 1 || lineOfCode[start - 1] == ' ') {
        lValid = true;
    }
    if (end + 1 >= lineOfCode.size() || lineOfCode[end + 1] == ' ') {
        rValid = true;
    }

    while (it != tokenmap.end() && !(lValid && rValid)) {
        if (it->second[0] == 's') {
            if (!lValid && start >= it->first.size()) {
                if (it->first == lineOfCode.substr(start - it->first.size(), it->first.size())) {
                    lValid = true;
                }
            }
            if (!rValid && end + 1 + it->first.size() <= lineOfCode.size()) {
                if (it->first == lineOfCode.substr(end + 1, it->first.size())) {
                    rValid = true;
                }
            }
        }
        ++it;
    }
    return (lValid && rValid);
}

// Scans the input file and processes each line
void LexAnalyzer::scanFile(istream& infile, ostream& outfile) {
    string lineOfCode;
    bool error = false;

    while (getline(infile, lineOfCode) && !error) {
        for (size_t i = 0; i < lineOfCode.size(); ++i) {
            if (lineOfCode[i] != ' ') {
                if (isdigit(lineOfCode[i])) {
                    processNumber(i, lineOfCode, outfile, error);
                }
                else if (lineOfCode[i] == '"') {
                    processString(i, lineOfCode, outfile, error);
                }
                else {
                    processKeywordOrIdentifier(i, lineOfCode, outfile, error);
                }
            }

        }
    }
}

// PRIVATE: Function to process numbers
void LexAnalyzer::processNumber(size_t& i, const string& lineOfCode, ostream& outfile, bool& error) {
    size_t number = 1;
    while (i + number < lineOfCode.size() && isdigit(lineOfCode[i + number])) {
        ++number;
    }

    if (validChecker(i, i + number - 1, lineOfCode)) {
        outfile << "t_number : " << lineOfCode.substr(i, number) << endl;
        i += number - 1;
    }
    else {
        cout << "Error in number" << endl;
        outfile << "Error in number" << endl;
        error = true;
        i = lineOfCode.size();
    }
}

// PRIVATE: Function to process string literals
void LexAnalyzer::processString(size_t& i, const string& lineOfCode, ostream& outfile, bool& error) {
    size_t number = 1;
    while (i + number < lineOfCode.size() && lineOfCode[i + number] != '"') {
        ++number;
    }

    if (i + number >= lineOfCode.size() || !validChecker(i, i + number, lineOfCode)) {
        cout << "Error in string" << endl;
        outfile << "Error in string" << endl;
        error = true;
        i = lineOfCode.size();
    }
    else {
        outfile << "t_text : " << lineOfCode.substr(i + 1, number - 1) << endl;
    }

    i += number;
}

// PRIVATE: Function to process keywords and identifiers
void LexAnalyzer::processKeywordOrIdentifier(size_t& i, const string& lineOfCode, ostream& outfile, bool& error) {
    auto it = tokenmap.rbegin();
    bool found = false;

    while (it != tokenmap.rend() && !found) {
        if (it->first.size() <= lineOfCode.size() - i) {
            if (it->first == lineOfCode.substr(i, it->first.size())) {
                if (validChecker(i, i + it->first.size()-1, lineOfCode)) {
                    outfile << it->second << " : " << it->first << endl;
                    found = true;
                    i += it->first.size() - 1;
                }
                else {
                    if (it->second[0] != 't') {
                        outfile << it->second << " : " << it->first << endl;
                        found = true;
                        i += it->first.size() - 1;
                    }
                }
            }
        }
        ++it;
    }

    if (!found) {
        processIdentifier(i, lineOfCode, outfile, error, found);
    }
}

// PRIVATE: Function to process identifiers (variable names, function names)
void LexAnalyzer::processIdentifier(size_t& i, const string& lineOfCode, ostream& outfile, bool& error, bool& found) {
    if (isalpha(lineOfCode[i])) {
        size_t number = 1;
        while (!found) {
            auto it = tokenmap.rbegin();
            while (it != tokenmap.rend() && !found) {
                if (it->first.size() <= 1) {
                    if (i + number < lineOfCode.size() &&
                        (lineOfCode[i + number] == ' ' || it->first == lineOfCode.substr(i + number, 1))) {
                        outfile << "t_id : " << lineOfCode.substr(i, number) << endl;
                        found = true;
                        i += number - 1;
                    }
                }
                ++it;
            }
            number++;
        }
    }
    else {
        cout << "Error in id" << endl;
        outfile << "Error in id" << endl;
        error = true;
        i = lineOfCode.size();
    }
}
