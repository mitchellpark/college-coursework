/*
 * Author: Mitchell Park
 * Assignment: COEN 12 Lab 1
 */
#include <stdio.h>
#include <stdbool.h> //Library used to declare variables with values "true" and "false" 
#include <ctype.h> //Library used for the isspace() method

#define MAX_WORD_LENGTH 30 //maximum length of a word

void getFileWC(const char* filename);

/*
 * This main method simply calls function getFileWC, which prints a file's word count.
 * The function is supplied the first command line argument.
 */
int main(int argc, char** argv){
	getFileWC(argv[1]);
	return 0;
}

/*
	Method getFileWC that takes in the name of a file, and returns the word count.
*/
void getFileWC(const char* filename){

	int wordCount;
    FILE *file;

	/*
	 * Opens a file with the provided filename (in read-only), and prints an error message 
	 * if the file cannot be accessed.
	 */
	wordCount = 0;
    file = fopen(filename, "r");
    if(file==NULL){
        printf("Please enter a valid argument");
    }else{

		/*
		 * The file can be accessed, so we inspect the file, character by character.
		 */
        bool sawSpace; 		//sawSpace is true if the previous character is a space.
		int wordLen; 		//wordLen counts the length of the current word while parsing.
		char c; 			//c is a variable that represents a character in the getc() stream.

		wordLen = 0;
		sawSpace = true;  	//Initially set to true, to count the first word. 

    	while((c=getc(file))!=EOF){

			/*
			 * If the previous character is a space and the current character 
			 * is not a space, then we increment wordCount.
			 */
        	if(isspace(c)==false && (sawSpace==true)) {
				++wordCount;
			}
			++wordLen; //At each character, word length is incremented.

			/*
			 * sawSpace is true if we detect that the current character is a space,
			 * or we reach the maximum characters seen without seeing a space.
			 */
        	sawSpace = (wordLen==MAX_WORD_LENGTH+1) || isspace(c);

			//At a space, we reset the word length.
			if(sawSpace) {
				wordLen = 0;
			}
    	}
    	
		//File is closed, and the generated word count is printed.
		fclose(file);
    	printf("%d\n", wordCount);
    }
}
