#include <iostream>
#include <cmath>

class Deque {
public:
    Deque() : data(nullptr), head_id(0), tail_id(0), size(0), capacity(0) {}

    ~Deque() {
        delete[] data;
    }

    void push_back(int a) {
        if (data == nullptr) {
            data = new int[1];
            data[0] = a;
            capacity = 1;
        } else {
            if (size == 0 && capacity > 0) {
                data[head_id] = a;
            } else if (size > 0 && size < capacity) {
                if (tail_id == (capacity - 1)) {
                    tail_id = 0;
                } else {
                    ++tail_id;
                }
                data[tail_id] = a;
            } else if (size == capacity) {
                grow();
                data[tail_id + 1] = a;
                tail_id = size;
            }
        }
        ++size;
    }

    void push_front(int a) {
        if (data == nullptr) {
            data = new int[1];
            data[0] = a;
            capacity = 1;
        } else {
            if (size == 0 && capacity > 0) {
                data[head_id] = a;
            } else if (size > 0 && size < capacity) {
                if (head_id == 0) {
                    head_id = capacity - 1;
                } else {
                    --head_id;
                }
                data[head_id] = a;
            } else if (size == capacity) {
                grow();
                data[capacity - 1] = a;
                head_id = capacity - 1;
            }
        }
        ++size;
    }

    int pop_back() {
        if (size == 0) {
            return -1;
        } else {
            int res = data[tail_id];
            if (size > 1) {
                if (tail_id == 0) {
                    tail_id = capacity - 1;
                } else {
                    --tail_id;
                }
            }
            --size;
            return res;
        }
    }

    int pop_front() {
        if (size == 0) {
            return -1;
        } else {
            int res = data[head_id];
            if (size > 1) {
                if (head_id == capacity - 1) {
                    head_id = 0;
                } else {
                    ++head_id;
                }
            }
            --size;
            return res;
        }
    }

    void print() {
        for (size_t i = 0; i < size; ++i) {
            std::cout << data[(head_id + i) % capacity] << ' ';
        }
        std::cout << '\n';
    }

private:
    void grow() {
        int *new_data = new int[capacity * 2];
        for (size_t i = 0; i < size; ++i) {
            new_data[i] = data[(head_id + i) % capacity];
        }
        head_id = 0;
        tail_id = size - 1;
        delete[] data;
        data = new_data;
        capacity *= 2;
    }

    int *data;
    size_t head_id;
    size_t tail_id;
    size_t size;
    size_t capacity;
};

int main() {
    size_t n = 0;
    std::cin >> n;
    bool f = true;
    Deque d;
    for (size_t i = 0; i < n; ++i) {
        int a, b;
        std::cin >> a >> b;
        if (a == 1) {
            d.push_front(b);
        } else if (a == 2) {
            int k = d.pop_front();
            if (k != b) {
                f = false;
            }
        } else if (a == 3) {
            d.push_back(b);
        } else if (a == 4) {
            int k = d.pop_back();
            if (k != b) {
                f = false;
            }
        }
    }
    if (f) {
        std::cout << "YES";
    } else {
        std::cout << "NO";
    }
    return 0;
}