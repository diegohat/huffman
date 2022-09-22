#include "tree.hpp"

int main()
{
    ifstream myFile("src/huffman.txt");
    string myText;
    vector<string> vWord;
    if (myFile.is_open())
    {
        myText.assign((istreambuf_iterator<char>(myFile)), istreambuf_iterator<char>());
        myFile.close();
    }
    else
    {
        cout << "Não foi possível abrir o arquivo txt." << endl;
    }

    removePunctuation(myText);
    getTextToVector(myText, &vWord);
    unordered_map<string, float> words;
    setFrequencies(myText, words);
    int countWords = normalizeFrequencies(words);
    transferToQueue(words, countWords);
    // printEncode();
    createBinaryFile(vWord);

    return 0;
}
