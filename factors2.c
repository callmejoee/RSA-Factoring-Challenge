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
        int n, p, q, i;
        FILE *fp;
        char *line;
        size_t len = 0;
        ssize_t read;
        int max;

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
                n = atoi(line);

                max = my_sqrt(n);

                for (i = 2; i <= max; i++)
                {
                        if (n % i == 0)
                        {
                                q = n / i;
                                p = i;
                                printf("%d = %d*%d\n", n, p, q);
                        }
                }
        }

        free(line);
        fclose(fp);
        return (0);
}
