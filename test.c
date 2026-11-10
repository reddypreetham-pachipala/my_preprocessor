#include<stdio.h>

#define ADD(a,b) ((a)+(b))
#define MUL(a,b) ((a)*(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define PF printf

int main()
{
    int x = 10, y = 20;

    // perform operations

    int s = ADD(x,y);
    int p = MUL(x,y);

    /*
       find maximum
    */

    int m = MAX(x,y);

    PF("Sum = %d\n", s);
    PF("Product = %d\n", p);
    PF("Max = %d\n", m);
}
