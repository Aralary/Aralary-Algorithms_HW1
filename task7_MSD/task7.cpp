#include <iostream>
#include <string>

struct symbol {
    char value;
    int count = 0;
    int end = 0;
};

void print_symbols(symbol *symbols, size_t size) {
    for (size_t i = 0; i < size; ++i) {
        std::cout << " char = " << symbols[i].value << " count = " << symbols[i].count << " end = " << symbols[i].end
                  << std::endl;
    }
}

void print_strings(std::string *strs, size_t l, size_t r) {
    for (size_t i = l; i <= r; ++i) {
        std::cout << strs[i];
        if (i != r) {
            std::cout << std::endl;
        }
    }
}

void MSD(std::string *arr, size_t pos, int l, int r) {
    if (r - l < 1) {
        return;
    }

    char minVal = arr[l][pos];
    char maxVal = arr[l][pos];

    for (size_t i = l + 1; i <= r; i++) {
        minVal = std::min(minVal, arr[i][pos]);
        maxVal = std::max(maxVal, arr[i][pos]);
    }

    int countBufSize = maxVal - minVal + 1;
    auto *countBuf = new symbol[countBufSize]();

    for (size_t i = l; i <= r; i++) {
        countBuf[arr[i][pos] - minVal].value = arr[i][pos];
        countBuf[arr[i][pos] - minVal].count++;
        countBuf[arr[i][pos] - minVal].end++;
    }

    countBuf[0].end = countBuf[0].count;
    for (size_t i = 1; i < countBufSize; i++) {
        countBuf[i].count += countBuf[i - 1].count;
        countBuf[i].end += countBuf[i - 1].end;
    }

    auto *tmpBuf = new std::string[r - l + 1];

    for (int i = r; i >= l; --i) {
        size_t countBufPos = arr[i][pos] - minVal;
        countBuf[countBufPos].count--;
        tmpBuf[countBuf[countBufPos].count] = arr[i];
    }


    for (size_t i = l; i <= r; i++) {
        arr[i] = tmpBuf[i - l];
    }

    delete[] tmpBuf;
    for (size_t i = 0; i < countBufSize; ++i) {
        if (countBuf[i].value != '\0' || (countBuf[i].end - 1 == countBuf[i].count)) {
            MSD(arr, pos + 1, l + countBuf[i].count, l + countBuf[i].end - 1);
        }
    }
    delete[] countBuf;
}


int main() {
    int size = 0;
    int max_count_strs = 100000;
    auto *strs = new std::string[max_count_strs];
    std::string temp;
    while (std::getline(std::cin, temp)) {
        if (temp.empty()) {
            break;
        }
        strs[size] = temp;
        ++size;
    }
    MSD(strs, 0, 0, size - 1);
    print_strings(strs, 0, size - 1);
    delete[] strs;
}