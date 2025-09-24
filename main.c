/*
 * main.c
 *
 * Copyright (C) 2025.9.24 TOP WAYE topwaye@hotmail.com
 *
 * copy and replace all HTML or SQL words with predefined words which your browser is able to recognize
 * for converting command text into non-command text
 */

#include <stdio.h>

#define MAX_CHAR_VALUE_SIZE_IN_CHARS    16 /* include '\0' */

/* 
 * return the absolute value of I.
 */
static int abs ( int i )
{
    return i < 0 ? -i : i;
}

/*
 * the itoa function converts a integer value to its string representation.
 * it supports different base system from 2 (Binary) to 36.
 */
static void itoa ( int value, char * result, /* in, out */ int * size, int base )
{
    char c;
    int a;
    int i, j;

    if ( * size < 1 ) /* size >= len + 1 */
        return;
    
    /* check that the base is valid */
    if ( base < 2 || base > 36 )
    {
        * size = 0;
        return;
    }

    a = abs ( value );

    j = 0;
    do {
        if ( j + 1 == * size )
        {
            * size = 0;
            return;
        }
        * ( result + j ++ ) = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ" [ a % base ];
    } while ( a /= base );

    /* apply negative sign */
    if ( value < 0 )
    {
        if ( j + 1 == * size )
        {
            * size = 0;
            return;
        }
        * ( result + j ++ ) = '-';
    }

    * ( result + j ) = '\0';
    i = 0; * size = j --; /* return actual len, NOT including '\0' */
    while ( i < j )
    {
        c = * ( result + j );
        * ( result + j -- ) = * ( result + i );
        * ( result + i ++ ) = c;
    }
}

/*
 * return the actual length we copied and replaced, NOT including '\0'.
 */
int copy_and_replace ( char * src, int src_len, char * dst, int dst_size )
{
    int n;
	int i, j;

	if ( dst_size < 1 ) /* size >= len + 1 */
		return 0;

    j = 0;
	for ( i = 0; i < src_len; i ++ )
	{
		if ( j + 1 + 1 + MAX_CHAR_VALUE_SIZE_IN_CHARS >= dst_size )
			return 0;
    
        * ( dst + j ) = '&';
        j += 1;
        * ( dst + j ) = '#';
        j += 1;
        n = MAX_CHAR_VALUE_SIZE_IN_CHARS;
        itoa ( * ( src + i ), dst + j, & n, 10 ); /* NOT 16 */
        j += n;
        * ( dst + j ) = ';';
        j += 1;
	}

	*( dst + j ) = '\0';

	return j;
}

#define MAX_TEST_SIZE	128

int main ( )
{
    char unknown_chars_1 [ ] = "~<HTML>~<HTM>~SELECT~";
    char unknown_chars_2 [ MAX_TEST_SIZE ];

    int len = sizeof ( unknown_chars_1 ) / sizeof( unknown_chars_1 [ 0 ] ) - 1;

    len = copy_and_replace ( unknown_chars_1, len, unknown_chars_2, MAX_TEST_SIZE );
    printf ( "%d:%s\n", len, unknown_chars_2 );
    return 0;
}
