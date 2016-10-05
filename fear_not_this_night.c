/*
 *  the main program for this keyper
 *
 *
 *  (C)    2016-10    Yuanda Zhang
 */

#include "cipher.h"
#include "cmd_parser.h"
#include "info_struct.h"
#include "rw_info.h"

static void welcome(void);

int main(void)
{
        DLinkedList acc_list;

        welcome();
        init_list(&acc_list);
        decrypt_kitty();
        create_file();
        read_info(&acc_list, &password);
        cmd(&acc_list);

        return 0;
}

static void welcome(void)
{
        printf("It's just a little thing to make your accounts and keys safer.\n");
        printf("GPG2 is invoked to ensure the security.\n");
        printf("All keys are stored in ciphertext(even after decryption).\n");
        printf("You set two passwords[main and secondary], the main for encrytion and decrytion, ");
        printf("the secondary for showing and changing keys of accounts, also deleting accounts.\n");
        printf("The true security depends on your own habbit, not software.\nGOOD LUCK!\n\n");
}