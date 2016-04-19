/*******************************************************
* Code contributed by Chris Takahashi,                 *
* ctakahashi (at) users (dot) sourceforge (dot) net.   *
* See stdlib.h for licence.                            *
* $Date: 2005/08/31 11:39:47 $                         *
*******************************************************/
// Temp. buffer eliminated by Sergey A. Borshch

#include <stdlib.h>
#include <stdint.h>

char *itoa(int num, char *str, int radix)
{
    //an int can only be 32 bits long
    //at radix 2 (binary) the string
    //is at most 32 + 1 ('\0') chars long.

    uint_fast8_t sign = 0;
    char * pDst = str;

    //save sign for radix 10 conversion
    if (radix == 10 && num < 0)
    {
        sign = 1;
        num = -num;
    }

    unsigned int Tmp = num;
    //construct a backward string of the number.
    do
    {
        uint_fast8_t digit = Tmp % radix;
        Tmp   = Tmp / radix;
        if (digit < 10) 
            *pDst++ = digit + '0';
        else
            *pDst++ = digit - 10 + 'A';
    }
    while (Tmp > 0);

    //now add the sign for radix 10
    if (radix == 10 && sign)
        *pDst++ = '-';

    // add null termination.
    *pDst-- = '\0';

    //now reverse the string.
    char *pHead = str;
    char *pTail = pDst;
    while ( pTail > pHead )
    {   // while there are still chars
        char Tmp = *pTail;
        *pTail-- = *pHead;
        *pHead++ = Tmp;
    }
    return str;
}

