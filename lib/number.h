#pragma once
#include <cinttypes>
#include <iostream>

const int mod = 1000000000;
const int int_amount = 68;

struct uint2022_t {
public:

    uint2022_t() : 
        length(1), 
        arr(new uint32_t[int_amount]) 
    {
        for (int i = 0; i < int_amount; ++i) { arr[i] = 0; } // Here 68 must be
    }
    

    int length;
    uint32_t* arr;
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
