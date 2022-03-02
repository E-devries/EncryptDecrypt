
/*
 * FILE          : encryptDecrpyt.h
 * PROJECT       : EncryptDecrypt
 * PROGRAMMER    : Elizabeth deVries
 * FIRST VERSION : 2022-01-22
 * DESCRIPTION   : This file contains prototype declarations for non-main functions called in encryptDecrypt.c
*/

#ifndef EDCRYPT_H
#define EDCRYPT_H

// includes

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Prototypes

void translateString(char *outString, char *inString, bool translationMode);

void encodeASCII(char ascii, char* hexPair);

char decodeHex(char* hexChar);

void createOutFileName(char *outFileName, char *inFileName, bool translationMode);

// Constants

#define MAX_TRANSLATION_STRING 241	    // the max character length of a string to be decrypted, which is at maximum double the max size of an ascii string to encrpt, 241
#define MAX_FILE_NAME 256               // max character length of a file name
#define SHIFT_COUNT 16                  // amount to shift char value when decrypting/encrypting
#define MIN_ASCII 32                    // minimum value that an ascii character can be shifted to
#define ADD_ASCII 144                   // if an ascii is shifted too low, this value is added to it
#define MAX_OUT_CHAR 127                // max value that decoded ascii can be converted to
#define HEX_LETTER_TO_NUM 55            // number to convert from A-F hex ascii to it's number representation 
#define HEX_NUMBER_TO_NUM 48            // number to convert from a ascii digit to its number representation


const char *TAB_ENCODE;                 // the special character sequence for encoding tabs


// command line constants
const char *USAGE;
const char *SWITCHES;
const char *ENCRYPT_SWITCH;
const char *DECRYPT_SWITCH;

// bool constants
const bool ENCRYPT;
const bool DECRYPT;

// file extension constants
const char *ENCRYPT_EXT;
const char *DECRYPT_EXT;


#endif