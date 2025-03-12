#include "../include/ascii85.h"
#include <iostream>
#include <cstdint>

using namespace std;

void encode(const char* input, size_t len, ostream& out) {
    if (len == 0) return;

    uint32_t num = 0;
    for (size_t i = 0; i < 4; ++i) {
        uint8_t byte = (i < len) ? static_cast<uint8_t>(input[i]) : 0;
        num = (num << 8) | byte;
    }

    // Обработка специального случая 'z'
    if (len == 4) {
        bool all_zero = true;
        for (size_t i = 0; i < 4; ++i) {
            if (input[i] != 0) {
                all_zero = false;
                break;
            }
        }
        if (all_zero) {
            out.put('z');
            return;
        }
    }

    // Кодирование в ASCII85
    char encoded[5];
    for (int i = 4; i >= 0; --i) {
        encoded[i] = num % 85 + 33;
        num /= 85;
    }

    // Определение длины вывода
    size_t output_len = len == 4 ? 5 : len + 1;
    out.write(encoded, output_len);
}