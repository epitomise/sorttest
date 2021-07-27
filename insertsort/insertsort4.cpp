#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <sys/time.h>
#include <assert.h>

const int N = 10000000;
const int M = 10;
int a[N + 1], f[N + 1], aux[N + 1];

void init(int *a, int *f, int p, int r)
{
    for (int i = p; i <= r; ++i)
        a[i] = f[i];
}

void insertsort(int* a, int p, int r)
{
    int i, j, x;
    int lo, hi, mid;
    for (i = p + 1; i <= r; ++i)
    {
        x = a[i];
        if (x <= a[p])
        {
            for (j = i - 1; j > p; --j)
                a[j + 1] = a[j];
            a[p] = x;
        }
        else
        {
            x = a[i];
            lo = p + 1;
            hi = i;        
            while (lo < hi)
            {
                mid = (lo + hi) / 2;
                if (x < a[mid]) hi = mid;
                else lo = mid + 1;
            }
            for (j = i - 1; j >= lo; --j)
                a[j + 1] = a[j];
            a[lo] = x;
        }
    }
}

int main(int argc, char **argv)
{
    int i, n, m, x, timeuse = 0;
    struct timeval starttime, endtime;
    srand((unsigned)time(NULL));
    if (argc < 2) n = 10000;
    else n = atoi(argv[1]);
    assert(n > 0 && n <= N);
    if (argc < 3) m = M;
    else m = atoi(argv[2]);
    assert(m > 0);
    for (i = 1; i <= n; ++i)
    {
        x = rand() % 10000 * 10000;
        f[i] = x + rand() % 10000;
        //f[i] = n - i;
    }
    for (i = 1; i <= m; ++i)
    {
        init(a, f, 1, n);
        gettimeofday(&starttime, 0);
        insertsort(a, 1, n);
        gettimeofday(&endtime, 0);
        timeuse += 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        assert(std::is_sorted(a + 1, a + n));
    }
    std::cout << timeuse / M << std::endl;
    return 0;
}

