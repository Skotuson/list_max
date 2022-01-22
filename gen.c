#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int generateArray ( int nr ) {
    printf( "nr = %d;\n", nr );
    int max = 0;
    int n = 0;
    for ( int i = 0; i < nr; i++ ) {
        n = rand();
        if ( n > max )
            max = n;
        printf( "x[%d] = parseList ( \"%d\" );\n", i, n );
    }
    return max;
}

int main ( void ) {
    srand( time(NULL) );
    int i = 30;
    int max = 0;
    while ( i-- ) {
        max = generateArray ( rand() % 150 );
        printf( "test_max ( parseList ( \"%d\" ), maxOf ( x, nr ) );\n", max );
        printf( "deleteListArr ( x, nr );\n\n");
    }
    return 0;
}