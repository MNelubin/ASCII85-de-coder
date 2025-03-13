# ASCII85-de-coder

## 1. Обзор проекта
### 2. Сборка и установка
### 3. Использование
### 4. Тестирование
### 5. Архитектура
### 6. Файловая структура

---

### Обзор проекта

Проект `ASCII85-de-coder` предназначен для кодирования и декодирования данных в формате ASCII85. Он включает в себя модули для кодирования (`encoder.cpp`), декодирования (`decoder.cpp`), а также главную программу (`main.cpp`) для выполнения операций.

---

### Сборка и установка

Для сборки проекта используется Makefile, который настраивается следующим образом:

```makefile
PROJECT = ASCII85_app
LIBPROJECT = $(PROJECT).a
TESTPROJECT = test-$(PROJECT)

# Directories
SRC_DIR = src
TEST_DIR = test
INC_DIR = include

# Tools
CXX = g++
A = ar
AFLAGS = crs

# Flags
CXXFLAGS = -I. -std=c++17 -Wall -g -fPIC -Werror -Wpedantic -Iinclude
LDXXFLAGS = $(CXXFLAGS) -lpthread
LDGTESTFLAGS = $(CXXFLAGS) -lgtest -lgtest_main -lpthread

# Source Files
SRC = $(wildcard $(SRC_DIR)/*.cpp) \
      $(wildcard $(SRC_DIR)/cards/*.cpp) \
      $(wildcard $(SRC_DIR)/player/*.cpp)

# Targets
.PHONY: all test integration-test clean cleanall

all: $(PROJECT)

$(PROJECT): $(APP_OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(APP_OBJ) $(LIBPROJECT) $(LDXXFLAGS)

$(LIBPROJECT): $(LIB_OBJ)
	$(A) $(AFLAGS) $@ $^

$(TESTPROJECT): $(TEST_OBJ) $(LIBPROJECT)
	$(CXX) -o $@ $(TEST_OBJ) $(LIBPROJECT) $(LDGTESTFLAGS)

test: $(TESTPROJECT)
	@echo "Running unit tests..."
	@./$(TESTPROJECT)

integration-test: $(PROJECT) $(TEST_SCRIPT)
	@echo "Running integration tests..."
	@chmod +x $(TEST_SCRIPT)
	@./$(TEST_SCRIPT)

testall: test integration-test
```

Для сборки проекта выполните:

```bash
make
```

---

### Использование

Программа принимает следующие аргументы командной строки:
- `-d`: Режим декодирования
- `-e`: Режим кодирования

Примеры использования:

```bash
# Кодирование данных
./ASCII85_app -e < input.bin > output.a85

# Декодирование данных
./ASCII85_app -d < output.a85 > decoded.bin
```

---

### Тестирование

Для тестирования проекта предусмотрены модульные тесты (`test-ASCII85_app.cpp`) и интеграционные тесты (`test.sh`), которые проверяют корректность кодирования и декодирования данных.

Для запуска тестов выполните:

```bash
make test
./test/test.sh
```

```bash
make testall
```

---

### Архитектура

Проект имеет модульную архитектуру, состоящую из следующих компонентов:
- `encoder.cpp`: Модуль для кодирования данных в формате ASCII85.
- `decoder.cpp`: Модуль для декодирования данных из формата ASCII85.
- `main.cpp`: Главная программа для выполнения кодирования и декодирования.
- `ascii85.h`: Заголовочный файл с объявлениями функций кодирования и декодирования.

---

### Файловая структура

```
ASCII85-de-coder/
├── Makefile
├── README.md
├── include/
│   └── ascii85.h
├── src/
│   ├── decoder.cpp
│   ├── encoder.cpp
│   └── main.cpp
├── test/
│   ├── test-ASCII85_app.cpp
│   └── test.sh
```
