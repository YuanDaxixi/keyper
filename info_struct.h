/*
 *  The structure of the information of user's accounts
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#ifndef __INFO_STRUCT_H__
#define __INFO_STRUCT_H__

#define ACC_LEN 32
#define KEY_LEN 16
#define SHA_LEN 256
#define DES_LEN 128
#define PLAINTXT "kitty.dat"
#define HISTORY "history"
#define CIPHERTXT "kitty.gpg"

#include "doubly_linked_list.h"
#include "cipher.h"

typedef struct{
        char encrypted_key[KEY_LEN + 1];
        char stream_cipher[KEY_LEN + 1];
        char account[ACC_LEN + 1];
        char description[DES_LEN + 1];
}AccKeyPair;

typedef struct{
        char main_key[SHA_LEN + 1];
        char scndry_key[SHA_LEN + 1];
}Identity;

typedef AccKeyPair *pAccKeyPair;
typedef Identity *pIdentity;

/*
 * fucntion:  create a new account and its key  
 * return:    return -1 if fail and return 0 if account exits 
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
 * fucntion:  list name of the account
 * return:    none
 * parameter: account node
 * call:      none
 * called by: none
 */
void show_account(const pDListNode account_node);

/*
 * fucntion:  verify the main key
 * return:    return 0 if fail
 * parameter: the address of main and secondary key(password)
 * call:      get_mainkey
 * called by: none
 */
int verify_mainkey(void);

/*
 * fucntion:  verify the secondary key
 * return:    return 0 if fail
 * parameter: the address of main and secondary key(password)
 * call:      get_scndry
 * called by: delete_account, free_all, change_key
 */
int verify_scndrykey(void);

/*
 * fucntion:  get the encrypted key
 * return:    the address of the string
 * parameter: the address of the account node
 * call:      none
 * called by: none
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
* fucntion:  show uesr the password of the account he offered
* return:    none
* parameter: 1. the list. 2.account name
* call:      get_enkey get_streamkey
* called by: none
*/
void show_password(DLinkedList *account_list, char account_name[]);

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
 * parameter: none
 * call:      none
 * called by: verify_mainkey
 */
const char* get_mainkey(void);

/*
 * fucntion:  judge whether account name is same
 * return:    return 1 if same, or 0
 * parameter: 1.first account  2.second account
 * call:      none
 * called by: none
 */
static int is_same(Elem father, Elem dad);

#endif