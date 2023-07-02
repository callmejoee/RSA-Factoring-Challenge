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
    mpz_t num;
    mpz_init(num);
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
        mpz_set_str(num, line, 10);
        factorize(num);
    }
    mpz_clear(num);
    fclose(file);
    return 0;
}
