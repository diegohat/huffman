#include <bits/stdc++.h>
using namespace std;

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
    float max = 0.0;
    float min = 1.0;
    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
    {
        if (max < p->second)
            max = p->second;
        else if (min > p->second)
            min = p->second;
    }

    cout << "MAX VALUE = " << max << endl;
    cout << "MIN VALUE = " << min << endl;

    for (p = wordFreq.begin(); p != wordFreq.end(); p++)
    {
        p->second = (p->second - min) / (max - min);
    }
}

int main()
{

    ifstream myFile("huffman.txt");
    string myText;
    myText.assign((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
    myFile.close();

    unordered_map<string, float> wordFreq;

    setFrequencies(myText, wordFreq);

    printFrequencies(wordFreq);

    normalizeFrequencies(wordFreq);

    printFrequencies(wordFreq);

    return 0;
}