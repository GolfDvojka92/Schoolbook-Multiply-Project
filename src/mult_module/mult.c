#include "mult.h"

static char in[MAX_DIGITS + 2] = {0};

size_t multiply_arrays(const uint8_t *restrict first, size_t len_first,
                       const uint8_t *restrict second, size_t len_second,
                       uint32_t *restrict out) {
    assert(out != NULL);
    assert(len_first == 0 || first != NULL);
    assert(len_second == 0 || second != NULL);
    assert(len_first < MAX_SAFE_DIGITS || len_second < MAX_SAFE_DIGITS);
    for (size_t i = 0; i < len_first; i++)  assert(first[i] <= 9);
    for (size_t i = 0; i < len_second; i++)  assert(second[i] <= 9);

    // empty operand edge case
    if (len_first == 0 || len_second == 0) {
        out[0] = 0;
        return 1;
    }

    // trimming leading zeroes from operands
    while (len_first > 1 && first[len_first - 1] == 0)  len_first--;
    while (len_second > 1 && second[len_second - 1] == 0)  len_second--;

    // computing max length and zeroing the out buffer
    const size_t total = len_first + len_second;
    for (size_t i = 0; i < total; i++)  out[i] = 0;

    // Accumulating raw column sums without carrying. Each column holds at most
    // min(len_first, len_second) * 81, which means that a single carry pass is
    // fine for up to a ~47.7 million digit shorter operand
    for (size_t i = 0; i < len_first; i++) {
        if (first[i] == 0)  continue;
        uint32_t *row = out + i;
        for (size_t j = 0; j < len_second; j++) {
            row[j] += first[i] * second[j];
        }
    }

    // single carry pass
    uint32_t carry = 0;
    for (size_t i = 0; i < total; i++) {
        uint32_t value = out[i] + carry;
        out[i] = value % 10;
        carry = value / 10;
    }
    // carry is necessarily 0, since the product always fits len_first + len_second digits
    assert(carry == 0);

    // trimming leading zeroes from result
    size_t len_result = total;
    while (len_result > 1 && out[len_result - 1] == 0)  len_result--;

    return len_result;
}

// on READ_FAIL_* *out_len is garbage, only usable on READ_SUCCESS and READ_FAIL_EMPTY
int read_operand(uint8_t *out, size_t *out_len, const char *prompt) {
    for (;;) {
        fputs(prompt, stdout);
        if (!fgets(in, MAX_DIGITS + 2, stdin)) {
            fprintf(stderr, "Input failed!\n");
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
        // looping in this implementation, there is an error code for this edge case which is unused
    }
    assert(out != NULL && out_len != NULL);
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
