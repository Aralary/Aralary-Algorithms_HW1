#include <iostream>
#include <cmath>

template<typename T>
void print(T *arr, unsigned int l, unsigned int r) {
    for (unsigned int i = l; i < r + 1; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

template<typename T, typename Comparator = std::less<>>
unsigned int mid_three(T *arr, unsigned int l, unsigned int r, Comparator cmp = Comparator()) {
    if (r == l) {
        return l;
    } else if (r == l + 1) {
        if (cmp(arr[l], arr[r])) {
            return l;
        }
        return r;
    } else {
        unsigned int mid = l + (r - l + 1) / 2;
        T min = std::min(arr[l], std::min(arr[mid], arr[r]));
        T max = std::max(arr[l], std::max(arr[mid], arr[r]));
        T res = arr[l] + arr[mid] + arr[r] - min - max;
        if (arr[mid] == res) {
            return mid;
        } else if (arr[l] == res) {
            return l;
        } else {
            return r;
        }
    }
}

template<typename T, typename Comparator = std::less<>>
unsigned int partition(T *arr, unsigned int l, unsigned int r, Comparator cmp = Comparator()) {
    if (l == r) {
        return l;
    }
    unsigned int pivot_id = mid_three(arr, l, r);
    T pivot = arr[pivot_id];
    if (r != pivot_id) {
        std::swap(arr[r], arr[pivot_id]);
    }
    unsigned int i = l;
    unsigned int j = l;
    while (j < r) {
        while (i < r && cmp(arr[i], pivot) && cmp(arr[j], pivot)) {
            ++i;
            ++j;
        }
        while (j < r && !cmp(arr[j], pivot)) {
            ++j;
        }
        std::swap(arr[i], arr[j]);
        ++i;
        ++j;
    }
    if (j == r && arr[j] == pivot) {
        std::swap(arr[i], arr[j]);
        ++i;
    }
    --i;
    return i;
}

template<typename T, typename Comparator = std::less<>>
void quick_sort(T *arr, unsigned int l, unsigned int r, Comparator cmp = Comparator()) {
    unsigned int pivot = partition(arr, l, r, cmp);
    if (l < pivot) {
        quick_sort(arr, l, pivot - 1, cmp);
    }
    if (r > pivot && pivot >= l) {
        quick_sort(arr, pivot + 1, r, cmp);
    }
}

template<typename T, typename Comparator = std::less<T>>
T kth_stat(T *arr, unsigned int k, unsigned int l, unsigned int r, Comparator cmp = Comparator()) {
    unsigned int pivot_pos = partition(arr, l, r, cmp);

    while (pivot_pos != k) {
        if (pivot_pos > k) {
            r = pivot_pos - 1;
        } else {
            l = pivot_pos + 1;
        }
        pivot_pos = partition(arr, l, r, cmp);
    }
    return arr[pivot_pos];
}


int main() {
    unsigned int size = 0;
    std::cin >> size;
    if (size == 0) {
        return 0;
    }
    auto *arr = new unsigned long long[size];
    for (unsigned int i = 0; i < size; ++i) {
        std::cin >> arr[i];
    }

    unsigned int ten_percent = size * 10 / 100;
    unsigned int mid = size * 50 / 100;
    unsigned int ninety = (size * 90) / 100;
    std::cout << kth_stat(arr, ten_percent, 0, size - 1) << '\n';
    std::cout << kth_stat(arr, mid, 0, size - 1) << '\n';
    std::cout << kth_stat(arr, ninety, 0, size - 1);
    delete[] arr;
    return 0;
}
