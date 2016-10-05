/*
 *  encrypt and decrypt the information in disk
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#ifndef __CIPHER_H__
#define __cipher_H__

#include "info_struct.h"
#include "io.h"
#include <conio.h>

/*
 * fucntion:   decrypt the file
 * return:     none
 * parameter:  none
 * call:       none
 * called by:  none
 */
void decrypt_kitty(void);

/*
 * fucntion:   input password
 * return:     address to save password
 * parameter:  1.address to save password
 * call:       none
 * called by:  decrypt_kitty
 */
char *get_password(char *passwd);

/*
 * fucntion:   encrypt the file
 * return:     none
 * parameter:  1.password
 * call:       none
 * called by:  none
 */
void encrypt_kitty(char *passwd);

#endif