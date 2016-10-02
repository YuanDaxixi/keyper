/*
 *  the interface of reading and writing
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#include "rw_info.h"

void create_file(void)
{
        char cmd[128];
        
        if ( _access(FILENAME, 0) == 0 )
                ;
        else
                fclose(fopen(FILENAME, "wb"));
}

int read_info(DLinkedList* account_list, pIdentity password)
{
        FILE *fp;
        AccKeyPair temp;
        pDListNode new_node;

        if ( (fp = fopen(FILENAME, "rb")) == NULL)
        {
                fprintf(stderr, "Can't open file: %s.\n", FILENAME);
                return 0;
        }
        if ( fread(password, sizeof(Identity), 1, fp) != 1 )
        {
                printf("Welcome!Welcome!\n");
                printf("It's your first time to use me, ");
                printf("I have many words to say, but I won't say, haha!\n");
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
        {
                printf("A,O. The data can't be read correctly.\n");
                return 0;
        }
        fclose(fp);

        return 1;
}

int write_info(DLinkedList* account_list, pIdentity password)
{
        FILE *fp;
        pDListNode temp;

        if ( (fp = fopen("temp", "wb")) == NULL )
        {
                fprintf(stderr, "Writing error!\n");
                return 0;
        }
        if ( fwrite(password, sizeof(Identity), 1, fp) != 1 )
        {
                fprintf(stderr, "Failing in writing password.\n");
                remove("temp");
                return 0;
        }

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
                remove(temp);
                return 0;
        }
        fclose(fp);
        remove(FILENAME);
        rename("temp", FILENAME);

        return 1;
}