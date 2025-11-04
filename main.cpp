//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>

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

    cout << "Frequency table built successfully.\n";
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
    cout << "Created " << nextFree << " leaf nodes.\n";
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

    cout << "Root index is: " << heap->data[0] << endl;
    return heap->data[0];
}

// Step 4: Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // TODO:
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    // Declare stack object and push root node into it, with alterable string
    stack<pair<int, string>> st;
    st.push({root, ""});

    int k = 11;
    cout << "charArr[]: ";
    for (int i = 0; i < k; i++) {
        cout << charArr[i] << " ";
    }
    cout << "\nweightArr[]: ";
    for (int i = 0; i < k; i++) {
        cout << weightArr[i] << " ";
    }
    cout << "\nleftArr[]: ";
    for (int i = 0; i < k; i++) {
        cout << leftArr[i] << " ";
    }
    cout << "\nrightArr[]: ";
    for (int i = 0; i < k; i++) {
        cout << rightArr[i] << " ";
    }
    cout << endl;

    while (!st.empty()) {
        pair<int, string> node = st.top();
        //cout << "STACK --> Index: " << node.first << " string: " << node.second << endl;
        //cout << "left: " << weightArr[leftArr[node.first]] << " at index: " << leftArr[node.first] << "; and right: "
            //<< weightArr[rightArr[node.first]] << " at index: " << rightArr[node.first] << endl;
        //cout << endl;
        //cout << "Traversed: " << traversed[node.first] << endl;
        st.pop();

        if (leftArr[node.first] == -1 && rightArr[node.first] == -1) {
            codes[charArr[node.first] - 'a'] = node.second;
            continue;
        }
        if (rightArr[node.first] != -1) {
            st.push({rightArr[node.first], node.second + "1"});
        }
        if (leftArr[node.first] != -1) {
            st.push({leftArr[node.first], node.second + "0"});
        }


        /*if (traversed[node.first]) {
            if (node.first > 0) {
                st.push({--node.first, ""});
                continue;
            }
            continue;
        }

        traversed[node.first] = true;

        int i = 0;
        int j = root;

        // If approached leaf, end
        if (leftArr[node.first] == -1 && rightArr[node.first] == -1) {
            // Assign to index containing correct letter
            int holder = charArr[node.first];
            codes[holder - 'a'] = node.second;

            st.push({root, ""});
            continue;
        }

        //else, if not traversed to left or right
        if (rightArr[node.first] != -1) {
            //st.push({rightArr[node.first], node.second + "0"}); //needs to be 3 ... the index of the wanted character at weightArr...
            // ... so rightArr[node.first] == weightArr[3], and we want that index... basically, from right we want to find it in weightArr
            while (rightArr[node.first] != weightArr[j]) {
                j--;
                //cout<< j <<endl;
            }
            st.push({j, node.second + "1"});
        }
        else {
            while (leftArr[node.first] != weightArr[i]) {
                i++;
            }
            st.push({i, node.second + "0"}); // needs to be 0
        }*/
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