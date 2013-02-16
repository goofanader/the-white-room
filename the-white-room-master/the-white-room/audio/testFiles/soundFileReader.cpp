#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

//let C++ hold our hands and essentially cut the string for us...
//C++ coders don't have to deal with char ** or even char *** for
//tokenizing....makes me sad. Though, the code is a lot cleaner
vector<string> tokenize(const string &str, const string &delim) {
    vector<string> tokens;
    size_t p0 = 0, p1 = string::npos;

    while(p0 != string::npos) {
        //set p1 to the offset of the first occurence of the 
        //delim pattern in str, starting from offset p0
        p1 = str.find_first_of(delim, p0);
        if (p1 != p0) {
            //create a string from p0 to p1
            string token = str.substr(p0, p1-p0);
            tokens.push_back(token);
        }

        //set p0 to the offset of the first character not in a 
        //series of delim patterns
        p0 = str.find_first_not_of(delim, p1);
    }

    return tokens;
}


int main(int argc, char *argv[]) {
    ifstream soundFile;
    string in;
    soundFile.open("sounds.txt");

    if (soundFile.is_open()) {
        while (soundFile.good()) {
            vector<string> tokens;
            getline(soundFile, in);
            if (in != "") {
                tokens = tokenize(in, ":");
                cout << tokens[0] << endl << tokens[1] << endl;
            }
        }

        soundFile.close();
    }

    return 0;
}
