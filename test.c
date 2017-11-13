/*
 *  test PRG and info_struct
 *
 *
 *  (C)    2016-9    Yuanda Zhang    
 */

#include "PRG.h"
#include "info_struct.h"

int main(void)
{
        DLinkedList account_list;
        int choose;
        char account_name[ACC_LEN];

        init_list(&account_list);

        printf("1. add a account.        2. change password.\n");
        printf("3. delete a account.     4. delete all information.\n");
        printf("5. show password.        6. show all account name.\n\n");
        printf("Aha: ");
        while ( (choose = getchar()) <= '6' && choose >= '1' )
        {
                while ( getchar() != '\n' );
                if ( choose == '1' )
                        add_account(&account_list);
                else if ( choose == '2' )
                {
                        printf("Account name: ");
                        gets(account_name);
                        change_key(&account_list, account_name);
                }
                else if ( choose == '3' )
                {
                        printf("Account name: ");
                        gets(account_name);
                        delete_account(&account_list, account_name);
                }
                else if ( choose == '4' )
                        free_all(&account_list);
                else if ( choose == '5' )
                {
                        printf("Account name: ");
                        gets(account_name);
                        show_password(&account_list, account_name);
                }
                else if ( choose == '6' )
                        print_list(&account_list, show_account);
                else
                        ;
                printf("Aha: ");
        }
        printf("It seems everthing goes right, good luck!\n");
        free_list(&account_list);

        return 0;
}