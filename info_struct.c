/*
 *  The operatoin of the information of user's accounts
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "info_struct.h"
#include "PRG.h"
#include "sha.h"

Identity password; // just for test

int add_account(DLinkedList *account_list)
{
        AccKeyPair value;
        pDListNode new_node;

        if ( (new_node = new_node_back(account_list)) == NULL )
                return -1;

        printf("Enter account name[%d bytes at most]: ", ACC_LEN);
        gets(value.account);
        
        if ( seek_by_value(account_list, (Elem)&value, is_same) != NULL )
        {
                printf("The account you added exists!\n");
                return 0;
        }
        gen_key(&value);
        printf("Add a description for this account[128 at most]:\n");
        gets(value.description);
        assign_value(new_node, (Elem)&value, sizeof(value));

        return 1;
}


int delete_account(DLinkedList *account_list, char* account_name)
{
        pDListNode account_node;
        AccKeyPair value;

        if ( verify_scndrykey() != 0 )
        {
                strncpy(value.account, account_name, ACC_LEN);
                value.account[ACC_LEN + 1] = '\0';
                account_node = seek_by_value(account_list, (Elem)&value, is_same);
                if ( account_node == NULL )
                        printf("The account doesn't exist.\n");
                return account_node != NULL ? (int)delete_node(account_list, account_node) : 0;
        }
        return 0;
}

void free_all(DLinkedList *account_list)
{
        char choose;

        printf("Are you sure to delete all information and changes?[Y/N]\n");
        if ( (choose = getchar()) == 'y' || choose == 'Y' )
        {
                while ( getchar() != '\n' );
                if ( verify_scndrykey() != 0 )
                {
                        free_list(account_list);
                        init_list(account_list);
                }
        }
        else
                while ( getchar() != '\n' );
}


int change_key(DLinkedList *account_list, char *account_name)
{
        pDListNode account_node;
        AccKeyPair value;
        int ret;

        if ( verify_scndrykey() != 0 )
        {
                strncpy(value.account, account_name, ACC_LEN);
                value.account[ACC_LEN + 1] = '\0';
                account_node = seek_by_value(account_list, (Elem)&value, is_same);
                if ( account_node == NULL )
                {
                        printf("The account doesn't exist.\n");
                        ret = 0;
                }
                else
                {
                        gen_key(&value);
                        ret = (int)assign_value(account_node, (Elem)&value, sizeof(value));
                }
        }

        return ret;
}


void show_account(const pDListNode account_node)
{
        static num = 0;
        pAccKeyPair value = account_node->data;

        printf("%2d: %-*s %-s\n\n", num++, ACC_LEN, value->account, value->description);
}


int verify_mainkey(void)
{
        char input[KEY_LEN + 1];
        char temp[SHA_LEN];

        printf("Enter password: ");
        get_password(input);
        if ( strcmp(StrSHA256(input, strlen(input), temp), get_mainkey()) )
                printf("Bad pasword.\n");

        return !strcmp(input, get_mainkey());
}


int verify_scndrykey(void)
{
        char input[KEY_LEN + 1];
        char temp[SHA_LEN];

        printf("Secondary password: ");
        get_password(input);
        if ( strcmp(StrSHA256(input, strlen(input), temp), get_scndrykey()) )
                printf("Bad password.\n");

        return !strcmp(input, get_scndrykey());
}

void show_password(DLinkedList *account_list, char account_name[])
{
        pDListNode account_node;
        AccKeyPair value;
        unsigned int i;

        if ( verify_scndrykey() )
        {
                strncpy(value.account, account_name, ACC_LEN);
                value.account[ACC_LEN + 1] = '\0';
                account_node = seek_by_value(account_list, (Elem)&value, is_same);
                if ( account_node == NULL )
                {
                        printf("The account dosen't exist.\n");
                        return;
                }
                value = *(pAccKeyPair)account_node->data;
                for ( i = 0; i < strlen(value.encrypted_key); i++ )
                        printf("%c", value.encrypted_key[i] ^ value.stream_cipher[i]);
                putchar('\n');
        }
}

const char* get_enkey(const pAccKeyPair account_node)
{
        return account_node->encrypted_key;
}

const char* get_streamkey(const pAccKeyPair account_node)
{
        return account_node->stream_cipher;
}

const char* get_mainkey(void)
{
        return password.main_key;
}

const char* get_scndrykey(void)
{
        return password.scndry_key;
}

static int is_same(Elem father, Elem dad)
{
        return !strcmp( ((pAccKeyPair)father)->account, ((pAccKeyPair)dad)->account);
}