//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>

#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Step 1: Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Step 2: Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Step 3: Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Step 4: Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Step 5: Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Step 1: Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    // Commented out for output format
    //cout << "Frequency table built successfully.\n";
}

// Step 2: Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    // Commented out for output format
    //cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

// Step 3: Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // Create minheap object
    MinHeap *heap = new MinHeap();

    // Push all indexes with an associated weight > 0 into minheap (the least frequent being the root)
    for (int i = 0; i < 26; ++i) {
        if (weightArr[i] > 0) {
            heap->push(i, weightArr);
        }
    }

    // Build encoding tree: adds to weightArr, leftArr, and rightArr while popping from minheap
    while (heap->size > 1) {
        // Set left and right equal to popped indexes, then add their weights to cmbwgt
        int cmbWgt = 0;
        int left = heap->pop(weightArr);
        int right = heap->pop(weightArr);

        cmbWgt += weightArr[left] + weightArr[right];

        // Add cmbWgt to end of weightArr and set pointers to end of left and right
        weightArr[nextFree] = cmbWgt;
        leftArr[nextFree] = left;
        rightArr[nextFree] = right;

        // Push parent back into minheap
        heap->push(nextFree, weightArr);

        nextFree++;
    }

    return heap->data[0];
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Declare stack object and push root node into it, with alterable string
    stack<pair<int, string>> st;
    st.push({root, ""});

    // DFS traversal: Going left adds 0 to string, going right adds 1
    while (!st.empty()) {
        // Save and pop top node (starting with root)
        pair<int, string> node = st.top();
        st.pop();

        // If you reach a leaf node, place the resulting string into proper index for code[] and continue
        if (leftArr[node.first] == -1 && rightArr[node.first] == -1) {
            codes[charArr[node.first] - 'a'] = node.second;
            continue;
        }

        // Else, so long as a right or left child exists, push from left and/or right arrays and add to string
        if (rightArr[node.first] != -1) {
            st.push({rightArr[node.first], node.second + "1"});
        }
        if (leftArr[node.first] != -1) {
            st.push({leftArr[node.first], node.second + "0"});
        }
    }
}

// Step 5: Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";

    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}