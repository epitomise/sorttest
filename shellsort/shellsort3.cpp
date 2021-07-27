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

void shellsort(int* a, int p, int r)
{
    if (p >= r) return;
    int h, i, j, x, n;
    int arr[] = {0,1,5,19,41,109,209,505,929,2161,3905,8929,16001,36289,64769,
                 146305,260609,587521,1045505,2354689,4188161,9427969};
    int dh = sizeof(arr) / sizeof(arr[0]) - 1;    
    n = r - p + 1;
    while (arr[dh] > n) --dh;
    h = arr[dh];
    while (h >= 1)
    {
        for (i = h + p; i <= r; ++i)
        {
            x = a[i];
            for (j = i - h; j >= p && a[j] > x; j -= h)
                a[j + h] = a[j];
            a[j + h] = x;
        }
        h = arr[--dh];
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
        shellsort(a, 1, n);
        gettimeofday(&endtime, 0);
        timeuse += 1000000 * (endtime.tv_sec - starttime.tv_sec) + (endtime.tv_usec - starttime.tv_usec);
        assert(std::is_sorted(a + 1, a + n));
    }
    std::cout << timeuse / M << std::endl;
    return 0;
}

