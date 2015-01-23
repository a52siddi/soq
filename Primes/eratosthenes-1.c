#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>

enum { MAX_PRIME = 1000000000 };
static char sieve[MAX_PRIME/2];

int main(int argc, char **argv)
{
    int i;
    int max = MAX_PRIME;
    uint64_t sum = 2;
    uint64_t cnt = 1;

    if (argc > 1)
        max = atoi(argv[1]);
    if (max > MAX_PRIME)
    {
        max = MAX_PRIME;
        printf("Reset max to %d\n", max);
    }

    printf("2\n");
    int sqrt_max = sqrt(max);

    for (i = 3; i <= sqrt_max; i += 2)
    {
        if (sieve[i/2] == 0)
        {
            sum += i;
            cnt++;
            printf("%d\n", i);
            for (int j = i + i + i; j < max; j += i + i)
                sieve[j/2] = 1;
        }
    }

    for ( ; i < max; i += 2)
    {
        if (sieve[i/2] == 0)
        {
            sum += i;
            cnt++;
            printf("%d\n", i);
        }
    }

    printf("Sum   of primes to %d = %" PRIu64 "\n", max, sum);
    printf("Count of primes to %d = %" PRIu64 "\n", max, cnt);
    return 0;
}