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
const int CUTOFF = 20;
int a[N + 1], f[N + 1];

void init(int *a, int *f, int p, int r)
{
    for (int i = p; i <= r; ++i)
        a[i] = f[i];
}

void insertsort(int* a, int p, int r)
{
    int i, j, x;
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
            for (j = i - 1; a[j] > x; --j)
                a[j + 1] = a[j];
            a[j + 1] = x;
        }
    }
}

void quicksort(int* a, int p, int r)
{    
    if (p + CUTOFF < r)
    {
        int i = p, j = r, x = a[p];
        while (i < j)
        {
            while (i < j && a[j] >= x) --j;
            if (i < j) a[i++] = a[j];
            while (i < j && a[i] < x) ++i;
            if (i < j) a[j--] = a[i];
        }
        a[i] = x;
        quicksort(a, p, i - 1);
        quicksort(a, i + 1, r);
    }
    else insertsort(a, p, r);
}

int main(int argc, char **argv)
{
    int i, n, m, x, timeuse = 0;
    struct timeval starttime, endtime;
    srand((unsigned)time(NULL));
    if (argc < 2) n = 1000000;
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
        quicksort(a, 1, n);
        gettimeofday(&endtime, 0);
        timeuse += 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        assert(std::is_sorted(a + 1, a + n));
    }
    std::cout << timeuse / M << std::endl;
    return 0;
}

