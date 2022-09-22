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

unordered_map<string, vector<bool>> gEncode;

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
void createBinaryFile();

Tree::Tree(pair<string, float> data)
{
    this->data = data;
    left = right = nullptr;
}

Tree *createHuffmanTree(priority_queue<Tree *, vector<Tree *>, CompareFrequencies> pq)
{
    while (pq.size() != 1)
    {
        Tree *left = pq.top();
        pq.pop();
        Tree *right = pq.top();
        pq.pop();

        Tree *node = new Tree(pair<string, float>("null", left->data.second + right->data.second));

        node->left = left;
        node->right = right;

        pq.push(node);
    }
    return pq.top();
}

void removePunctuation(string &myString)
{
    auto lowercase = transform(myString.begin(), myString.end(), myString.begin(),
                               [](unsigned char c)
                               { return tolower(c); });

    auto remove = remove_if(myString.begin(), myString.end(), [](char const &s)
                            { return ispunct(s); });
    myString.erase(remove, myString.end());
}

void setFrequencies(string &str, unordered_map<string, float> &wordFreq)
{
    istringstream ss(str);
    string word;
    while (ss >> word)
        wordFreq[word]++;
}

int normalizeFrequencies(unordered_map<string, float> &wordFreq)
{
    unordered_map<string, float>::iterator p;
    int countWords = 0;

    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        countWords++;

    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        p->second /= countWords;
    return countWords;
}

void printTree(Tree *root, int arr[], int top)

{
    if (root->left)
    {
        arr[top] = 0;
        printTree(root->left,
                  arr, top + 1);
    }

    if (root->right)
    {
        arr[top] = 1;
        printTree(root->right, arr, top + 1);
    }

    if (!root->left && !root->right)
    {
        pair<string, vector<bool>> aux;
        aux.second.clear();
        aux.first = root->data.first;
        // cout << root->data.first << " ";

        for (int i = 0; i < top; i++)
        {
            // cout << arr[i];
            aux.second.push_back(arr[i]);
        }
        // cout << endl;
        gEncode.insert(aux);
    }
}

void transferToQueue(unordered_map<string, float> words, int countWords)
{
    priority_queue<Tree *, vector<Tree *>, CompareFrequencies> pq;

    for (unordered_map<string, float>::iterator p = words.begin(); p != words.end(); p++)
    {
        Tree *newNode = new Tree(pair<string, float>(p->first, p->second));
        pq.push(newNode);
    }

    Tree *root = createHuffmanTree(pq);
    int arr[countWords], top = 0;
    printTree(root, arr, top);
}

void printFrequencies(unordered_map<string, float> &wordFreq)
{
    unordered_map<string, float>::iterator p;
    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        cout << "(" << p->first << ", " << p->second << ")\n";
}

void printEncode()
{
    for (auto item : gEncode)
    {
        cout << "(" << item.first << ", ";
        for (auto itemVec : item.second)
        {
            cout << itemVec;
        }
        cout << ")" << endl;
    }
}

void getTextToVector(string &myText, vector<string> *vWord)
{
    istringstream ss(myText);
    string word;
    while (ss >> word)
        vWord->push_back(word);
}

void createBinaryFile(vector<string> vWord)
{
    ofstream myFile("src/test.dat", ios::out | ios::binary);
    if (!myFile.good())
    {
        cout << "Cannot open file!" << endl;
        return;
    }
    string text;
    unordered_map<string, vector<bool>>::iterator p;
    for (auto item : vWord)
    {
        text.assign("");
        p = gEncode.find(item);
        if (p != gEncode.end())
        {
            for (auto i : p->second)
                text.append(to_string(i));
            myFile.write(text.c_str(), (text.size()));
        }
    }

    myFile.close();
}

#endif