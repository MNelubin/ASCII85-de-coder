#include "../include/ascii85.h"
#include <iostream>
#include <cmath>
#include <cstdint>

using namespace std;

bool decode(istream& in, ostream& out) {
    const uint32_t POW85[5] = {52200625, 614125, 7225, 85, 1};
    char group[5];
    size_t pos = 0;
    bool is_zero_block = false;

    char c;
    while (in.get(c)) {
        // Пропускаем пробелы
        if (isspace(c)) continue;

        // Обработка 'z'
        if (c == 'z') {
            if (pos != 0 || is_zero_block) return false;
            out.write("\0\0\0\0", 4);
            is_zero_block = true;
            continue;
        }

        // Проверка допустимости символа
        if (c < '!' || c > 'u') return false;

        group[pos++] = c;
        is_zero_block = false;

        // Когда набрано 5 символов
        if (pos == 5) {
            uint32_t num = 0;
            for (int i = 0; i < 5; ++i) {
                num += (group[i] - 33) * POW85[i];
            }

            // Извлекаем байты через деление
            uint8_t bytes[4];
            bytes[0] = num / 16777216;          // 256^3
            bytes[1] = (num / 65536) % 256;     // 256^2
            bytes[2] = (num / 256) % 256;       // 256^1
            bytes[3] = num % 256;               // 256^0

            out.write(reinterpret_cast<char*>(bytes), 4);
            pos = 0;
        }
    }

    // Обработка остатка
    if (pos > 0) {
        if (pos < 2) return false;

        // Дополняем группу до 5 символов
        while (pos < 5) group[pos++] = 'u';

        uint32_t num = 0;
        for (int i = 0; i < 5; ++i) {
            num += (group[i] - 33) * POW85[i];
        }

        // Вычисляем количество байт: pos - 1
        uint8_t bytes[4];
        bytes[0] = num / 16777216;
        bytes[1] = (num / 65536) % 256;
        bytes[2] = (num / 256) % 256;
        bytes[3] = num % 256;

        out.write(reinterpret_cast<char*>(bytes), pos - 1);
    }

    return true;
}