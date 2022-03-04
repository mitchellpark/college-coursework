/*
 * Author: Mitchell Park
 * Program 2 
 */
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

/*
 * Precondition: str is a string of size 10
 * Postcondition: str is reversed
 */
string reverse(string str){
    int len = str.length();
    for(int i=0;i<len/2;i++){
        swap(str[i], str[len-1-i]);
    }
    return str;

}

int main(){
    string input;
    string reversed;

    cout<< "Input String of 10 digits (no spaces)" <<endl;
    cin >> input;

    while(input.size()!=10){            //Prompt the user to retry until the input size is 10.
        cout<<"Enter an input string of length 10." << endl;
        cin >> input;
    }
    reversed = reverse(input);
    cout << "\n";

    //"reversed" now holds the reversed input, so we can now print the data using setw();
    for(int i = 0; i < 5; i++) {
        //cout << setw(15);
        cout << setw(12 + i) << right <<input << setw(18) << right << reversed << endl;      

    }

    return 0;
}
