/*
Author: Sreeram Kondapalli
Date: 11/24/2022
Description: The goal will be to parse a large text file and determine the word frequency of
every word in the text file.
Usage: ./exe
*/

#include <iostream>
#include <fstream>
#include <string.h>
#include <algorithm>
#include "Kondapalli_BST.h"
#include "Word_Entry.h"

using namespace std;

//forward declarations of functions
bool splitinsert(BinarySearchTree<WordEntry>* tree,string output);
int totalWordsRecur(Node<WordEntry>* root, int num);
int totalWords(BinarySearchTree<WordEntry>* tree);
int uniqueWords(BinarySearchTree<WordEntry>* tree);
int freqFinder(BinarySearchTree<WordEntry>* tree, string word);
int freqComp(WordEntry w1,  WordEntry w2);
int freqCompReverse(WordEntry w1,  WordEntry w2);
void printArray(WordEntry* arr, int n);


//output file
ofstream writer ("Analysis.txt");

//main
int main()
{
    string filename;
    string output;
    int choice;
    int uniqueSize;
    string userInput;

//UI
    cout << "Welcome to Sreeram Kondapalli's Word Frequency Analysis Algorithm" << endl;
    cout << "Choose a file that you would like to perform word frequency analysis on:" << endl;
    cout << "1. Frankenstein\n2. Frost Poems\n3. Frost Ghost\n4. Warpeace" << endl;
    cin >> choice;
//switch statement to give the user a choice to pick from
    switch(choice)
    {
        case 1 : filename = "./frankenstein.txt";
            break;

        case 2 : filename = "./frost_poems.txt";
            break;

        case 3 : filename = "./frostGhost.txt";
            break;

        case 4 : filename = "./warpeace.txt";
            break;
        default: cout << "Error, choose a valid choice" << endl;
    }

    ifstream input(filename);
//creating a new binary search tree object on the heap
    BinarySearchTree<WordEntry>* tree = new BinarySearchTree<WordEntry>();


    while (!input.eof()){
        input >> output;
        splitinsert(tree, output);
    }

//prints the total amount of words
    cout << "Total words : " << totalWords(tree) << endl;
    writer << "Total words : " << totalWords(tree) << endl;
//prints the total unique amount of words
    cout << "Total unique words : " << uniqueWords(tree) << endl;
    writer << "Total unique words : " << uniqueWords(tree) << endl;

//gives an analysis of the words to search the frequency of
    cout << "For a more detailed analysis\nEnter a word you would like to search the frequency of (analysis will be printed in the file): ";
    cin >> userInput;
//prints the frequency of the word
    writer << "Frequency of the word " << "\"" << userInput << "\" is : " << freqFinder(tree, userInput) << endl;
    cout << "Frequency of the word " << "\"" << userInput << "\" is : " << freqFinder(tree, userInput) << endl;
    cout << endl << endl;
    uniqueSize = uniqueWords(tree);

    WordEntry* array = new WordEntry[uniqueSize + 20];


    int arraySize = tree->ToArray(array);
    //calling the array to get the 5 least used words
    sort(array, array+arraySize, freqComp);
    //prints out the 5 least used words
    writer << endl << "Printing the 5 least used words : " << endl;
    cout << endl << "Printing the 5 least used words : " << endl;
    printArray(array, 5);
    tree->Empty();

    //reverses the array to get the 5 most used words
    sort(array, array+arraySize, freqCompReverse);
    //prints out the 5 most used words
    writer << "Printing the 5 most used words : " << endl;
    cout << endl << "Printing the 5 least used words : " << endl;
    printArray(array, 5);
    tree->Empty();


    sort(array, array+arraySize, freqCompReverse);
    writer << "Printing by frequency : " << endl;
    //prints by frequency
    cout << "Printing by frequency : " << endl;
    printArray(array, arraySize);
    cout << "The Frequency Analysis is written in the file - Analysis.txt" << endl << endl;
    delete tree;
    return 0;
}

// This function splits and inserts the words using the binary search tree
bool splitinsert(BinarySearchTree<WordEntry>* tree,string output)
{
    string data = "";
    int length;
    char charector;

    length = output.length();
    int counter = 0;
    bool bool1;
//this loop runs when the counter is less than the length
    while (counter < length)
    {
        charector = output[counter];
        bool1 = false;
        //making sure every letter whether its capital or not to be included
        while ((charector >= 'a' && charector <='z') || (charector >='A' && charector<='Z') || charector=='\'')
        {
            data+=tolower(charector);
            bool1 = true;
            counter++;
            charector = output[counter];
        }

        if(bool1)
        {
            WordEntry we(data, 1);
            bool result = tree->Insert(we);
            if(!result){
                Node<WordEntry>* node = tree->Find(we);
                int freq = node->getData().getFreq();
                node->getData().setFreq(freq+1);
            }
            data = "";
        }
        else counter++;
    }
    return false;
}
//this function analysis and sums up the total words of the file
int totalWordsRecur(Node<WordEntry>* root, int num)
{
    if(root == NULL) return num;

    num= totalWordsRecur(root->getLeft(), num);
    num+= root->getData().getFreq();
    num = totalWordsRecur(root->getRight(), num);
    return num;

}
//this function sums up the total words in the file
int totalWords(BinarySearchTree<WordEntry>* tree)
{
    if(tree == NULL) return -1;
    if(tree->getRoot()==NULL) return 0;
    return totalWordsRecur(tree->getRoot(), 0);
}
//this function sums up the total unique words in the file
int uniqueWords(BinarySearchTree<WordEntry>* tree)
{
    return tree->Count();
}
//this function finds and counts the frequency of the words in the file
int freqFinder(BinarySearchTree<WordEntry>* tree, string word)
{
    if(tree==NULL) return -1;
    if(tree->getRoot()==NULL) return 0;
    WordEntry dummy(word, 0);
    Node<WordEntry>* node = tree->Find(dummy);
    if(node==NULL) return 0;
    return node->getData().getFreq();
}
//this function analyses the frequency of words in the file in a decending order
int freqComp(WordEntry w1,  WordEntry w2)
{
    return w1.getFreq() < w2.getFreq();
}
//this function reverses the freqComp to count the words in an accending order
int freqCompReverse(WordEntry w1,  WordEntry w2)
{
    return w1.getFreq() > w2.getFreq();
}
//this function prints the outputs into a different file
void printArray(WordEntry* arr, int n)
{
    for(int i=0; i<n; i++)
    {
        writer<<arr[i];

    }
    writer<<endl;
}

