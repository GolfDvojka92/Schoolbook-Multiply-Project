#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>

#define STR_(x) #x
#define STR(x) STR_(x)
#define MAX_DIGITS 2048
#define READ_SUCCESS 1
#define READ_FAILURE 0

// out must be (first_length + second_length) * uint32_t size
// returns size of out
size_t multiply_arrays(const uint8_t* first, const size_t first_length,
                       const uint8_t* second, const size_t second_length,
                       uint32_t* out);

// reusable function for reading an operand from stdin and storing it into an array
// returns 1 for success, 0 for failure
int read_operand(char* in, uint8_t* out, size_t* out_len, const char* prompt);
