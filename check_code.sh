#!/bin/bash

# Проверка форматирования с помощью clang-format
find ./src ./include -name "*.cpp" -o -name "*.h" | xargs clang-format -i

# Путь к compile_commands.json
COMPILE_COMMANDS_PATH="./build/compile_commands.json"

# Проверка наличия compile_commands.json
if [ ! -f "$COMPILE_COMMANDS_PATH" ]; then
    echo "Error: compile_commands.json not found in build directory."
    exit 1
fi

# Запуск clang-tidy на всех файлах проекта с использованием compile_commands.json и исправлением ошибок
find ./src ./include -name "*.cpp" | xargs clang-tidy -p "$COMPILE_COMMANDS_PATH" --fix --warnings-as-errors=*
