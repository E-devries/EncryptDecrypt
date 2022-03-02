/*
 * FILE : translate.c
 * PROJECT : EncryptDecrypt
 * PROGRAMMER : Elizabeth deVries
 * FIRST VERSION : 2022-01-22
 * DESCRIPTION   : This file contains decryption and encryption related functions for the EncryptDecrypt program
 */


#include"../inc/encryptDecrypt.h"




// FUNCTION    : translateString
// PARAMETERS  : char *outString : the resulting encrypted or decrypted string
//               char *inString  : the string to be encrypted or decrypted
//               bool translationMode : indicates whether the output file needs to be encrypted (true) or decrypted (false)
// RETURNS     : void
// DESCRIPTION : This function encrypts a string of characters into hexadecimal pairs for each character excluding tab and carriage return, or decrypts the reverse
void translateString(char *outString, char *inString, bool translationMode)
{
    // get string length to determine loop
    int stringLength = strlen(inString);

    for (int i = 0; i < stringLength; i++)
    {
        
        char translatedChar[3] = {' '}; // short string to hold either hex pair or ascii

        // for each character, encode or decode into translated char string
        if (translationMode == ENCRYPT)
        {
            // get pair of hex characters and concatenate to outstring
            char outputHexPair[3] = {' '};
            encodeASCII(inString[i], outputHexPair);
            strcpy(translatedChar, outputHexPair);
        }
        else
        {
            // get pair of characters, incrementing i so that we don't repeat characters
            char inputHexPair[3] = {inString[i], inString[++i]};
            char asciiDecoded[2] = {decodeHex(inputHexPair)};
                
            strcpy(translatedChar, asciiDecoded);
        }

        // Put translated character into outString

        // check if the outline string is still empty (no characters added yet)
        if (strcmp(outString, " ") == 0)
        {
            // if first, then copy first hex pair
            strcpy(outString, translatedChar);
        }
        // otherwise, concatenate
        else
        {
            strcat(outString, translatedChar);
        }
    }

    return;
}



// FUNCTION    : encodeASCII
// PARAMETERS  : char ascii : the single character to convert
//               char * : the resulting pair of hexadecimal characters
// RETURNS     : void
// DESCRIPTION : This function takes a single ascii character, and if not tab or carriage return, translates it into a pair of hexadecimal characters 
//               after shifting its ascii value. Carriage returns are not altered, while tabs are given the special translation 'TT'
void encodeASCII(char ascii, char* hexPair)
{

    // this should not get called on newline characters, but check for them anyways
    if (ascii == '\n')
    {
        strcpy(hexPair, "\n");
    }
    // if tab, use special encoding
    else if (ascii == '\t')
    {
        strcpy(hexPair, TAB_ENCODE);
    }
    // otherwise, do encoding calculation
    else
    {
        // shift value down
        int newHexValue = (int)ascii - SHIFT_COUNT;

        // if below minimum, add specified amount
        if (newHexValue < MIN_ASCII)
        {
            newHexValue = newHexValue - MIN_ASCII + ADD_ASCII;
        }

        // get hex code
        sprintf(hexPair, "%X", newHexValue);
    }

    return;
}



// FUNCTION    : decodeHex
// PARAMETERS  : char* hexChar
// RETURNS     : char : the resulting single ascii character
// DESCRIPTION : This function translates the encoded pair of hex characters by first checking for the special translation 'TT' which becomes a tab character,
//             : and shifting all other character values to find their original ascii representation
char decodeHex(char* hexChar)
{
    char decodedASCII = ' ';

    // a newline shouldn't be in the input of this function, but just incase check for it
    if (strchr(hexChar, '\n') != NULL)
    {
        decodedASCII = '\n';
    }
    // check for tab code, which is a special case and can't be translated the normal way
    else if (strcmp(hexChar, TAB_ENCODE) == 0)
    {
        decodedASCII = '\t';
    }
    // otherwise, decrypt as normal
    else
    {
        // get int from each hex code
        char firstValueChar = 0;
        char secondValueChar = 0;
        int interimCharAsInt = 0;

        sscanf(hexChar, "%c %c", &firstValueChar, &secondValueChar);

        // get face values instead of character

        // if letter, needs to subtract HEX_LETTER_TO_NUM
        if (firstValueChar >= 'A')
        {
            firstValueChar -= (char)HEX_LETTER_TO_NUM;
        }
        // otherwise, it's a digit and needs to have ascii difference subtracted instead
        else
        {
            firstValueChar -= (char)HEX_NUMBER_TO_NUM;
        }


        // if letter, needs to subtract HEX_LETTER_TO_NUM
        if (secondValueChar >= 'A')
        {
            secondValueChar -= (char)HEX_LETTER_TO_NUM;
        }
        // otherwise, it's a digit and needs to have ascii difference subtracted instead
        else
        {
            secondValueChar -= (char)HEX_NUMBER_TO_NUM;
        }

        // translate value in reverse by multiplying first value by 16 and adding second value
        interimCharAsInt = (int)firstValueChar * SHIFT_COUNT;

        interimCharAsInt += (int)secondValueChar;
        
        // next, shift in reverse
        interimCharAsInt += SHIFT_COUNT;

        // if value is above minimum outChar value, fix by doing encode trick in reverse
        if (interimCharAsInt > MAX_OUT_CHAR)
        {
            interimCharAsInt = interimCharAsInt - ADD_ASCII + MIN_ASCII;
        }

        // set decodedASCII
        decodedASCII = (char)interimCharAsInt;
    }

    return decodedASCII;
}