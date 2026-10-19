#include "mult_module/mult.h"

#define PROMPT_FIRST    "First operand: (digits only, max " STR(MAX_DIGITS) "): "
#define PROMPT_SECOND   "Second operand: (digits only, max " STR(MAX_DIGITS) "): "
#define READ_FAILURE_MSG    "Read failed, exiting program\n"

static uint8_t  first[MAX_DIGITS]       = {0};
static uint8_t  second[MAX_DIGITS]      = {0};
static char     buffer[MAX_DIGITS + 2];

int main() {
    size_t first_len;
    size_t second_len;
    if (!read_operand(buffer, first, &first_len, PROMPT_FIRST)) {
        printf(READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    if (!read_operand(buffer, second, &second_len, PROMPT_SECOND)) {
        printf(READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    uint32_t result[first_len + second_len];
    return 0;
}

