/*
 *  encrypt and decrypt the information in disk
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "cipher.h"

void decrypt_kitty(void)
{
        char cmd[128] = "gpg --batch --passphrase ";
        char passwd[KEY_LEN + 1];

        if ( _access(CIPHERTXT, 0) == 0 )
        {
                printf("Enter the password: ");
                get_password(passwd);
                strcat(cmd, passwd);
                strcat(cmd, " -o ");
                strcat(cmd, PLAINTXT);
                strcat(cmd, " -d ");
                strcat(cmd, CIPHERTXT);
                system(cmd);
        }
}

void encrypt_kitty(char *passwd)
{
        char cmd[128] = "gpg --batch --passphrase ";

        strcat(cmd, passwd);
        strcat(cmd, " -o ");
        strcat(cmd, CIPHERTXT);
        strcat(cmd, " -c ");
        strcat(cmd, PLAINTXT);
        system(cmd);
}

char* get_password(char *passwd)
{
        int i;
        char temp;

        for ( i = 0; i < KEY_LEN; i++ )
        {
                temp = _getch();
                if ( temp == '\r' )
                        break;
                else if ( temp == '\b' )
                {
                        if ( i > 0 )
                        {
                                i -= 2;
                                printf("\b \b");
                        }
                        else if ( i == 0 )
                                i--;
                        else
                                ;
                }
                else
                {
                        passwd[i] = temp;
                        putchar('*');
                }
        }
        putchar('\n');
        passwd[i] = '\0';

        return passwd;
}