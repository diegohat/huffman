#include "wordcounter.hpp"

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
    removePunctuation(str);

    stringstream ss(str);
    string word;
    while (ss >> word)
        wordFreq[word]++;
}

void printFrequencies(unordered_map<string, float> &wordFreq)
{
    unordered_map<string, float>::iterator p;
    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        cout << "(" << p->first << ", " << p->second << ")\n";
}

void normalizeFrequencies(unordered_map<string, float> &wordFreq)
{
    unordered_map<string, float>::iterator p;
    int countWords = 0;

    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        countWords++;

    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
        p->second /= countWords;
}