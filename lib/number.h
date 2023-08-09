#pragma once
#include <cinttypes>
#include <iostream>

const uint8_t BYTE_MOVE = 8;
const uint8_t MAX_VALUE = 0xff;
const uint16_t BASE = 256;
const uint8_t ARR_SIZE = 253;
const uint16_t MAX_DEC_SIZE = 609;

struct uint2022_t {
    uint8_t data[ARR_SIZE] = {0};
};

static_assert(sizeof(uint2022_t) <= 300, "Size of uint2022_t must be no higher than 300 bytes");

uint2022_t from_uint(uint32_t i);

uint2022_t from_string(const char* buff);

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs);

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs);

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs);

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value);
