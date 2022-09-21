#include "tree.hpp"

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
    removePunctuation(str);

    stringstream ss(str);
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
        cout << root->data.first << " ";
        for (int i = 0; i < top; i++)
        {
            cout << arr[i];
        }
        cout << endl;
    }
}

void transferToQueue(unordered_map<string, float> words, int countWords)
{
    priority_queue<Tree *, vector<Tree *>, CompareFrequencies> pq;
    ;

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