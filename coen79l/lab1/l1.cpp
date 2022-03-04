/*
 * Author: Mitchell Park
 * Program 1
 */
#include <iostream>
#include <string>
using namespace std;

int main(){
    string s = "";
    int alpha = 0;
    int nonAlpha = 0;

    cout<<"Please input something"<<endl;
    getline(cin, s);           //The whole input is contained in a string.

    //Traverses through the collected input to increment alphaCount and numCount
    for(int i=0; i<s.length(); i++){
        if(s.at(i)!=' '){
            if(isalpha(s.at(i)) || isdigit(s.at(i))) alpha++;
            else nonAlpha++;
        }
    }
    cout << "Found " << alpha << " alphanumeric characters."  <<endl;
    cout << "Found " << nonAlpha << " non-alphanumeric characters." << endl;
}