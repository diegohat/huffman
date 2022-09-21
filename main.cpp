#include "wordcounter.cpp"

int main()
{
    ifstream myFile("huffman.txt");
    string myText;
    myText.assign((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
    myFile.close();

    unordered_map<string, float> wordFreq;

    setFrequencies(myText, wordFreq);
    normalizeFrequencies(wordFreq);
    printFrequencies(wordFreq);

    return 0;
}