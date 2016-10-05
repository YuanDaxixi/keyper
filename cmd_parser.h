/*
 *  command parser
 *
 *
 *  (C)    2016-10    Yuanda Zhang
 */

#ifndef __CMD_PARSER_H__
#define __CMD_PARSER_H__

#include "info_struct.h"
#include "PRG.h"
#include "rw_info.h"
#include "sha.h"
#include "cipher.h"

#define CMD_LEN 10
#define OPT_LEN (ACC_LEN + 1)
#define SWEEP "sweep"
#define DELETE_ACCOUNT  "dacc"
#define ADD_ACCOUNT "aacc"
#define LIST_ACCOUNT "lacc"
#define SHOW_KEY "skey"
#define CHANGE_KEY "ckey"
#define CHANGE_SECONDARY "csncd"
#define QUIT "exit"
#define SAVE_AND_QUIT "save"
#define HELP "help"


extern Identity password;
extern int num;
/*
 * fucntion:   delete all the information and change in main memory,
 *           so once invoke "save" to quit, everything gets empty.
 * return:     none
 * parameter:  account list
 * call:       none
 * called by:  cmd_exec
 */
static void sweep(DLinkedList *account_list);

/*
 * fucntion:   delete an account by its name
 * return:     none
 * parameter:  1.account list 2.account name
 * call:       none
 * called by:  cmd_exec
 */
static void del_acc(DLinkedList *account_list, char *account_name);

/*
 * fucntion:   add a new account
 * return:     none
 * parameter:  account list
 * call:       none
 * called by:  cmd_exec
 */
static void add_acc(DLinkedList *account_list);

/*
 * fucntion:   list all accounts
 * return:     none
 * parameter:  none
 * call:       none
 * called by:  cmd_exec
 */
static void show_acc(DLinkedList *account_list);

/*
 * fucntion:   show the password of the account
 * return:     void
 * parameter:  1.account list 2.account name
 * call:       none
 * called by:  cmd_exec
 */
static void show_psswrd(DLinkedList *account_list, char account_name[]);

/*
 * fucntion:   change the password of the account
 * return:     void
 * parameter:  1.account list 2.account name
 * call:       none
 * called by:  cmd_exec
 */
static void change_psswrd(DLinkedList *account_list, char account_name[]);

/*
 * fucntion:   change main password
 * return:     void
 * parameter:  none
 * call:       none
 * called by:  cmd_exec
 */
static void change_main(void);

/*
 * fucntion:   change secondary password
 * return:     void
 * parameter:  none
 * call:       none
 * called by:  cmd_exec
 */
static void change_scndry(void);

/*
 * fucntion:   quit the program without save
 * return:     none
 * parameter:  none
 * call:       none
 * called by:  cmd_exec
 */
static void good_bye(void);

/*
 * fucntion:   save changes users have done and users can change their password, then quit
 * return:     none
 * parameter:  account list
 * call:       none
 * called by:  cmd_exec
 */
static void save_quit(DLinkedList *account_list);

/*
 * fucntion:   show usage of each command
 * return:     none
 * parameter:  none
 * call:       none
 * called by:  cmd_exec
 */
static void cmd_tip(void);

/*
 * fucntion:   parse the command
 * return:     none
 * parameter:  1.string of command 2.account list
 * call:       ...
 * called by:  cmd
 */
static void parse_cmd(char cmd[], DLinkedList *acc_list);

/*
 * fucntion:   get command from users
 * return:     none
 * parameter:  address to save command
 * call:       none
 * called by:  cmd
 */
static void get_cmd(char cmd[]);

/*
 * fucntion:   interface of this module which contains command input, command parser, command execution 
 * return:     none
 * parameter:  account list
 * call:       get_cmd, parse_cmd 
 * called by:  none
 */
void cmd(DLinkedList *acc_list);

#endif