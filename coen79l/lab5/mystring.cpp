#include "mystring.h"
#include <cassert>
#include <cstring>

using namespace coen79_lab5;

string::string(const char str[ ])
{
    current_length = strlen(str);
    allocated = current_length;
    characters = new char[allocated];
    strncpy(characters, str, allocated);
    characters[current_length] = '\0';      //null signifies the end of the word
}

string::string(char c)
{
    current_length = 1; 
    allocated = current_length+1;   //Needs one space for the null character

    characters = new char[allocated];
    characters[0] = c;
    characters[1] = '\0';
}  

string::string(const string& source)
{
    current_length = source.current_length;
    allocated = source.current_length + 1;
    characters = new char[allocated];
    strncpy(characters, source.characters, allocated);
}

string::~string( )
{
    allocated = 0;
    current_length = 0;
    delete[] characters;
}

/*
    Appends the addend to the current string, using reserve function to allocate memory.
 */
void string::operator+=(const string& addend)
{
    reserve(current_length + addend.current_length);
    strncat(characters, addend.characters, allocated);
    current_length += addend.current_length;
}

/*
 * Appends the addend to the current string, using reserve function to allocate memory. 
 */
void string::operator+=(const char addend[ ])
{
    reserve(current_length + strlen(addend));
    strncat(characters, addend, allocated);
    current_length += strlen(addend);
}

void string::operator+=(char addend)
{
    reserve(current_length);
    characters[current_length] = addend;
    current_length+=1;
    characters[current_length] = '\0';      //Null isn't there, so we need to add it
}

/*
 * Reserve allocates memory to the specified length, creating
 * a temporary array so that there is no memory leak.
 */
void string::reserve(size_t n)
{
    char *tmp = new char[n+allocated];
    strncpy(tmp, characters, current_length);
    delete[] characters;
    
    characters = tmp;
    allocated += n;
}

/*
 * The characters array is set to a new array where we copy the character array from source.
 *  We use the reserve function so that we allocate sufficient memory.
 */
string& string::operator=(const string& source)
{
    current_length = source.length();
    allocated = current_length;
    characters = new char[allocated];   
    reserve(source.current_length);     //We allocate sufficient memory to add source 
    strncpy(characters, source.characters, allocated);  //Copy the character array over
    characters[current_length] = '\0';      
    return *this;
}

/*
 * inserts a string into a specified index (0-indexed).
 */
void string::insert(const string& source, unsigned int position)
{
    assert(position <= current_length);

    reserve(source.current_length + current_length);
    char buffer[current_length - position];     //buffer's index is at where the word should start inserting
    strncpy(buffer, characters + position, current_length - position);
    strncpy(characters + position + source.current_length, buffer, current_length - position);
    strncpy(characters + position, source.characters, source.current_length);
    current_length += source.current_length;    //length is now the combined length
}

void string::dlt(unsigned int position, unsigned int num)
{
    assert(position + num <= current_length);
    for(int i=position; i<=(current_length-num); i++) {
        characters[i] = characters[i+num];
    }
    characters[current_length]='\0';
    current_length-=num;
}

/* replaces character at the given index*/
void string::replace(char c, unsigned int position)
{
    assert(position<current_length);
    characters[position]=c;
}

/* Replaces chars in characters with the source's characters at a given index */
void string::replace(const string& source, unsigned int position)
{
    assert(position + source.current_length<=current_length);
    strncpy(&characters[position], source.characters, source.current_length);
}

/* Returns the character at the given index*/
char string::operator[ ](size_t position) const
{
    assert(position<current_length);
    return characters[position];
}

/*If the given character is found, the index is returned.*/
int string::search(char c) const{
    for(int i=0; i<current_length; i++) {
        if(characters[i]==c) {
            return i;
        }
    }
    return -1;      //If it's not found, we return -1.
}

/* 
 * Searches for the given string within the characters array.
 * Uses the strstr(), which points to where the substring should start.
 */
int string::search(const string& substring) const{
    char* tmp = strstr(characters, substring.characters);       
        if(tmp!=NULL) {                                           
            return tmp[0]-characters[0];                            
        }
    /*
    for(int i=0; i<(current_length-substring.current_length) + 1; i++) {
        if(strncmp(&characters[i], substring.characters, substring.current_length==0)) {
            return i;
        }
    }*/
    return -1;      //If it's not found, we return -1.
}

/*Returns how many of the given char exists in the characters array.*/
unsigned int string::count(char c) const
{
    int count=0;
    for(int i=0; i<current_length; i++) {
        if(characters[i]==c) count++;
    }
    return count;
}

namespace coen79_lab5
{
    /*Simply printing out the characters array*/
    std::ostream& operator<<(std::ostream& outs, const string& source)
    {
        outs<<source.characters;
        return outs;
    }

    /*returns true if the two strings are equal.*/
    bool operator==(const string& s1, const string& s2)
    {
        return strncmp(s1.characters,s2.characters,s1.current_length)==0;
    }

    /*returns true if the two strings are not equal.*/
    bool operator!=(const string& s1, const string& s2)
    {
        return strncmp(s1.characters,s2.characters,s1.current_length)!=0;
    }

    /*Returns true if s1's length is greater than s2's length.*/
    bool operator>(const string& s1, const string& s2)
    {
        return strncmp(s1.characters,s2.characters,s1.current_length)>0;
    }

    /*returns true is s1's length is less than s2's length.*/
    bool operator<(const string& s1, const string& s2)
    {
        return strncmp(s1.characters,s2.characters,s1.current_length)<0;
    }

    /*returns true is s1's length is greater than or equal to s2's length.*/
    bool operator>=(const string& s1, const string& s2)
    {
        return ((string)s1==(string)s2)  ||  ((string)s1>(string)s2);
    }

    /*Returns true is s1's length is less than or equl to s2's length.*/
    bool operator<=(const string& s1, const string& s2)
    {
        return ((string)s1==(string)s2)  ||  (s1 < s2);
    }
}

/*returns a string that is the sum of the two given strings.*/
string coen79_lab5::operator+(const string& s1, const string& s2)
{
    string tmp(s1);
    tmp+=s2;
    return tmp;
}

/*returns a string that is the sum of the given string and char array.*/
string coen79_lab5::operator+(const string& s1, const char addend[ ])
{
    string tmp(s1);
    tmp+=addend;
    return tmp;
}

/*Receives a string input, with a buffer of 100*/ 
std::istream& coen79_lab5::operator>>(std::istream& ins, string& target)
{
    char buffer[100] = {'\0'};
    ins>>buffer;
    target= string(buffer);
    return ins;
}
