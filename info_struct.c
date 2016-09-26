/*
 *  The operatoin of the information of user's accounts
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "info_struct.h"
#include "PRG.h"

static Identity password;

int add_account(DLinkedList *account_list)
{
        AccKeyPair value;
        pDListNode new_node;

        if ( new_node_back(account_list) == NULL )
                return 0;
        else
        {
                printf("Enter account name[%d bytes at most]: ", ACC_LEN);
                fgets(&value.account, ACC_LEN ,stdin);
                //generate a key for the account
                assign_value(new_node, (Elem)&value, sizeof(value));
                return 1;
        }
}


int delete_account(DLinkedList *account_list, char* account_name)
{
        pDListNode account_node;
        AccKeyPair value;

        if ( verify_scndrykey() != 0 )
        {
                strncpy(&value.account, account_name, ACC_LEN);
                account_node = seek_by_value(account_list, (Elem)&value, is_same);
                return delete_node(account_list, account_node);
        }
        else
                return 0;
}

void free_all(DLinkedList *account_list)
{
        char choose;

        printf("Are you sure to delete all the accounts information?[Y/N]\n");
        if ( (choose = getchar()) == 'y' || choose == 'Y' )
        {
                if ( verify_scndrykey() != 0 )
                {
                        free(account_list);
                        system("del /f /q filename");
                }
        }
        else
                ;

        while ( getchar() != '\n' )
                continue;
}


int change_key(DLinkedList *account_list, char *account_name)
{
        pDListNode account_node;
        AccKeyPair value;
        int ret;

        if ( verify_scndrykey() != 0 )
        {
                strncpy(&value.account, account_name, ACC_LEN);
                account_node = seek_by_value(account_list, (Elem)&value, is_same);
                //generate a new key for the account
                ret = (int)assign_value(account_node, (Elem)&value, sizeof(value));
        }

        return ret;
}


void show_account(const pDListNode account_node)
{
        static num = 0;
        pAccKeyPair value = account_node->data;

        printf("%2d: %-*s\n\n", num++, ACC_LEN, value->account);
}


int verify_mainkey(void)
{
        char input[KEY_LEN];

        printf("Enter password: ");
        fgets(input, KEY_LEN, stdin);
        return !strcmp(input, password.main_key);
}


int verify_scndrykey(void)
{
        char input[KEY_LEN];

        printf("Secondary password: ");
        fgets(input, KEY_LEN, stdin);
        return !strcmp(input, get_scndrykey());
}

const char* get_enkey(const pAccKeyPair account_node)
{
        return account_node->encrypted_key;
}

const char* get_streamkey(const pAccKeyPair account_node)
{
        return account_node->stream_cipher;
}

const char* get_scndrykey(void)
{
        return password.scndry_key;
}

static int is_same(Elem father, Elem dad)
{
        return !strcmp( ((pAccKeyPair)father)->account, ((pAccKeyPair)dad)->account);
}