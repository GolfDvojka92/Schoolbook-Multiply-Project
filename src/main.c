#include "mult_module/mult.h"

#define STR_(x) #x
#define STR(x) STR_(x)

#define PROMPT_FIRST        "First operand: (digits only, max " STR(MAX_DIGITS) "): "
#define PROMPT_SECOND       "Second operand: (digits only, max " STR(MAX_DIGITS) "): "
#define READ_FAILURE_MSG    "Read failed, exiting program\n"

static uint8_t first[MAX_DIGITS]       = {0};
static uint8_t second[MAX_DIGITS]      = {0};
static uint32_t result[2 * MAX_DIGITS] = {0};

int main(void)
{
    size_t len_first = 0;
    size_t len_second = 0;
    if (read_operand(first, &len_first, PROMPT_FIRST) != READ_SUCCESS)
    {
        fprintf(stderr, READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    assert(len_first >= 1 && len_first <= MAX_DIGITS);
    if (read_operand(second, &len_second, PROMPT_SECOND) != READ_SUCCESS)
    {
        fprintf(stderr, READ_FAILURE_MSG);
        exit(EXIT_FAILURE);
    }
    assert(len_second >= 1 && len_second <= MAX_DIGITS);
    
    size_t len_result = multiply_arrays(first, len_first, second, len_second, result);
    assert(len_result >= 1 && len_result <= len_first + len_second);
    assert(len_result == 1 || result[len_result - 1] != 0);
    for (size_t i = 0; i < len_result; i++) assert(result[i] <= 9);
    printf("Result: ");
    for (size_t i = 0; i < len_result; i++)
    {
        printf("%d", result[len_result - 1 - i]);
    }
    printf("\n");
    return 0;
}

