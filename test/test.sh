#!/bin/bash

# Компиляция программы
cd ..
make
cd test

# Генерация случайных данных
dd if=/dev/urandom of=test_input.bin bs=1K count=1

# Тест 1: Кодирование + декодирование через C++
".././ASCII85_app" -e < test_input.bin > encoded.a85
".././ASCII85_app" -d < encoded.a85 > decoded.bin

# Проверка совпадения исходных и декодированных данных
cmp test_input.bin decoded.bin || echo "Test 1 failed"

# Тест 2: Сравнение с Python
python3 -c "
import base64, sys

# Читаем исходные данные
with open('test_input.bin', 'rb') as f:
    data = f.read()

# Кодируем через Python
py_encoded = base64.a85encode(data, adobe=False).decode()

# Читаем результат C++
with open('encoded.a85', 'rb') as f:
    cpp_encoded = f.read().decode()

# Проверяем совпадение
assert py_encoded == cpp_encoded, 'Encoded data mismatch'

# Декодируем через Python
py_decoded = base64.a85decode(cpp_encoded, adobe=False)

# Проверяем совпадение с исходными данными
assert py_decoded == data, 'Decoded data mismatch'

print('All tests passed!')
"

# Тест 3: Некорректные данные
echo -n "InvalidData~" > invalid.a85
./ascii85 -d < invalid.a85 >/dev/null 2>&1
[ $? -ne 0 ] && echo "Test 3 passed"

# Очистка
rm test_input.bin encoded.a85 decoded.bin invalid.a85