#include "mult.h"

size_t multiply_arrays(const uint8_t *first, size_t first_length,
                       const uint8_t *second, size_t second_length,
                       uint32_t *out) {
    return sizeof(0);
}

int read_operand(char *in, uint8_t *out, size_t *out_len, const char *prompt) {
    for (;;) {
        fputs(prompt, stdout);
        if (!fgets(in, MAX_DIGITS + 2, stdin)) {
            printf("Input failed");
            return READ_FAILURE;
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
    size_t out_length = strlen(in);
    for (size_t i = 0; i < out_length; i++) {
        if (in[i] < '0' || in[i] > '9') {
            return READ_FAILURE;
        }
        out[out_length - 1 - i] = in[i] - '0';
    }
    return READ_SUCCESS;
}
