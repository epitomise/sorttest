#include <iostream>
#include <vector>
#include <cstdlib>
#include <algorithm>
#include <cmath>
#include <ctime>
#include <sys/time.h>
using namespace std;
const int n = 2000000;
int a[n + 1], b[n + 1], c[n + 1];
void insertsort(int* a, int p, int r)
{
    int i, j, x;
    for (i = p + 1; i <= r; ++i)
    {
        x = a[i];
        if (a[i] <= a[p])
        {
            for (j = i - 1; j >= 1; --j)
                a[j + 1] = a[j];
            a[p] = x;
        }
        else
        {
            j = i - 1;
            while (a[j] > x)
            {
                a[j + 1] = a[j];
                --j;
            }
            a[j + 1] = x;
        }
    }
}
void heapify(int* a, int i, int p, int len)
{
    int largest, t;
    int l = 2 * (i - p + 1) + p - 1;
    int r = l + 1;
    if (l <= len && a[l] > a[i])
        largest = l;
    else largest = i;
    if (r <= len && a[r] > a[largest])
        largest = r;
    while (largest != i)
    {
        t = a[i];
        a[i] = a[largest];
        a[largest] = t;
        i = largest;
        l = 2 * (i - p + 1) + p - 1;
        r = l + 1;
        if (l <= len && a[l] > a[i])
            largest = l;
        else largest = i;
        if (r <= len && a[r] > a[largest])
            largest = r;
    }
}
void heapsort(int* a, int p, int len)
{
    int i, x, t;
    x = len / 2;
    for (i = x; i >= 1; --i)
        heapify(a, i + p - 1, p, x);
    for (i = len; i >= 2; --i)
    {
        t = a[p];
        a[p] = a[i];
        a[i] = t;
        len = len - 1;
        heapify(a, p, p, len);
    }
}
void quicksort1(int* a, int p, int r, int d)
{
    if (p + 32 < r)
    {
        if (d > 0)
        {
            int x = a[r];
            int i = p;
            int j, t;
            --d;
            for (j = p; j < r; ++j)
                if (a[j] <= x)
                {
                    t = a[i];
                    a[i] = a[j];
                    a[j] = t;
                    ++i;
                }
            t = a[i];
            a[i] = a[r];
            a[r] = t;
            quicksort1(a, p, i - 1, d);
            quicksort1(a, i + 1, r, d);
        }
        else
        {
            heapsort(a, p, r);
        }
    } 
}
int mycomp(const void *a, const void *b){
     int *numa = (int *)a, *numb = (int *)b;
    return *numa - *numb;
}
int main()
{
    int i, x, d, timeuse;
    struct timeval starttime, endtime;
    srand((unsigned)time(NULL));
    for (i = 1; i <= n; i++)
    {
        x = rand() % 10000 * 10000;
        a[i] = x + rand() % 10000;
        //a[i] = n - i;
        b[i] = a[i];
        c[i] = a[i];
    } 
    gettimeofday(&starttime,0);
    sort(c, c+n);
    //qsort(c, n, sizeof(int), mycomp);
    gettimeofday(&endtime,0);
    timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    cout << timeuse/1000 << endl;

    gettimeofday(&starttime,0);
    heapsort(b, 1, n);
    gettimeofday(&endtime,0);
    timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    cout << timeuse/1000 << endl;

    gettimeofday(&starttime,0);
    d = (int)(ceil(3 * log(n) / log(2)) + 0.0001);
    quicksort1(a, 1, n, d);
    insertsort(a, 1, n);
    gettimeofday(&endtime,0);
    timeuse  = 1000000*(endtime.tv_sec - starttime.tv_sec) + endtime.tv_usec - starttime.tv_usec;
    cout << timeuse/1000 << endl;
    
    return 0;
}
