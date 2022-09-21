#include <bits/stdc++.h>
#ifndef _WORDCOUNTER_H
#define _WORDCOUNTER_H

using namespace std;

void removePunctuation(string &myString);
void setFrequencies(string &str, unordered_map<string, float> &wordFreq);
void printFrequencies(unordered_map<string, float> &wordFreq);
void normalizeFrequencies(unordered_map<string, float> &wordFreq);

#endif