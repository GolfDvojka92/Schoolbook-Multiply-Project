#include "mult.h"

static char in[MAX_DIGITS + 2] = {0};

size_t multiply_arrays(const uint8_t *first, size_t first_length,
                       const uint8_t *second, size_t second_length,
                       uint32_t *out) {
    return sizeof(0);
}

// on READ_FAIL_ *out_len is garbage, don't use
int read_operand(uint8_t *out, size_t *out_len, const char *prompt) {
    for (;;) {
        fputs(prompt, stdout);
        if (!fgets(in, MAX_DIGITS + 2, stdin)) {
            printf("Input failed");
            return READ_FAIL_IO;
        }
        char* newline = strchr(in, '\n');
        if (newline) {              // got a full line, success
            *newline = '\0';
            break;
        }
        if (feof(stdin)) break;     // no newline, but EOF, success
        // no newline, no EOF, failure, input too long
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        printf("Operand too long, try again!\n");
    }
    size_t in_len = strlen(in);
    for (size_t i = 0; i < in_len; i++) {
        if (in[i] < '0' || in[i] > '9') {
            return READ_FAIL_NONDIGIT;
        }
        out[in_len - 1 - i] = in[i] - '0';
    }
    *out_len = in_len;
    if (*out_len == 0) {
        return READ_FAIL_EMPTY;
    }
    return READ_SUCCESS;
}
