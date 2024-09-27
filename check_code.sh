#!/bin/bash

find ./src ./include -name "*.cpp" -o -name "*.h" | xargs clang-format -i

COMPILE_COMMANDS_PATH="./build/compile_commands.json"

if [ ! -f "$COMPILE_COMMANDS_PATH" ]; then
    echo "Error: compile_commands.json not found in build directory."
    exit 1
fi

find ./src ./include -name "*.cpp" | xargs clang-tidy -p "$COMPILE_COMMANDS_PATH" --fix --warnings-as-errors=*
