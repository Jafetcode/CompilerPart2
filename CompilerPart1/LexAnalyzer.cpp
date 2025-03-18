#include "LexAnalyzer.h"
// pre: parameter refers to open data file consisting of token and
// lexeme pairs i.e.  s_and and t_begin begin t_int 27
// Each pair appears on its own input line.
// post: tokenmap has been populated - key: lexeme, value: token

LexAnalyzer::LexAnalyzer(istream& infile) {
    string wordPair;
    while (getline(infile, wordPair)) {
        unsigned int pos = wordPair.find(" ");
        string token = wordPair.substr(0, pos);
        string lex = wordPair.substr(pos + 1, wordPair.size());
        tokenmap.insert(make_pair(lex, token));
        lexemes.push_back(lex);
        tokens.push_back(token);
    }
}

// pre: 1st parameter refers to an open text file that contains source
// code in the language, 2nd parameter refers to an open empty output
// file
// post: If no error, the token and lexeme pairs for the given input
// file have been written to the output file (token : lexeme).
// If there is an error, the incomplete token/lexeme pairs, as well as
// an error message have been written to the output file.
// A success or fail message has printed to the console.
void LexAnalyzer::scanFile(istream& infile, ostream& outfile) {
    string lineOfCode;
    while (getline(infile, lineOfCode)) {
        for (int i = 0; i < lineOfCode.size(); ++i) {
            if (lineOfCode[i] != ' ') {
                if (lineOfCode[i] >= '0' && lineOfCode[i] <= '9') {
                    int number = 1;
                    while (lineOfCode[i+number] >= '0' && lineOfCode[i+number] <= '9') {
                        ++number;
                    }
                    outfile << "t_number : " << lineOfCode.substr(i, number) << endl;
                    i += number-1;
                }
                else if (lineOfCode[i] == '"') {
                    int number = 1;
                    while (lineOfCode[i+number] != '"') {
                        ++number;
                    }
                    outfile << "t_text : " << lineOfCode.substr(i+1, number-1) << endl;
                    i += number;
                }
                else {
                    map<string, string>::iterator it = tokenmap.begin();
                    bool found = false;
                    while (it != tokenmap.end() && !found) { // fix this later
                        if (it->first.size() <= lineOfCode.size() - i) {
                            //cout << "Test: " << lineOfCode.substr(i, it->first.size()) << endl;
                            if (it->first == lineOfCode.substr(i, it->first.size())) {
                                outfile << it->second << " : " << it->first << endl;
                                found = true;
                                i += it->first.size() - 1;
                            }
                        }
                        ++it;
                    }

                    if (!found) {
                        if (lineOfCode[i] >= 'A' && lineOfCode[i] <= 'Z' || lineOfCode[i] >= 'a' && lineOfCode[i] <= 'z') {
                            cout << "Based: " << lineOfCode.substr(i, 1) << endl;
                        }
                        else {
                            cout << "Cringe: "<< lineOfCode.substr(i, 1) << endl;
                        }

                        int number = 1;
                        while (!found) {
                            it = tokenmap.begin();
                            while (it != tokenmap.end() && !found) {
                                if (it->first.size() <= 1) {
                                    if (lineOfCode.at(i+number) == ' ' || it->first == lineOfCode.substr(i+number, 1)) {
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
                }
            }
        }
    }
}
