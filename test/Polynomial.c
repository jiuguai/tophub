#include <stdio.h>
#include <time.h>
#include <math.h>
#define MAXN 1000
#define MAXK 1e6

clock_t start, stop;

double f(int n, double a[], double x);
double f1(int n, double a[], double x);
void ct(double (*func)(int, double*, double),int n, double a[], double x);

int main()
{   
    double a[MAXN];
    for(int i=0; i<MAXN; i++) a[i] = (double)i;

    printf("f :");
    ct(f, MAXN-1, a, 2);
    printf("f1:");
    ct(f1, MAXN-1, a, 2);
    // start = clock();
    
    // double x = f(MAXN, a, 2);
    // printf("%6.2e\n", x);
    // stop = clock();
    // duration = ((double)(stop-start))/CLK_TCK;

    // printf("%fs\n", duration);

    return 0;
}



double f(int n, double a[], double x)
{
    int i;
    double p = a[0];
    for ( i=1; i<=n; i++)
        p += (a[i]*pow(x,i));

    return p;

}
double f1(int n, double a[], double x)
{
    int i;
    double p = a[n];
    for ( i=n; i>0; i--)
        p += a[i-1] + x*p;

    return p;

}

void ct(double (*func)(int, double*, double),int n, double a[], double x)
{
    start = clock();
    for( int i=0; i<MAXK; i++){
        func(n, a, x);
    }
    stop = clock();
    double task = ((double)(stop-start))/CLK_TCK;
    double duration = task/MAXK;
    printf("task:%fs\n", task);
    printf("duration:%fs\n", duration);
}
