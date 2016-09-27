/*
 *  The structure of the information of user's accounts
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#ifndef __INFO_STRUCT__
#define __INFO_STRUCT__

#define ACC_LEN 32
#define KEY_LEN 16
#define SHA_LEN 256
#define DES_LEN 128

#include "doubly_linked_list.h"

typedef struct{
        char encrypted_key[KEY_LEN];
        char stream_cipher[KEY_LEN];
        char account[ACC_LEN];
        char description[DES_LEN];
}AccKeyPair;

typedef struct{
        char main_key[SHA_LEN];
        char scndry_key[SHA_LEN];
}Identity;

typedef AccKeyPair *pAccKeyPair;
typedef Identity *pIdentity;

/*
 * fucntion:  create a new account and its key  
 * return:    return 0 if fail 
 * parameter: the list
 * call:      none
 * called by: 
 */
int add_account(DLinkedList *account_list);

/*
 * fucntion:  delete a account and its key
 * return:    return 0 if fail
 * parameter: 1. the list 2. tha name of the account
 * call:      none
 * called by: none
 */
int delete_account(DLinkedList *account_list, char* account_name);

/*
 * fucntion:  delete all the accounts
 * return:    none
 * parameter: the list
 * call:      none
 * called by: none
 */
void free_all(DLinkedList *account_list);

/*
 * fucntion:  change key
 * return:    return 0 if fail
 * parameter: 1.the list 2.the name of the account
 * call:      none
 * called by: none
 */
int change_key(DLinkedList *account_list, char *account_name);

/*
 * fucntion:  list all names of the accounts
 * return:    none
 * parameter: each account
 * call:      none
 * called by: none
 */
void show_account(const pDListNode account_node);

/*
 * fucntion:  verify the main key
 * return:    return 0 if fail
 * parameter: the address of main and secondary key(password)
 * call:      none
 * called by: none
 */
int verify_mainkey(void);

/*
 * fucntion:  verify the secondary key
 * return:    return 0 if fail
 * parameter: the address of main and secondary key(password)
 * call:      get_mainkey
 * called by: none
 */
int verify_scndrykey(void);

/*
 * fucntion:  get the encrypted key
 * return:    the address of the string
 * parameter: the address of the account node
 * call:      get_scndry
 * called by: delete_account, free_all, change_key
 */
const char* get_enkey(const pAccKeyPair);

/*
 * fucntion:  get the stream key
 * return:    the address of the string
 * parameter: the address of the account node
 * call:      none
 * called by: none
 */
const char* get_streamkey(const pAccKeyPair);

/*
 * fucntion:  get the secondary key
 * return:    the address of the string
 * parameter: none
 * call:      none
 * called by: verify_scndrykey
 */
const char* get_scndrykey(void);

/*
 * fucntion:  get the main key
 * return:    the address of the string
 * parameter: the address of the account node
 * call:      none
 * called by: verify_mainkey
 */
const char* get_mainkey(void);

#endif