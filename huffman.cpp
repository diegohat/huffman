#include "wordcounter.hpp"

struct Node
{
    pair<string, float> data;
    Node *left, *right;

    Node(pair<string, float> data)
    {
        this->data = data;
        left = right = nullptr;
    }
};

struct compareFrequencies
{
    bool operator()(Node *a, Node *b)
    {
        return a->data.second > b->data.second;
    }
};

Node *createTree(priority_queue<Node *, vector<Node *>, compareFrequencies> pq)
{
    while (pq.size() != 1)
    {
        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        Node *node = new Node(pair<string, float>("test", left->data.second + right->data.second));

        node->left = left;
        node->right = right;

        pq.push(node);
    }
    return pq.top();
}