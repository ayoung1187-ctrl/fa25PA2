//
// Created by Manju Muralidharan on 10/19/25.
//

//
// Updated by Ashley Young
//

#ifndef HEAP_H
#define HEAP_H

#include <iostream>
using namespace std;

// All to be fixed later-- just getting thoughts out
// weightArr[] is the frequency of each character arranged in an array

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        data[size] = weightArr[idx];
        upheap(0, data);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Case 1: heap is empty
        if (size == 0) {
            return 0;
        }
        // Case 2: else
        int holder = data[0];
        data[0] = data[--size];
        downheap(0, data);
        return holder;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // Case 1: heap is empty
        // Case 2: heap has one element
        // Case 3: else
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        // Case 1: heap is empty
        // Case 2: heap has one element
        // Case 3: else
    }
};

#endif