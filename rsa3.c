#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

bool is_prime(int n) {
    if (n <= 1) {
        return false;
    }
    else if (n <= 3) {
        return true;
    }
    else if (n % 2 == 0 || n % 3 == 0) {
        return false;
    }
    int i = 5;
    while (i * i <= n) {
        if (n % i == 0 || n % (i + 2) == 0) {
            return false;
        } 
        i += 6;
    }
    return true;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: rsa <file>\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        uint64_t num = strtoull(line, NULL, 10);
        if (num <= ULLONG_MAX) {
            // use simple algorithm for small numbers
            uint64_t p;
            for (p = 2; p <= sqrt(num); p++) {
                if (num % p == 0) {
                    uint64_t q = num / p;
                    if (is_prime(q) && is_prime(p)) {
                        printf("%llu=%llu*%llu\n", num, q, p);
                        break;
                    }
                }
            }
        } else {
            printf("%llu is too large to factor with this algorithm.\n", num);
        }
    }
    fclose(file);
    return 0;
}
