/*
*
*
*
*  (C)    2016-9    Yuanda Zhang
*/

#include "PRG.h"
#include <time.h>
#include <ctype.h>

static int gen_prandom(void)
{
        return rand() % 256;
}

void gen_stream(char cipher[], int length)
{
        int i;

        for ( i = 0; i < length; i++ )
                cipher[i] = (char)gen_prandom();
        cipher[i] = '\0';
}

void gen_key(pAccKeyPair cipher_key)
{
        int key_len, temp, i;
        int lower, upper, special, digit;
        digit = lower = upper = special = 1;

        srand(time(NULL));
        key_len = MIN_LEN + gen_prandom() % (DIS + 1);
        gen_stream(cipher_key->stream_cipher, key_len);

        while ( digit || lower || upper || special )
        {
                lower = upper = special = 1;
                for ( i = 0; i < key_len; i++ )
                {
                        while ( (temp = gen_prandom() >> 1) < '!' || temp > 'z' )
                                continue;
                        cipher_key->encrypted_key[i] = (char)temp;

                        if ( isupper(temp) )
                                upper = 0;
                        else if ( islower(temp) )
                                lower = 0;
                        else if ( isdigit(temp) )
                                digit = 0;
                        else
                                special = 0;
                }
                cipher_key->encrypted_key[i] = '\0';
        } 

        for ( i = 0; i < key_len; i++ )
                cipher_key->encrypted_key[i] ^= cipher_key->stream_cipher[i];
}