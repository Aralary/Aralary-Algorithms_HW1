#include <iostream>

int main() {
    unsigned int n = 0;
    unsigned int k = 0;
    std::cin >> n >> k;//
    std::cout << (n ^ (1 << k));
    return 0;
}