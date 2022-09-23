#ifndef _TREE_H_
#define _TREE_H_

#include <iostream>
#include <queue>
#include <unordered_map>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <map>

using namespace std;

class Tree
{
private:
public:
    pair<string, float> data;
    Tree *left, *right;
    Tree(pair<string, float> data);
};

struct CompareFrequencies
{
    bool operator()(Tree *a, Tree *b)
    {
        return a->data.second > b->data.second;
    }
};

Tree *createHuffmanTree(priority_queue<Tree *, vector<Tree *>, CompareFrequencies> pq);
void removePunctuation(string &myString);
void setFrequencies(string &str, unordered_map<string, float> &wordFreq);
int normalizeFrequencies(unordered_map<string, float> &wordFreq);
void printTree(Tree *root, int arr[], int top);
void transferToQueue(unordered_map<string, float> words, int countWords);
void printFrequencies(unordered_map<string, float> &wordFreq);
void printEncode();
void getTextToVector(string &myText, vector<string> *vWord);
void createBinaryFile(vector<string> vWord);

#endif