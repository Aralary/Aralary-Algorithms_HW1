#include <iostream>

struct line {
    unsigned int l = 0;
    unsigned int r = 0;
};

bool operator<(line a, line b) {
    if (a.l != b.l) {
        return a.l < b.l;
    }
    return a.r < b.r;
}

template<typename T, class Compare = std::less<>>
void merge(T *arr, size_t l, size_t mid, size_t r, Compare cmp = Compare{}) {
    size_t length_left = mid - l + 1;
    size_t length_right = r - mid;
    T left_arr[length_left];
    T right_arr[length_right];
    for (size_t i = 0; i < length_left; ++i) {
        left_arr[i] = arr[l + i];
    }
    for (size_t i = 0; i < length_right; ++i) {
        right_arr[i] = arr[mid + 1 + i];
    }

    size_t i = 0;
    size_t j = 0;

    size_t length = r - l + 1;

    for (size_t k = 0; k < length; ++k) {
        bool f = (i < length_left && j < length_right);
        if (f) {
            if (cmp(left_arr[i], right_arr[j])) {
                arr[l + k] = left_arr[i];
                ++i;
            } else {
                arr[l + k] = right_arr[j];
                ++j;
            }
        } else if (i >= length_left) {
            arr[l + k] = right_arr[j];
            ++j;
        } else if (j >= length_right) {
            arr[l + k] = left_arr[i];
            ++i;
        }
    }
}

template<typename T>
void print(T *arr, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

template<typename T, class Cmp = std::less<>>
void merge_sort(T *arr, size_t left, size_t right, Cmp cmp = Cmp{}) {
    if (left >= right) {
        return;
    }
    size_t mid = (right - left) / 2 + left;

    merge_sort(arr, left, mid);
    merge_sort(arr, mid + 1, right);

    merge(arr, left, mid, right);
}

void print_l(line *lines, size_t k) {
    for (size_t i = 0; i < k; ++i) {
        std::cout << '(' << lines[i].l << ',' << lines[i].r << ')' << std::endl;
    }
}

int main() {
    size_t k = 0;
    std::cin >> k;

    line *lines = new line[k];
    for (size_t i = 0; i < k; ++i) {
        std::cin >> lines[i].l >> lines[i].r;
    }

    if (k <= 0) {
        std::cout << 0;
        return 0;
    }

    merge_sort(lines, 0, k - 1);

    size_t result = 0;

    line temp_line;
    temp_line.l = lines[0].l;
    temp_line.r = lines[0].r;
    for (size_t i = 0; i < k - 1; ++i) {
        //1
        if (temp_line.l >= lines[i + 1].r) {
            continue;
        }
            //2
        else if (temp_line.l >= lines[i + 1].l && temp_line.r <= lines[i + 1].r) {
            temp_line.l = temp_line.r;
            temp_line.r = lines[i + 1].r;
        }
            //3
        else if (temp_line.l >= lines[i + 1].l && temp_line.r > lines[i + 1].r) {
            temp_line.l = lines[i + 1].r;
        }
            //4
        else if (temp_line.r <= lines[i + 1].l) {
            result += (temp_line.r - temp_line.l);
            temp_line.l = lines[i + 1].l;
            temp_line.r = lines[i + 1].r;
        }
            //5
        else if (temp_line.r >= lines[i + 1].l && temp_line.r <= lines[i + 1].r) {
            result += ((lines[i + 1].l - temp_line.l));// + (lines[i+1].r- temp_line.r)
            temp_line.l = temp_line.r;
            temp_line.r = lines[i + 1].r;
        }
            //6
        else if (temp_line.r > lines[i + 1].l && temp_line.r > lines[i + 1].r) {
            result += ((lines[i + 1].l - temp_line.l));// + (lines[i+1].r- temp_line.r)
            temp_line.l = lines[i + 1].r;
        }
    }
    result += (temp_line.r - temp_line.l);
    std::cout << result;
    delete[] lines;
}
