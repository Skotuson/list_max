#include <stdio.h>
#include <stdlib.h>

int g_Ok = 0, g_Fail = 0;

typedef struct TItem {
    struct TItem * next;
    char digit;
} TITEM;

TITEM * createNode ( char digit, TITEM * next ) {
    TITEM * node = ( TITEM* ) malloc ( sizeof ( TITEM ) );
    node -> digit = digit;
    node -> next = next;
    return node;
}

void deleteList ( TITEM * head ) {
    while ( head ) {
        TITEM * tmp = head -> next;
        free ( head );
        head = tmp;
    }
}

void printList ( TITEM * head ) {
    while ( head ) {
        printf( "%c -> ", head -> digit );
        head = head -> next;
    }
    printf("\n");
}

void deleteListArr ( TITEM ** x, int nr ) {
    while ( nr-- )
        deleteList ( x[nr] );
}

TITEM * parseList ( const char * str ) {
    TITEM * head = NULL;
    while ( *str ) {
        head = createNode ( *str, head );
        str++;
    }
    return head;
}

int getListLength ( TITEM * head ) {
    int cnt = 0;
    while ( head ) {
        cnt++;
        head = head -> next;
    }
    return cnt;
}

int * listToArr ( TITEM * a, int len ) {
    int * arr = ( int* ) malloc ( len * sizeof( *arr ) );
    int cnt = 0;
    while ( a ) {
        arr[cnt++] = a -> digit - '0';
        a = a -> next;
    }
    return arr;
}

TITEM * compareLists ( TITEM * a, TITEM * b ) {
    int lenA = getListLength ( a ), lenB = getListLength ( b );
    int * arrA = listToArr ( a, lenA );
    int * arrB = listToArr ( b, lenB );
    TITEM * r = NULL;
    int min = lenA < lenB ? lenA : lenB;
    if ( lenA != lenB ) {
        int diff = abs ( lenA - lenB );
        TITEM * maxList = lenA > lenB ? a : b;
        int * maxArr = lenA > lenB ? arrA : arrB;
        while ( diff-- ) {
            if ( maxArr[min + diff] > 0 ) {            
                free ( arrA );
                free ( arrB );
                return maxList;
            }
        }
    }
    while ( min-- ) {
        if ( arrA[min] < arrB[min] ) {
            r = b;
            break;
        }
        else if ( arrA[min] > arrB[min] ) {
            r = a;
            break;
        }
    }
    free ( arrA );
    free ( arrB );
    return r;
}

TITEM * maxOf ( TITEM ** x, int nr ) {
    TITEM * max = x[0];
    for ( int i = 1; i < nr; i++ ) 
        max = compareLists ( max, x[i] );
    return max;
}

int compare ( TITEM * a, TITEM * b ) {
    if ( getListLength ( a ) != getListLength ( b ) )
        return 0;
    while ( a ) {
        if ( a -> digit != b -> digit )
            return 0;
        a = a -> next;
        b = b -> next;
    }
    return 1;
}

void test_max ( TITEM * ref, TITEM * act ) {

    if ( ! compare ( ref, act ) ) {
        printf("ERR: VALUE MISMATCH\n");
        printf("EXP: ");
        printList ( ref );
        printf("GOT: ");
        printList ( act );
        g_Fail++;
    } else g_Ok++;
    
    deleteList ( ref );
}

int main ( void ) {
    TITEM * x[100];
    int nr;

    nr = 3;
    x[0] = parseList ( "091" );
    x[1] = parseList ( "0097" ); 
    x[2] = parseList ( "113" );
    test_max ( parseList ( "113" ), maxOf ( x, nr ) );
    deleteListArr ( x, nr );

    printf( "Passed:%d\nFailed:%d\n", g_Ok, g_Fail );
    return 0;
}