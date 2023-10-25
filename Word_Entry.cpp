/*
Author: Sreeram Kondapalli
Date: 11/24/2022
Description: The goal will be to parse a large text file and determine the word frequency of
every word in the text file.
*/
#include "Word_Entry.h"
#include <iostream>
#include <string>

using namespace std;

//Word Entry default constructor
WordEntry::WordEntry(){
    word = "";
    freq = 0;
}
//Word Entry modified constructor
WordEntry::WordEntry(string word, int freq){
    this->word = word;
    this->freq = freq;
}
//Word Entry destructor
WordEntry::~WordEntry(){

}
//Word Entry word setter method
void WordEntry::setWord(string word){
    this->word = word;
}
//Word Entry frequency setter method
void WordEntry::setFreq(int freq){
    this->freq = freq;
}
//Word Entry word getter method
string WordEntry::getWord(){
    return this->word;
}
//Word Entry frequency getter method
int WordEntry::getFreq(){
    return this->freq;
}
//Word Entry overriding the "==" operator
bool WordEntry::operator==(const WordEntry entry2){
    return (this->word == entry2.word);
}
//Word Entry overriding the "<" operator
bool WordEntry::operator<(const WordEntry entry2){
    return (this->word < entry2.word);
}
//Word Entry overriding the ">" operator
bool WordEntry::operator>(const WordEntry entry2){
    return (this->word > entry2.word);
}
//Word Entry overriding the "<<" operator
ostream& operator<<(ostream &strm, const WordEntry &we){
    return (strm << we.word << " - " << we.freq << endl);
}