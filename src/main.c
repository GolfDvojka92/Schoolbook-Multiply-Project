#include "mult_module/mult.h"
#include <stdio.h>

#define PROMPT_FIRST        "First operand: (digits only, max " STR(MAX_DIGITS) "): "
#define PROMPT_SECOND       "Second operand: (digits only, max " STR(MAX_DIGITS) "): "
#define READ_FAILURE_MSG    "Read failed, exiting program\n"

static uint8_t first[MAX_DIGITS]       = {0};
static uint8_t second[MAX_DIGITS]      = {0};

int main() {
    size_t len_first;
    size_t len_second;
    if (!read_operand(first, &len_first, PROMPT_FIRST)) {
        printf(READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    if (!read_operand(second, &len_second, PROMPT_SECOND)) {
        printf(READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    uint32_t result[len_first + len_second];
    size_t len_result = multiply_arrays(first, len_first, second, len_second, result);
    return 0;
}

