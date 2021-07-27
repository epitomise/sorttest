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
int a[N + 1], f[N + 1];

void init(int *a, int *f, int p, int r)
{
    for (int i = p; i <= r; ++i)
        a[i] = f[i];
}

void heapify(int* a, int i, int p, int b)
{
    int t;
    int x = a[i];
    int k = i;
    int c = 2 * k - p + 1;
    while (c <= b)
    {
        if (c + 1 <= b && a[c + 1] > a[c])
            ++c;
        if (x > a[c]) break;
        a[k] = a[c];
        k = c;
        c = 2 * k - p + 1;
    }
    a[k] = x;
}

void heapsort(int* a, int p, int r)
{
    int i, x, t;
    x = (r - p + 1) / 2;
    for (i = p + x; i >= p; --i)
        heapify(a, i, p, r);
    for (i = r; i > p; --i)
    {
        t = a[p];
        a[p] = a[i];
        a[i] = t;
        heapify(a, p, p, i - 1);
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
        heapsort(a, 1, n);
        gettimeofday(&endtime, 0);
        timeuse += 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        assert(std::is_sorted(a + 1, a + n));
    }
    std::cout << timeuse / M << std::endl;
    return 0;
}

