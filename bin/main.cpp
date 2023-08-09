#include <lib/number.h>
#include <iostream>

int main() {
    uint2022_t a = from_uint(2000);
    uint2022_t b = from_uint(2);
    std::cout << a / b << std::endl;

    return 0;
}