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
        cout << "Unable to open the text file." << endl;
    }

    removePunctuation(myText);
    getTextToVector(myText, &vWord);
    unordered_map<string, float> words;
    setFrequencies(myText, words);
    int countWords = normalizeFrequencies(words);
    transferToQueue(words, countWords);
    // printEncode();
    // createBinaryFile(vWord);

    int menu = 0;

    while (menu != 9)
    {
        cout << "----------MENU----------" << endl;
        cout << "[1] Print word's frequencies." << endl;
        cout << "[2] Print Huffman tree." << endl;
        cout << "[3] Create binary file." << endl;
        cout << "[9] Exit." << endl;
        cout << "------------------------" << endl;
        cout << "Enter an option: ";
        cin >> menu;
        switch (menu)
        {
        case 1:
            printFrequencies(words);
            cout << "------------------------" << endl;
            cout << "Number of Words: " << countWords << endl;
            cout << "------------------------" << endl;
            break;

        case 2:
            printEncode();
            break;

        case 3:
            createBinaryFile(vWord);
            break;

        case 9:
            cout << "Shutting down..." << endl;
            break;

        default:
            cout << "Invalid Option." << endl;
            break;
        }
    }
    return 0;
}
