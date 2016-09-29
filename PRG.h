/*
 *  pseudorandom generator
 *
 *
 *  (C)    2016-9    Yuanda Zhang
 */

#ifndef __PRG_H__
#define __PRG_H__

#include "info_struct.h"

#define DIS 5
#define MIN_LEN (KEY_LEN - DIS )
#define MAX_LEN KEY_LEN


/*
 * fucntion:   generate a byte-long pseudorandom  
 * return:     pseudorandom
 * parameter:  none
 * call:       none
 * called by:  
*/
static int gen_prandom(void);

/*
 * fucntion:   generate a stream cipher
 * return:     none
 * parameter:  1.the address to save the stream cipher 2.cipher length
 * call:       gen_prandom
 * called by:  
 */
void gen_stream(char cipher[], int length);

/*
 * fucntion:   generate a password(key) for user's account and encrypt it with stream cipher
 * return:     none
 * parameter:  the address to save the password(encrypt) and stream cipher
 * call:       gen_stream
 * called by:  none
 */
void gen_key(pAccKeyPair cipher_key);

#endif