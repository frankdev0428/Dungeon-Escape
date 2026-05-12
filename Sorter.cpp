#include <iostream>
#include <vector>
#include "Sorter.h"

// --- Merge step ---
// Takes two sorted halves of 'items' (left..mid and mid+1..right)
// and merges them into one sorted sequence in place.
void merge(std::vector<Item>& items, int left, int mid, int right) {

    // Copy both halves into temporary vectors
    std::vector<Item> leftHalf;
    std::vector<Item> rightHalf;

    for (int i = left; i <= mid; i++)
        leftHalf.push_back(items[i]);

    for (int i = mid + 1; i <= right; i++)
        rightHalf.push_back(items[i]);

    int i = 0;          // index into leftHalf
    int j = 0;          // index into rightHalf
    int k = left;       // index into the original items vector

    // Compare front of each half and place the smaller one back
    while (i < leftHalf.size() && j < rightHalf.size()) {
        if (leftHalf[i].getValue() <= rightHalf[j].getValue()) {
            items[k] = leftHalf[i];
            i++;
        } else {
            items[k] = rightHalf[j];
            j++;
        }
        k++;
    }

    // Copy any leftover elements from either half
    while (i < leftHalf.size()) { items[k] = leftHalf[i]; i++; k++; }
    while (j < rightHalf.size()) { items[k] = rightHalf[j]; j++; k++; }
}

// --- Merge Sort (recursive) ---
// Splits items into halves until each half has one element (base case),
// then merges them back in sorted order on the way up.
void mergeSort(std::vector<Item>& items, int left, int right) {

    // Base case: a single element is already sorted — stop recursing
    if (left >= right) return;

    int mid = (left + right) / 2;      // find the midpoint

    mergeSort(items, left, mid);        // sort left half
    mergeSort(items, mid + 1, right);   // sort right half
    merge(items, left, mid, right);     // merge the two sorted halves
}

// Public entry point — called from main with the full vector
void sortItems(std::vector<Item>& items) {
    if (items.empty()) return;
    mergeSort(items, 0, items.size() - 1);
}
