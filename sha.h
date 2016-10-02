/*
 *  SHA-256
 *
 *
 *  (C)    2015-9    CSDN-Blackkitty
 */

#ifndef __SHA_H__
#define __SHA_H__

#include <stdio.h>
#include <stdlib.h>

#define SHA256_ROTL(a,b) (((a>>(32-b))&(0x7fffffff>>(31-b)))|(a<<b))
#define SHA256_SR(a,b) ((a>>b)&(0x7fffffff>>(b-1)))
#define SHA256_Ch(x,y,z) ((x&y)^((~x)&z))
#define SHA256_Maj(x,y,z) ((x&y)^(x&z)^(y&z))
#define SHA256_E0(x) (SHA256_ROTL(x,30)^SHA256_ROTL(x,19)^SHA256_ROTL(x,10))
#define SHA256_E1(x) (SHA256_ROTL(x,26)^SHA256_ROTL(x,21)^SHA256_ROTL(x,7))
#define SHA256_O0(x) (SHA256_ROTL(x,25)^SHA256_ROTL(x,14)^SHA256_SR(x,3))
#define SHA256_O1(x) (SHA256_ROTL(x,15)^SHA256_ROTL(x,13)^SHA256_SR(x,10))

/*
计算字符串SHA-256
参数说明：
str         字符串指针
length      字符串长度
sha256         用于保存SHA-256的字符串指针
返回值为参数sha256
*/
extern char* StrSHA256(const char* str, long long length, char* sha256);

/*
计算文件SHA-256
参数说明：
file        文件路径字符串指针
sha256         用于保存SHA-256的字符串指针
返回值为参数sha256
*/
extern char* FileSHA256(const char* file, char* sha256);

#endif