#include "tree.hpp"

int main()
{
    ifstream myFile("huffman.txt");
    string myText;
    myText.assign((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
    myFile.close();

    unordered_map<string, float> words;
    setFrequencies(myText, words);
    int countWords = normalizeFrequencies(words);
    transferToQueue(words, countWords);

    return 0;
}
