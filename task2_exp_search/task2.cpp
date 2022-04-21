#include <iostream>

size_t custom_binary_search(const int set[], size_t set_size, int el, size_t left, size_t right) {
    size_t mid = left + (right - left) / 2;
    while (right >= left) {
        if (set[mid] == el) {
            return mid;
        } else if (set[mid] < el) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
        mid = left + (right - left) / 2;
    }
    return set_size;
}

size_t exp_search(const int set1[], size_t n, size_t sep, int el) {
    while (sep < (n - 1) && set1[sep] < el) {
        sep *= 2;
    }
    if (sep > n - 1) {
        sep = n - 1;
    }
    return custom_binary_search(set1, n, el, sep / 2, sep);
}

void solve(const int set1[], size_t n, int set2[], size_t m) {
    size_t k = 0;// count of same elements
    size_t sep = 1;
    for (size_t i = 0; i < m; ++i) {
        if (set2[i] > set1[n - 1] || set2[m - 1] < set1[0]) {
            i = m;
        } else if (set2[i] < set1[0]) {
            continue;
        } else {
            size_t temp = exp_search(set1, n, sep, set2[i]);
            if (temp < n) {
                set2[k] = set1[temp];
                ++k;
            }
        }
    }
    if (k != 0) {
        for (size_t i = 0; i < k; ++i) {
            std::cout << set2[i];
            if (i != k - 1) {
                std::cout << ' ';
            }
        }
    } else {
        std::cout << "";
    }
}

void fill_sets(int set1[], size_t n, int set2[], size_t m) {
    for (size_t i = 0; i < n; ++i) {
        std::cin >> set1[i];
    }
    for (size_t i = 0; i < m; ++i) {
        std::cin >> set2[i];
    }
}

int main() {
    size_t n, m;
    std::cin >> n >> m;
    int set1[n];
    int set2[m];
    fill_sets(set1, n, set2, m);
    solve(set1, n, set2, m);
    return 0;
}
