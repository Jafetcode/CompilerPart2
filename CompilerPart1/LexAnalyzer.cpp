
#include "LexAnalyzer.h"
// pre: parameter refers to open data file consisting of token and
// lexeme pairs i.e.  s_and and t_begin begin t_int 27
// Each pair appears on its own input line.
// post: tokenmap has been populated - key: lexeme, value: token

LexAnalyzer::LexAnalyzer(istream& infile) {

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
<<<<<<< Updated upstream

=======
    string lineOfCode;
    while (getline(infile, lineOfCode)) {
        for (int i = 0; i < lineOfCode.size(); ++i) {
            if (lineOfCode[i] != ' ' ) {
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
                        if (i+number >= lineOfCode.size()) {
                            cout << "" << endl;
                        }
                    }
                    outfile << "t_text : " << lineOfCode.substr(i+1, number-1) << endl;
                    i += number;
                }
                else {
                    map<string, string>::iterator it = tokenmap.begin();
                    bool found = false;
                    while (it != tokenmap.end()) {
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

                    int number = 1;
                    while (!found) {
                        if (it->first.size() <= lineOfCode.size() - i) {}
                    }
                }
            }
        }
    }
>>>>>>> Stashed changes
}
