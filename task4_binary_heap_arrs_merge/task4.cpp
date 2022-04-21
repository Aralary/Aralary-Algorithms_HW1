#include <iostream>

template<typename T>
struct arr_iterator {
    T *arr;
    size_t size;
    size_t current_el;

    bool operator<(const arr_iterator &it) {
        return arr[current_el] < it.arr[current_el];
    }

    bool operator>(const arr_iterator &it) {
        return arr[current_el] > it.arr[current_el];
    }

    bool operator==(arr_iterator it) {
        if (size != it.size) {
            return false;
        }
        for (size_t i = 0; i < size; ++i) {
            if (arr[i] != it.arr[i]) {
                return false;
            }
        }
        return true;
    }

    arr_iterator &operator++() {
        ++current_el;
        return *this;
    }
};

template<typename K>
bool operator<(arr_iterator<K> &it1, arr_iterator<K> &it2) {
    if (it1.current_el + 1 > it1.size) {
        throw std::runtime_error("out of range");
    }
    return it1.arr[it1.current_el] < it2.arr[it2.current_el];
}

template<typename K>
bool operator>(arr_iterator<K> &it1, arr_iterator<K> &it2) {
    return it1.arr[it1.current_el] > it2.arr[it2.current_el];
}

template<typename K>
void swap(arr_iterator<K> &it1, arr_iterator<K> &it2) {
    std::swap(it1.size, it2.size);
    std::swap(it1.current_el, it2.current_el);
    std::swap(it1.arr, it2.arr);
}

template<typename T, class Compare=std::less<>>
class Heap {
public:
    Heap() : data(nullptr) {}

    Heap(size_t n) {
        data = new T[n];
        capacity = n;
    }

    ~Heap() {
        delete[] data;
    }

    bool empty() const {
        return size == 0;
    }

    void add_el(T el) {
        if (capacity == size) {
            grow();
        }
        data[size] = el;
        if (size != 0) {
            sift_up(size);
        }
        ++size;
    }

    T &top() {
        if (size > 0) {
            return data[0];
        }
        throw std::invalid_argument("empty");
    }

    T erase_top() {
        if (size == 0) {
            return T();
        }
        if (size == 1) {
            --size;
            return data[0];
        }
        T temp = data[0];
        std::swap(data[0], data[size - 1]);
        --size;
        sift_down(0);
        return temp;
    }

    void sift_down(size_t id) {
        while (2 * id + 1 < size) {
            size_t left = 2 * id + 1;
            size_t right = 2 * id + 2;
            if (right < size) {
                if (cmp(data[left], data[right])) {
                    if (!cmp(data[id], data[left])) {
                        std::swap(data[id], data[left]);
                        id = left;
                    } else {
                        id = size / 2;
                    }
                } else {
                    if (!cmp(data[id], data[right])) {
                        std::swap(data[id], data[right]);
                        id = right;
                    } else {
                        id = size / 2;
                    }
                }
            } else {
                if (!cmp(data[id], data[left])) {
                    std::swap(data[id], data[left]);
                }
                id = size / 2;
            }
        }
    }

    void sift_up(size_t id) {
        while (id != 0) {
            if (cmp(data[id], data[(id - 1) / 2])) {
                std::swap(data[id], data[(id - 1) / 2]);
                id = (id - 1) / 2;
            } else {
                id = 0;
            }
        }
    }

    size_t Size() const noexcept {
        return size;
    }

private:
    void grow() {
        if (capacity == 0) {
            data = new T[1];
            ++capacity;
        } else {
            T *new_data = new T[capacity * 2];
            for (size_t i = 0; i < capacity; ++i) {
                new_data[i] = data[i];
            }
            delete[] data;
            data = new_data;
            capacity *= 2;
        }
    }

    Compare cmp;
    T *data;
    size_t size = 0;
    size_t capacity = 0;
};

template<typename T>
void print_answer(Heap<T> &heap) {
    while (!heap.empty()) {
        std::cout << heap.top().arr[heap.top().current_el];
        ++heap.top().current_el;
        if (heap.top().current_el == heap.top().size) {
            heap.erase_top();
        } else {
            heap.sift_down(0);
        }
        if (heap.Size() != 0) {
            std::cout << ' ';
        }
    }
}

int main() {
    size_t n;
    std::cin >> n;
    Heap<arr_iterator<int>> heap(n);
    arr_iterator<int> temp{nullptr, 0, 0};
    int **all_data = new int *[n]; // collect all "new" data to clear
    for (size_t i = 0; i < n; ++i) {
        std::cin >> temp.size;
        temp.arr = new int[temp.size];
        for (size_t j = 0; j < temp.size; j++) {
            std::cin >> temp.arr[j];
        }
        all_data[i] = temp.arr;
        if (temp.size != 0) {
            heap.add_el(temp);
        }
    }

    print_answer(heap);

    for (size_t i = 0; i < n; ++i) {
        delete[] all_data[i];
    }
    delete[] all_data;
    return 0;
}