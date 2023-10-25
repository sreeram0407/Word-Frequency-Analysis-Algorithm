/*
Author: Sreeram Kondapalli
Date: 11/24/2022
Description: The goal will be to parse a large text file and determine the word frequency of
every word in the text file.
*/
#ifndef KONDAPALLI_SREERAM_HW5_WORD_ENTRY_H
#define KONDAPALLI_SREERAM_HW5_WORD_ENTRY_H
#include <string>
using namespace std;

class WordEntry {
private:
    string word;
    int freq;
public:
    //forward declaration
    WordEntry();

    WordEntry(string word, int freq);

    ~WordEntry();

    void setWord(string word);

    void setFreq(int freq);

    string getWord();

    int getFreq();

    bool operator==(const WordEntry entry2);

    bool operator<(const WordEntry entry2);

    bool operator>(const WordEntry entry2);

    friend ostream& operator<<(ostream &strm, const WordEntry &we);
};




#endif //KONDAPALLI_SREERAM_HW5_WORD_ENTRY_H
