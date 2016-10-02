/*
 *  the interface of reading and writing
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#ifndef __RW_INFO_H__
#define __RW_INFO_H__

#include <stdio.h>
#include <io.h>
#include "info_struct.h"

#define FILENAME "kitty.dat"

/*
 * fucntion:   read passwords and accounts information from the file into main memory
 * return:     return 0 if fail
 * parameter:  1.account list 2.address to save password
 * call:       none
 * called by:  none
 */
int read_info(DLinkedList* account_list, pIdentity password);

/*
 * fucntion:   write passwords and accounts into file
 * return:     return 0 if fail
 * parameter:  1.account list 2.address to save password
 * call:       none
 * called by:  none
 */
int write_info(DLinkedList* account_list, pIdentity password);

/*
 * fucntion:   create the file to save account information if not exist
 * return:     none
 * parameter:  none
 * call:       none
 * called by:  none
 */
void create_file(void);

#endif