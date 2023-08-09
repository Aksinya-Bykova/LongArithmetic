#include "number.h"

uint2022_t from_uint(uint32_t i) {
    uint2022_t t;
    t.data[0] = i & MAX_VALUE;
    t.data[1] = (i >> BYTE_MOVE) & MAX_VALUE;
    t.data[2] = (i >> (2 * BYTE_MOVE)) & MAX_VALUE;
    t.data[3] = i >> (3 * BYTE_MOVE);

    return t;
}

bool operator<(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int iter = ARR_SIZE - 1; iter >= 0; --iter) {
        if (lhs.data[iter] > rhs.data[iter]) {
            return false;
        }
        if (lhs.data[iter] < rhs.data[iter]) {
            return true;
        }
    }

    return false;
}

bool operator==(const uint2022_t& lhs, const uint2022_t& rhs) {
    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        if (lhs.data[iter] != rhs.data[iter]) {
            return false;
        }
    }

    return true;
}

bool operator!=(const uint2022_t& lhs, const uint2022_t& rhs) {
    return !(lhs == rhs);
}

uint8_t size2022_t(const uint2022_t i) {
    uint8_t s = 0;

    for (int iter = ARR_SIZE - 1; iter >= 0; --iter) {
        if (i.data[iter] != 0) {
            s = iter;
            break;
        }
    }

    return s + 1;
}

uint2022_t operator*(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t t = from_uint(0);
    uint16_t s = 0;

    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        s = s / BASE;
        t.data[iter] = t.data[iter] + s;

        for (int jter = 0; jter < iter + 1; ++jter) {
            t.data[iter] += lhs.data[jter] * rhs.data[iter - jter];
            s += lhs.data[jter] * rhs.data[iter - jter];
        }
    }

    return t;
}

uint2022_t operator*(const uint2022_t& lhs, const uint32_t& rhs) {
    uint2022_t t = from_uint(0);
    uint16_t s = 0;

    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        t.data[iter] = lhs.data[iter] * rhs + s;
        s = (lhs.data[iter] * rhs + s) / BASE;
    }

    return t;
}

uint2022_t operator+(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t t = from_uint(0);
    uint8_t s = 0;

    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        t.data[iter] = lhs.data[iter] + rhs.data[iter] + s;
        s = (lhs.data[iter] + rhs.data[iter] + s) / BASE;
    }

    return t;
}

uint2022_t operator-(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t t = from_uint(0);
    uint8_t s = 0;

    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        t.data[iter] = lhs.data[iter] - rhs.data[iter] - s + BASE;
        s = (MAX_VALUE - lhs.data[iter] + rhs.data[iter] + s) / BASE;
    }

    return t;
}

uint2022_t operator/(const uint2022_t& lhs, const uint2022_t& rhs) {
    uint2022_t t = from_uint(0);

    if (lhs < rhs || rhs == from_uint(0)) {
        return from_uint(0);
    }

    uint2022_t lhs_copy = lhs;
    uint2022_t ans_reversed;
    int ans_len = 0;
    uint8_t shift = 0;

    for (int iter = size2022_t(lhs) - 1; iter >= 0; --iter) {
        uint2022_t c = from_uint(0);

        for (int jter = size2022_t(lhs_copy) - 1; jter >= 0; --jter) {
            c = c * BASE + from_uint(lhs_copy.data[jter]);
            ++shift;
            if (!(c < rhs)) {
                break;
            }
        }

        uint8_t times = 0;

        while (!(c < rhs)) {
            c = c - rhs;
            ++times;
        }

        ans_reversed.data[ans_len] = times;
        ++ans_len;

        uint2022_t order = from_uint(0);
        order.data[size2022_t(lhs_copy) - 1] = 1;
        if (!(lhs_copy < (lhs_copy - order * rhs * times))) {
            lhs_copy = lhs_copy - order * rhs * times;
        } else {
            break;
        }
    }

    for (int iter = ans_len - 1; iter >= 0; --iter) {
        t.data[ans_len - 1 - iter] = ans_reversed.data[iter];
    }

    return t;
}

uint2022_t from_string(const char* buff) {
    uint2022_t t = from_uint(0);
    int len = 0;

    for (int iter = 0; iter < ARR_SIZE; ++iter) {
        if ((buff[iter] >= '0') && (buff[iter] <= '9')) {
            ++len;
        } else {
            break;
        }
    }

    uint2022_t c = from_uint(1);

    for (int iter = len - 1; iter >= 0; --iter) {
        t = t + c * static_cast<int>(buff[iter] - '0');
        c = c * 10;
    }

    return t;
}

std::ostream& operator<<(std::ostream& stream, const uint2022_t& value) {
    uint2022_t t = value;
    uint8_t dec_v[MAX_DEC_SIZE];
    uint32_t len = 0;

    for (int iter = 0; iter < MAX_DEC_SIZE; ++iter) {
        dec_v[iter] = (t - (t / from_uint(10)) * 10).data[0];
        t = t / from_uint(10);
        ++len;
        if (t == from_uint(0)) {
            break;
        }
    }

    for (int iter = len - 1; iter >= 0; --iter) {
        stream << static_cast<int>(dec_v[iter]);
    }

    return stream;
}
