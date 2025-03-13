#!/bin/bash

# Переходим в корень проекта
cd "$(dirname "$0")/.." || exit 1

# Компиляция программы
make clean && make

# Проверка существования бинарника
if [ ! -f "./ASCII85_app" ]; then
    echo "Error: ASCII85_app not found!"
    exit 1
fi

# Создаем папку для тестовых данных
mkdir -p test_data || exit 1

# Генерация случайных данных
dd if=/dev/urandom of=test_data/input.bin bs=1K count=1 status=none || exit 1

# Тест 1: Кодирование + декодирование через C++
./ASCII85_app -e < test_data/input.bin > test_data/encoded.a85 || exit 1
./ASCII85_app -d < test_data/encoded.a85 > test_data/decoded.bin || exit 1

# Проверка совпадения данных
cmp test_data/input.bin test_data/decoded.bin || { echo "Test 1 failed"; exit 1; }

# Тест 2: Сравнение с Python
python3 -c "
import base64, os
data = open('test_data/input.bin', 'rb').read()
py_encoded = base64.a85encode(data).decode()
cpp_encoded = open('test_data/encoded.a85', 'rb').read().decode()
assert py_encoded == cpp_encoded, 'Encoding mismatch'
py_decoded = base64.a85decode(cpp_encoded)
assert py_decoded == data, 'Decoding mismatch'
print('Python tests OK')
" || exit 1

# Тест 3: Некорректные данные
echo "InvalidData~" > test_data/invalid.a85 || exit 1
./ASCII85_app -d < test_data/invalid.a85 >/dev/null 2>&1
if [ $? -eq 0 ]; then
    echo "Test 3 failed"
    exit 1
else
    echo "Test 3 passed"
fi

# Очистка
rm -rf test_data
exit 0