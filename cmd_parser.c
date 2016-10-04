/*
 *  command parser
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "cmd_parser.h"
#include "ctype.h"

static void sweep(DLinkedList *account_list)
{
        free_all(account_list);
        printf("The change you have done has been deleted.\n");
        printf("Once you [save], your information will be empty.\n");
        printf("So directly [exit] if you want to only cancel changes.\n\n");

}

static void del_acc(DLinkedList *account_list, char *account_name)
{
        int ret;

        ret = delete_account(account_list, account_name);
        if ( ret == 1 )
                printf("[%s] deleted.\n", account_name);
        else
                printf("Failed to delete.\n");
}

static void add_acc(DLinkedList *account_list)
{
        int ret;

        ret = add_account(account_list);
        if ( ret == -1 )
                printf("An memory error occurs, please try again.\n\n");
}

static void show_acc(DLinkedList *account_list)
{
        pDListNode node;
        
        node = next_list_node(list_head(account_list));
        printf("index  %-*s %-s\n\n", ACC_LEN, "account name", "description");
        while ( is_valid_node(node, account_list) )
        {
                show_account(node);
                node = next_list_node(node);
        }
}

static void show_psswrd(DLinkedList *account_list, char account_name[])
{
        show_psswrd(account_list, account_name);
}

static void change_psswrd(DLinkedList *account_list, char account_name[])
{
        int ret;

        ret = change_key(account_list, account_name);
        if ( ret == 0 )
                printf("Failed to chagne");
}

static void change_main(void)
{
        char sha256[SHA_LEN + 1];
        char key[KEY_LEN + 1];
        char key2[KEY_LEN + 1];
        char temp;
        int i;

        if ( verify_mainkey() && verify_scndrykey() )
        {
                printf("Enter your new key[%d character at most]: ", KEY_LEN);
                get_password(key);
                printf("Enter it again: ");
                while ( strcmp(get_password(key2), key) )
                        printf("The keys you enterred are not same.\nEnter again: ");
                StrSHA256(key, strlen(key), sha256);
                strcpy(password.main_key, sha256);
        }
}

static void change_scndry(void)
{
        char sha256[SHA_LEN + 1];
        char key[KEY_LEN + 1];
        char key2[KEY_LEN + 1];
        char temp;
        int i;

        if ( verify_scndrykey() )
        {
                printf("Enter your new key[%d character at most]", KEY_LEN);
                get_password(key);
                printf("Enter it again: ");
                while ( strcmp(get_password(key2), key) )
                        printf("The keys you enterred are not same.\nEnter again: ");
                StrSHA256(key, strlen(key), sha256);
                strcpy(password.scndry_key, sha256);
        }
}

static void good_bye(void)
{
        printf("Make sure you have saved your change, if not, ");
        printf("I'm sorry it has lost forever.\nGood Luck!!!\n");

        exit(0);
}

static void save_quit(DLinkedList *account_list)
{
        char input_key[KEY_LEN + 1];
        char temp[KEY_LEN + 1];
        char sha256[SHA_LEN];

        printf("Enter your main password[a different key means you want to change it]:");
        get_password(input_key);

        if ( strcmp(StrSHA256(input_key, strlen(input_key), sha256), get_mainkey()) )
        {
                printf("Enter it again if you mean a new password\n");
                scanf("%s", temp);
                while ( getchar() != '\n' );
                if ( strcmp(input_key, temp) )
                {
                        printf("The passwords you enterrd were not same.\n");
                        return;
                }
                else
                {
                        strcpy(password.main_key, sha256);
                }
        }
        write_info(account_list, &password);
        rename(CIPHERTXT, HISTORY);
        encrypt_kitty(input_key);
        remove(PLAINTXT);
        good_bye();
}

static void parse_cmd(char cmd[], DLinkedList *acc_list)
{
        char cmd_name[CMD_LEN];
        char *opt_name;

        sprintf(cmd_name, "%s", cmd);
        opt_name = cmd + strlen(cmd_name);
        while ( isblank(*opt_name) )
                continue;

        if ( strstr(cmd_name, SWEEP) )
                sweep(acc_list);
        else if ( strstr(cmd_name, LIST_ACCOUNT) )
                show_acc(acc_list);
        else if ( strstr(cmd_name, ADD_ACCOUNT) )
                add_acc(acc_list);
        else if ( strstr(cmd_name, CHANGE_SECONDARY) )
                change_scndry();
        else if ( strstr(cmd_name, QUIT) )
                good_bye();
        else if ( strstr(cmd_name, SAVE_AND_QUIT) )
                save_quit(acc_list);
        else if ( strstr(cmd_name, DELETE_ACCOUNT) )
                del_acc(acc_list, opt_name);
        else if ( strstr(cmd_name, SHOW_KEY) )
                show_psswrd(acc_list, opt_name);
        else if ( strstr(cmd_name, CHANGE_KEY) )
                change_psswrd(acc_list, opt_name);
        else
                printf("Bad command\n");
}

static void get_cmd(char cmd[])
{
        int length = CMD_LEN + OPT_LEN;
        int i;
        char temp;

        printf(">>> ");
        for ( i = 0; i < length - 1; i++ )
        {
                if ( (temp = getchar()) == '\n' )
                        break;
                else
                        cmd[i] = temp;
        }
        cmd[i] = '\0';
}

void cmd(DLinkedList *acc_list)
{
        char cmd[CMD_LEN + OPT_LEN];

        get_cmd(cmd);
        parse_cmd(cmd, acc_list);
}