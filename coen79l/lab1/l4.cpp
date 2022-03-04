/*
 * Author: Mitchell Park
 * Program 4
 */
#include <iostream>
#include <string>
#include <limits>
#include <algorithm>
using namespace std;

int main(){
    int numGuesses = 0;
    string answer;

    cout << "Think of a number from 1 to 20."<<endl << endl;
    int guessArr[20];
    for(int i=0; i<20; i++){
        guessArr[i] = i;
    }
    random_shuffle(begin(guessArr), end(guessArr));

    int ind = 0;
    do{
        cout <<"Is your number " << guessArr[ind] << "? (Y/N)" << endl;
        numGuesses++;
        cin>>answer;

        //If there is an invalid answer, it prompts user for a Y/N answer
        while(cin.fail() || !(answer=="N" || answer=="n" || answer=="no" || answer=="Y" || answer=="y" || answer=="yes")){
            cout << "Please answer in a \"Y\" or \"N\"." <<endl; 
            cin>>answer;
        }
        //If the user answers "yes", break out of the loop and record the number
        if(answer=="y" || answer=="Y" || answer=="yes") {
            cout << "It took " << numGuesses << " guesses." << endl;
            exit(0);
        }
        ind++;
        if(ind>=20) break;
    }while(!(answer=="y" || answer=="Y" || answer=="yes"));
    cout << "You have incorrectly responded \"no\" 20 times."<<endl;
    return 0; 
}
