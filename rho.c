#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>
#include "factor.h"

uint64_t gcd(uint64_t a, uint64_t b)
{
    if (b == 0) {
        return a;
    }
    return gcd(b, a % b);
}


uint64_t modular_pow(uint64_t base, int exponent, uint64_t modulus)
{
    uint64_t result = 1;
    while (exponent > 0)
    {
        if (exponent & 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

uint64_t PollardRho(uint64_t n)
{
    srand (time(NULL));
    if (n == 1)
        return n;
    if (n % 2 == 0)
        return 2;
    uint64_t x = (rand() % (n - 2)) + 2;
    uint64_t y = x;
    uint64_t c = (rand() % (n - 1)) + 1;
    uint64_t d = 1;
    while (d == 1)
    {
        x = (modular_pow(x, 2, n) + c + n) % n;
        y = (modular_pow(y, 2, n) + c + n) % n;
        y = (modular_pow(y, 2, n) + c + n) % n;
        d = gcd(abs(x - y), n);
        if (d == n)
            return PollardRho(n);
    }
    return d;
}
