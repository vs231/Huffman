#include <iostream>
#include <queue>
#include <vector>
#include <string>

using namespace std;

struct Node {
    char data;
    int frequency;
    Node *left, *right;

    Node(char data, int frequency) : data(data), frequency(frequency), left(nullptr), right(nullptr) {}
};

struct comp {
    bool operator()(Node* a, Node* b) {
        return a->frequency > b->frequency;
    }
};

Node* build(vector<pair<char, int>>& charfreq) {
    priority_queue<Node*, vector<Node*>, comp> minHeap;

    for (const auto& entry : charfreq) {
        Node* newNode = new Node(entry.first, entry.second);
        minHeap.push(newNode);
    }

    while (minHeap.size() > 1) {
        Node* left = minHeap.top();
        minHeap.pop();
        Node* right = minHeap.top();
        minHeap.pop();

        Node* internalNode = new Node('\0', left->frequency + right->frequency);
        internalNode->left = left;
        internalNode->right = right;

        minHeap.push(internalNode);
    }

    return minHeap.top();
}

void print(Node* root, string code) {
    if (root == nullptr) {
        return;
    }

    if (root->data != '\0') {
        cout << root->data << ": "<< code << endl;
    }

    print(root->left, code + "0");
    print(root->right, code + "1");
}

int main() {
    string inputString;
    cout << "Enter the string: ";
    cin >> inputString;

    vector<pair<char, int>> charfreq;
    for (char character : inputString) {
        int frequency;
        cout << "Enter frequency for character '" << character << "': ";
        cin >> frequency;
        charfreq.push_back({character, frequency});
    }

    Node* root = build(charfreq);

    cout << "\nHuffman Codes:\n";
    print(root, "");

    return 0;
}
