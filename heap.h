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

struct MinHeap {
    int data[64];
    int size;

    MinHeap() { size = 0; }

    void push(int idx, int weightArr[]) {
        // TODO: insert index at end of heap, restore order using upheap()
        // Minheap will store indices and upheap will compare using weightArr
        data[size] = idx;
        upheap(size, weightArr);
        size++;
    }

    int pop(int weightArr[]) {
        // TODO: remove and return smallest index
        // Case 1: heap is empty
        if (size == 0) {
            return -1;
        }
        // Case 2: else
        int holder = data[0];
        swap(data[0], data[--size]);
        downheap(0, weightArr);
        return holder;
    }

    void upheap(int pos, int weightArr[]) {
        // TODO: swap child upward while smaller than parent
        // Case 1: heap is empty or has one element
        if (size <= 1) {
            return;
        }
        // Case 2: else, while less than parent-- will terminate if pos = 0
        while (weightArr[data[pos]] < weightArr[data[(pos - 1) / 2]]) {
            swap(data[pos], data[(pos - 1) / 2]);
            pos = (pos - 1) / 2;
        }
    }

    void downheap(int pos, int weightArr[]) {
        // TODO: swap parent downward while larger than any child
        // Case 1: heap is empty or has one element
        if (size <= 1) {
            return;
        }
        // Case 2: else, while greater than either child. Check if greater than either, then check for which one and
        // swap accordingly
        while (true) {
            int left = 2 * pos + 1;
            int right = 2 * pos + 2;
            int toSwap = pos;

            // If left child exists and its weight is smaller
            if (left < size && weightArr[left] < weightArr[toSwap]) {
                toSwap = left;
            }

            // If right child exists and its weight is smaller
            if (right < size && weightArr[right] < weightArr[toSwap]) {
                toSwap = right;
            }

            // If no child exists that is smaller, exit
            if (toSwap == pos) {
                return;
            }

            swap(data[pos], data[toSwap]);
            pos = toSwap;
        }
    }
};

#endif