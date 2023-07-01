#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double my_sqrt(double x) {
    double guess = x / 2.0;
    double prev_guess = 0.0;
    double diff = 1.0;

    while (diff > 0.000001) {
        prev_guess = guess;
        guess = (guess + x / guess) / 2.0;
        diff = fabs(guess - prev_guess);
    }

    return guess;
}

int main(int argc, char *argv[])
{
        long long unsigned n, p, q;
        FILE *fp;
        char *line;
        size_t len = 0;
        ssize_t read;

        if (argc != 2)
        {
                printf("factors <file>");
                return (0);
        }

        fp = fopen(argv[1], "r");

        if (fp == NULL)
        {
                printf("Error opening file.\n");
                return 1;
        }

        while((read = getline(&line, &len, fp) != -1))
        {
                n = strtoull(line, NULL, 10);

                for (p = 2; p <= n; p++)
                {
                        if (n % p == 0)
                        {
                                q = n / p;
                                printf("%llu = %llu*%llu\n", n, p, q);
                                break;
                        }
                }
        }

        free(line);
        fclose(fp);
        return (0);
}
