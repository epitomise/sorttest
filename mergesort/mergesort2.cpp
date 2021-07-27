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

void merge(int *a, int lo, int mid, int hi)
{
    int i = lo, j = mid + 1, k;
    for (k = lo; k <= hi; ++k)
        aux[k] = a[k];
    for (k = lo; k <= hi; ++k)
        if (i > mid) a[k] = aux[j++];
        else if (j > hi) a[k] = aux[i++];
        else if (aux[j] < aux[i]) a[k] = aux[j++];
        else a[k] = aux[i++];
}

void mergesort(int* a, int p, int r)
{    
    if (p >= r) return;
    int lo, mid, hi, len, n;
    n = r - p + 1;
    for (len = 1; len < n; len += len)
        for (lo = p; lo <= r - len; lo += len + len)
            {
                mid  = lo + len - 1;
                hi = lo + len + len - 1;
                if (hi > r) hi = r;
                merge(a, lo, mid, hi);
            }
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
        mergesort(a, 1, n);
        gettimeofday(&endtime, 0);
        timeuse += 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        assert(std::is_sorted(a + 1, a + n));
    }
    std::cout << timeuse / M << std::endl;
    return 0;
}

