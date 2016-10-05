/*
 *  the interface of reading and writing
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "rw_info.h"
#include "sha.h"

void create_file(void)
{
        if ( _access(PLAINTXT, 0) == 0 )
                ;
        else
                fclose(fopen(PLAINTXT, "wb"));
}

int read_info(DLinkedList* account_list, pIdentity password)
{
        FILE *fp;
        AccKeyPair temp;
        pDListNode new_node;

        if ( (fp = fopen(PLAINTXT, "rb")) == NULL)
        {
                fprintf(stderr, "Can't open file: %s.\n", PLAINTXT);
                return 0;
        }
        if ( fread(password, sizeof(Identity), 1, fp) != 1 )
        {
                printf("Welcome~Welcome!\n");
                printf("It's your first time to use me, ");
                printf("I have many words to tell, but I won't say, haha!\n");
                StrSHA256("0", strlen("0"), password->main_key);
                StrSHA256("0", strlen("0"), password->scndry_key);
        }
        while ( fread(&temp, sizeof(AccKeyPair), 1, fp) == 1 )
        {
                new_node = new_node_back(account_list);
                if ( new_node )
                        assign_value(new_node, (Elem)&temp, sizeof(temp));
                else
                        printf("An interesting error occurred.\n");
        }
        if ( feof(fp) )
                printf("Now you can do something...\n\n");
        else
                printf("AO. The data can't be read correctly.\n");
            
        fclose(fp);
        remove(PLAINTXT);

        return 1;
}

int write_info(DLinkedList* account_list, pIdentity password)
{
        FILE *fp;
        pDListNode temp;
        int ret = 1;

        if ( (fp = fopen("temp", "wb")) == NULL )
        {
                fprintf(stderr, "Writing error!\n");
                ret = 0;
        }
        if ( fwrite(password, sizeof(Identity), 1, fp) != 1 )
        {
                fprintf(stderr, "Failing in writing password.\n");
                ret = 0;
        }
        else
        {
                temp = next_list_node(list_head(account_list));
                while ( is_valid_node(temp, account_list) )
                {
                        fwrite(data_list_node(temp, pAccKeyPair), sizeof(AccKeyPair), 1, fp);
                        temp = next_list_node(temp);
                }

                if ( !ferror(fp) )
                        printf("Done...\n\n");
                else
                {
                        printf("A,O. The data can't be written correctly.\n");
                        ret = 0;
                }
        }
        fclose(fp);
        rename("temp", PLAINTXT);

        return ret;
}