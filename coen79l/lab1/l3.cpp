/*
 * Author: Mitchell Park
 * Program 3
 */

#include <iostream> 
#include <fstream>
#include <string>
#include <vector>
using namespace std;

string capitalized(string str);
vector<string> readStrFromFile(string);
vector<string> getOutput(vector<string>);


int main( int argc , char **argv){

    //If file argument is empty, remind user to enter one
    while(argv[1]==nullptr) {
        cout << "Please provide a file name" << endl;
        exit(1);
    }

    vector<string> lines = readStrFromFile(argv[1]);    //lines represents the file lines
    vector<string> output = getOutput(lines);       //the output is the final capitalized and simplified version
    for(int i=0; i<output.size(); i++){
        cout << output.at(i) << endl;
    }
}

/*
 * Receives a file name and returns a vector of strings that represent the file and its lines
 */
vector<string> readStrFromFile(string fn){
    string fileName = string(fn);
    ifstream src;

    src.open(fileName);
    if(!src.is_open()){         //If the given file name doesn't work, notify the user and exit the program.
        cout<<"Couldn't open the file. Please try again."<<endl;
        exit(1);
    }

    vector<string> lines;
    string line;
    //At the end of this loop, lines should be a vector of the file's lines, numeric values excluded.
    while (getline(src, line)){    
        string str = "";
        for(int i=0; i<line.length(); i++){
            if(isalpha(line.at(i)) || line.at(i)==' ') {
                str+=line.at(i);
            }
        } 
        lines.push_back(str);
    }
    return lines;
}

/*
 * Receives a vector of the file's lines with non-numeric characters, and returns the cpiatlized versions
 * of words whose size is greater than or equal to 10.
 */
vector<string> getOutput(vector<string> lines){
    vector<string> output;

    for(int i=0; i<lines.size(); i++){
        string line = lines.at(i);
        string s;       //only holds current word, and is updated as we traverse the line.

        /*
         * s will hold the current word, and when the word ends, we add it to the vector if its size is
         * greater than or equal to 10. 
         */
        for(int i=0; i<line.length(); i++){
            if(line.at(i)==' ' || i==line.length()-1) {     //current word ends
                s+=line.at(i);
                if(s.length()>=10) output.push_back(capitalized(s));    
                s = "";         //s is emptied and ready to hold a new word.
            }else s+=line.at(i);
        }
    }
    return output;
}

/*
 * Receives a string and returns the capitalized version
 */
string capitalized(string str){
    string res;
    for(int i=0; i<str.length(); i++){
        res += toupper(str.at(i));
    }
    return res;
}