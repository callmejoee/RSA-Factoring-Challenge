#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <gmp.h>

void factorize(mpz_t n) {
    mpz_t p, q;
    mpz_inits(p, q, NULL);
    mpz_set_ui(p, 2);
    while (mpz_cmp(p, n) <= 0) {
        if (mpz_divisible_p(n, p)) {
            mpz_divexact(q, n, p);
            gmp_printf("%Zd=%Zd*%Zd\n", n, q, p);
            break;
        }
        mpz_nextprime(p, p);
    }
    mpz_clears(p, q, NULL);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: factors <file>\n");
        return 1;
    }
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    char line[100];
    while (fgets(line, sizeof(line), file) != NULL) {
        unsigned long long num = strtoull(line, NULL, 10);
        if (num <= ULLONG_MAX) {
            // use simple algorithm for small numbers
            unsigned long long p;
            for (p = 2; p <= num; p++) {
                if (num % p == 0) {
                    unsigned long long q = num / p;
                    printf("%llu=%llu*%llu\n", num, q, p);
                    break;
                }
            }
        } else {
            // use GMP library for large numbers
            mpz_t num_gmp;
            mpz_init_set_str(num_gmp, line, 10);
            factorize(num_gmp);
            mpz_clear(num_gmp);
        }
    }
    fclose(file);
    return 0;
}
