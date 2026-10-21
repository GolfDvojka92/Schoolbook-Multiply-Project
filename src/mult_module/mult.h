// Schoolbook multiplication of two LSD-first base-10 digit arrays
//
//  first, len_first     : first operand array and its length
//  second, len_second   : second operand array and its length
//  out                     : result buffer, must be len_first + len_second elements 
//                            wide, also base-10 LSD-first, must not overlap first or second
//
// Returns resulting number of digits in out buffer, excluding leading
// zeroes, minimum 1, zero product returns 1 with out[0] == 0
//
// This implementation uses uint32_t as the width of the out buffer to account
// up to a theoretical ~47.7 million digit number multiplication, MAX_DIGITS is
// set inside the header and should be set according to necessary use case.

#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>
#include <assert.h>

#define MAX_DIGITS           4096
#define MAX_SAFE_DIGITS      47721858u
static_assert(MAX_DIGITS <= MAX_SAFE_DIGITS, "MAX_DIGITS exceeds uint32_t carry-pass limit");

#define READ_SUCCESS         1
#define READ_FAIL_IO         0
#define READ_FAIL_TOO_LONG  -1
#define READ_FAIL_NONDIGIT  -2
#define READ_FAIL_EMPTY     -3

// out must be (first_length + second_length) * uint32_t size
// returns number of digits of the product, with trimmed leading zeroes
size_t multiply_arrays(const uint8_t *restrict first, size_t first_length,
                       const uint8_t *restrict second, size_t second_length,
                       uint32_t *restrict out);

// This implementation also includes a read_operand() function that takes properly
// formatted user input and stores it into a forwarded uint8_t array, if appropriately sized.

// out must be MAX_DIGITS * uint8_t size
// returns one of the READ_* macros
int read_operand(uint8_t* out, size_t* out_len, const char* prompt);
