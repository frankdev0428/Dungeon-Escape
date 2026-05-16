#include <vector>
#include "MergeSort.h"

void merge(std::vector<Item>& items, int left, int mid, int right) {
    std::vector<Item> leftHalf;
    std::vector<Item> rightHalf;

    for (int i = left;     i <= mid;   i++) leftHalf.push_back(items[i]);
    for (int i = mid + 1;  i <= right; i++) rightHalf.push_back(items[i]);

    int i = 0, j = 0, k = left;
    while (i < (int)leftHalf.size() && j < (int)rightHalf.size()) {
        if (leftHalf[i].getValue() <= rightHalf[j].getValue())
            items[k++] = leftHalf[i++];
        else
            items[k++] = rightHalf[j++];
    }
    while (i < (int)leftHalf.size())  items[k++] = leftHalf[i++];
    while (j < (int)rightHalf.size()) items[k++] = rightHalf[j++];
}

void mergeSort(std::vector<Item>& items, int left, int right) {
    if (left >= right) return;
    int mid = (left + right) / 2;
    mergeSort(items, left, mid);
    mergeSort(items, mid + 1, right);
    merge(items, left, mid, right);
}

void sortItems(std::vector<Item>& items) {
    if (items.empty()) return;
    mergeSort(items, 0, (int)items.size() - 1);
}
